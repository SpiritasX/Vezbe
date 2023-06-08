#ifndef RADNA_MEMORIJA_HPP_INCLUDED
#define RADNA_MEMORIJA_HPP_INCLUDED

#include "dijagnostika.hpp"

#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;
using namespace chrono;

class Radna_memorija {
private:
    Dijagnostika& dijagnostika;
    vector<int> memorija;
    mutex m;
    condition_variable cv;
    int kraj_zauzete;
    int velicina;
    int slobodno;

public:
    Radna_memorija(Dijagnostika& d, int ukupno_lokacija) : dijagnostika(d), velicina(ukupno_lokacija), slobodno(ukupno_lokacija) {
        // Proširiti po potrebi ...
        memorija = vector<int>(ukupno_lokacija);
        kraj_zauzete = 0;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje procesa kako bi proces zauzeo potrebnu memoriju i krenuo sa radom
    //
    // id_procesa          - identifikator procesa
    // br_lokacija_procesa - ukupan broj lokacija memorije koje su neophodne za izvršenje procesa
    // trajanje            - koliko dugo se proces izvršava (u sekundama)
    //
    // Ukoliko trenutno nema na raspolaganju dovoljno slobodne memorije (moraju se zauzeti uzastopni okviri u memoriji!), potrebno je pozvati metodu dijagnostika.proces_ceka a nakon toga proces treba da čeka dok se memorija ne oslobodi.
    // Kada proces uspe da dođe do potrebne radne memorije, treba da se pozove dijagnostika.proces_zauzeo_okvire.
    // Kada se proces završi, potrebno je pozvati metodu dijagnostika.proces_zavrsio.
    // Metodu dijagnostika.ispisi_memoriju potrebno je pozvati u sledećim momentima: nakon što proces zauzme memoriju i nakon što proces oslobodi memoriju.
    void koristi(int id_procesa, int br_lokacija_procesa, int trajanje) {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        
        while(memorija.size() - kraj_zauzete < br_lokacija_procesa) {
            dijagnostika.proces_ceka(id_procesa);
            cv.wait(lock);
        }

        auto it = memorija.begin() + kraj_zauzete;
        for (int i = 0; i < br_lokacija_procesa; i++) {
            *it = id_procesa;
            it++;
        }

        dijagnostika.proces_zauzeo_okvire(id_procesa, kraj_zauzete, kraj_zauzete + br_lokacija_procesa);
        dijagnostika.ispisi_memoriju(memorija.begin(), memorija.end());

        lock.unlock();
        this_thread::sleep_for(seconds(trajanje));
        lock.lock();

        it = memorija.begin();

        while (*it != id_procesa) it++;

        for (int i = 0; i < br_lokacija_procesa; i++) {
            *it = 0;
            it++;
        }

        dijagnostika.proces_zavrsio(id_procesa);
        dijagnostika.ispisi_memoriju(memorija.begin(), memorija.end());
    }

    // Metoda koju poziva nit operativnog sistema koji se bavi sažimanjem memorije
    //
    // Nakon što je sažimanje obavljeno potrebno je pozvati metodu dijagnostika.sazimanje_obavljeno a nakon toga i metodu dijagnostika.ispisi_memoriju kako bi se prikazali efekti sažimanja memorije.
    void sazimanje() {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        vector<int> buffer(memorija.size());
        auto buf = buffer.begin();
        kraj_zauzete = 0;
        for (auto it = memorija.begin(); it != memorija.end(); it++) {
            if (*it != 0) {
                *buf = *it;
                buf++;
                kraj_zauzete++;
            }
        }
        memorija = buffer;
        cv.notify_all();
    }
};

#endif // RADNA_MEMORIJA_HPP_INCLUDED
