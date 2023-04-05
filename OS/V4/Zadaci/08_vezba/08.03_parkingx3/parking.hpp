#ifndef PARKING_HPP_INCLUDED
#define PARKING_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "automobil.hpp"

using namespace std;

class Parking {
    Automobil& automobil;
    int next_entrance;
    mutex m;
    condition_variable cv;
    bool free;
public:
    Parking(Automobil& a) : automobil(a) {
        // Prosiriti po potrebi ...
        next_entrance = 0;
        free = true;
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada on pokusava da udje na parking.
    // Metoda je blokirajuca - ukoliko nema slobodnog mesta, izvrsenje je u blokadi dok se ono ne oslobodi.
    //
    // rbr  - Redni broj automobila
    // ulaz - Ulaz na koji automobil pokusava da udje
    //
    // Potrebno je pozvati metodu automobil.ceka kada automobil ne moze da pridje parkingu i mora da ceka.
    // Potrebno je pozvati metodu automobil.zauzima kada automobil zauzme parking mesto.
    void udji(int rbr, int ulaz) {
        // Implementirati ...
        unique_lock<mutex> lock(m);

        while (!free || ulaz != next_entrance) {
            automobil.ceka(rbr, ulaz);
            cv.wait(lock);
        }

        free = false;
        automobil.zauzima(rbr);
        next_entrance = (ulaz + 1) % 3;
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada on napusta parking na koji je prethodno usao.
    //
    // rbr  - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada automobil napusti parking mesto.
    void izadji(int rbr) {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        cv.notify_all();
        automobil.napusta(rbr);
        free = true;
    }
};

#endif // PARKING_HPP_INCLUDED
