#ifndef SKLADISTE_HPP_INCLUDED
#define SKLADISTE_HPP_INCLUDED

#include "kamion.hpp"
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

class Skladiste {
private:
    Kamion& kamion;
    mutex m;
    condition_variable normal;
    condition_variable boom;
    int zapaljivih_ceka;
    bool slobodno[2];
public:
    Skladiste(Kamion& k) : kamion(k), zapaljivih_ceka(0) {
        // Prosiriti po potrebi ...
        slobodno[0] = true;
        slobodno[1] = true;
    }

    // Metoda koju poziva nit koja simulira kretanje kamiona kada on pokusava da istovari robu.
    // Metoda je blokirajuca - ako su sve rampe za istovar zauzete, izvrsenje ce blokirati dok se neka ne oslobodi.
    //
    // rbr       - Redni broj kamiona
    // kolicina  - Kolicina robe koja se prevozi (u tonama)
    // zapaljivo - Ukazuje na to da li je roba koja se prevozi zapaljiva (takva roba ima prioritet pri istovaru!)
    //
    // Potrebno je pozvati metodu kamion.ceka kada su rampe zauzete i kamion mora da ceka.
    // Potrebno je pozvati metodu kamion.istovara kada zapocne istovar robe iz kamiona (primetiti da ta metoda zahteva da joj se prosledi indeks rampe na kojoj se obavlja istovar!)
    // Potrebno je pozvati metodu kamion.odlazi kada je kamion zavrsio istovar i odlazi.
    void istovari(int rbr, int kolicina, bool zapaljivo) {
        unique_lock<mutex> lock(m);

        while(!slobodno[0] && !slobodno[1]) {
            kamion.ceka(rbr, kolicina, zapaljivo);
            if(zapaljivo) {
                zapaljivih_ceka++;
                boom.wait(lock);
            } else
                normal.wait(lock);
        }

        int rampa = slobodno[0] ? 0 : 1;
        slobodno[rampa] = false;

        kamion.istovara(rbr, kolicina, zapaljivo, rampa + 1);
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(kolicina * 1000));
        lock.lock();

        if (zapaljivo) {
            zapaljivih_ceka--;
        }

        slobodno[rampa] = true;
        if(zapaljivih_ceka != 0)
            boom.notify_one();
        else
            normal.notify_one();
        kamion.odlazi(rbr);
    }
};

#endif // SKLADISTE_HPP_INCLUDED
