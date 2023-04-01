#ifndef PARKING_HPP_INCLUDED
#define PARKING_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "automobil.hpp"

using namespace std;

class Parking {
private:
    Automobil& automobil;
    condition_variable cv;
    mutex m;
    const int kapacitet;
    int taken;
public:
    Parking(Automobil& a, int kapacitet) : automobil(a), kapacitet(kapacitet) {
        // Proširiti po potrebi ...
        taken = 0;
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kako bi automobil pokušao da se parkira.
    // Ako je parking zauzet, izvršenje ove metode će trajati dok se parking ne oslobodi i auto se parkira.
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.ceka kada je parking zauzet i auto ne može da se parkira.
    // Potrebno je pozvati metodu automobil.parkira kada auto uspe da se parkira.
    void udji(int rbr) {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        while (taken == kapacitet) {
            automobil.ceka(rbr);
            cv.wait(lock);
        }
        automobil.parkira(rbr);
        taken++;
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada auto izlazi sa parkinga (nakon što je bio parkiran).
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada auto napušta parking mesto.
    void izadji(int rbr) {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        automobil.napusta(rbr);
        cv.notify_one();
        taken--;
    }
};

#endif // PARKING_HPP_INCLUDED
