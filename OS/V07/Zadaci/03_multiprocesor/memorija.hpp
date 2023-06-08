#ifndef MEMORIJA_HPP_INCLUDED
#define MEMORIJA_HPP_INCLUDED

#include <mutex>
#include <condition_variable>
#include <iostream>

#include "dijagnostika.hpp"

using namespace std;
using namespace chrono;

enum Stanje {SLOBODAN, CITANJE, UPIS };

struct Lokacija {                        // Struktura koja predstavlja opis trenutnih pristupa jednoj memorijskoj reči
    Stanje stanje;                      // Memorijska reč moze biti u stanjima: slobodna, čita se ili piše se
    int aktivnih_citaca;                // Broj aktivnih čitača na memorijskoj reči
    int citaca_ceka;                    // Broj čitača koji čekaju na čitanje date reči
    condition_variable citanje;         // CV u koju se uvezuju oni koji hoće da čitaju reč
    condition_variable upis;            // CV u koju se uvezuju oni koji hoće da pišu u datu reč
    Lokacija() : stanje(SLOBODAN), aktivnih_citaca(0), citaca_ceka(0) {} // Na početku stanje slobodno i nema čitača i pisača
};

class Memorija {
private:
    Dijagnostika& dijagnostika;
    int broj_adresa;
    mutex m;
    vector<char> memorija;
    vector<shared_ptr<Lokacija>> lokacije;

public:
    Memorija(Dijagnostika& d, int bajtova) : dijagnostika(d), memorija(bajtova) {
        for (int i = 0; i < bajtova / 4; i++) {
            lokacije.push_back(make_shared<Lokacija>());
        }
    }

    // Metoda koju poziva nit koja simulira proces koji pristupa memoriji kako bi obavila čitanje iz nje
    //
    // rbp    - Redni broj procesa
    // adresa - Lokacija sa koje se čita vrednost prethodno upisana u memoriju
    //
    // Potrebno je pozvati dijagnostika.proces_ceka_citanje kada je memorijska reč zaključana i proces mora da čeka.
    // Potrebno je pozvati dijagnostika.proces_procitao onda kada je ostvaren pristup memoriji i kada je vrednost učitana iz nje.
    char citaj(int rbp, int adresa) {
        int idx = adresa / 4;
        unique_lock<mutex> lock(m);
        
        while (lokacije[idx]->stanje == UPIS) {
            lokacije[idx]->citaca_ceka++;
            dijagnostika.proces_ceka_citanje(rbp, adresa);
            lokacije[idx]->citanje.wait(lock);
        }

        lokacije[idx]->citaca_ceka--;
        lokacije[idx]->aktivnih_citaca++;
        lokacije[idx]->stanje = CITANJE;

        lock.unlock();
        this_thread::sleep_for(seconds(1));
        lock.lock();

        lokacije[idx]->aktivnih_citaca--;

        if (lokacije[idx]->aktivnih_citaca == 0) {
            lokacije[idx]->stanje = SLOBODAN;
            lokacije[idx]->upis.notify_one();
        }

        char vrednost = memorija[idx];
        dijagnostika.proces_procitao(rbp, adresa, vrednost);
        return vrednost;
    }

    // Metoda koju poziva nit koja simulira proces koji pristupa memoriji kako bi obavila upis u nju
    //
    // rbp      - Redni broj procesa
    // adresa   - Lokacija u koju se upisuje nova vrednost
    // vrednost - Vrednost koja se upisuje u memoriju
    //
    // Potrebno je pozvati dijagnostika.proces_ceka_upis kada je memorijska reč zaključana i proces mora da čeka.
    // Potrebno je pozvati dijagnostika.proces_upisao onda kada je ostvaren pristup memoriji i kada je vrednost upisana u nju.
    void pisi(int rbp, int adresa, char vrednost) {
        int idx = adresa / 4;
        unique_lock<mutex> lock(m);

        while (lokacije[idx]->stanje != SLOBODAN) {
            dijagnostika.proces_ceka_upis(rbp, adresa);
            lokacije[idx]->upis.wait(lock);
        }
        
        lokacije[idx]->stanje = UPIS;

        lock.unlock();
        this_thread::sleep_for(seconds(1));
        lock.lock();

        memorija[idx] = vrednost;
        dijagnostika.proces_upisao(rbp, adresa, vrednost);

        lokacije[idx]->stanje = SLOBODAN;

        if (lokacije[idx]->citaca_ceka != 0)
            lokacije[idx]->citanje.notify_all();
        else
            lokacije[idx]->upis.notify_one();
    }
};

#endif // MEMORIJA_HPP_INCLUDED
