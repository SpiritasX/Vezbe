#ifndef PARKING_HPP_INCLUDED
#define PARKING_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "automobil.hpp"

using namespace std;

class Parking {
private:
    Automobil& automobil;
    mutex m;
    condition_variable cv;
    bool zauzet;
public:
    Parking(Automobil& a) : automobil(a) {
        // Proširiti po potrebi ...
        zauzet = false;
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kako bi automobil pokušao da se parkira.
    // Ako je parking zauzet, izvršenje ove metode će trajati dok se parking ne oslobodi i auto se parkira.
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.ceka kada je parking zauzet i auto mora da čeka.
    // Potrebno je pozvati metodu automobil.parkira kada auto uspe da se parkira.
    void udji(int rbr) {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        automobil.ceka(rbr);
        while (zauzet)
            cv.wait(lock);
        
        automobil.parkira(rbr);
        zauzet = true;
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada auto izlazi sa parkinga (nakon što je bio parkiran).
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada auto napušta parking mesto.
    void izadji(int rbr) {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        cv.notify_one();
        zauzet = false;
        automobil.napusta(rbr);
    }
};

#endif // PARKING_HPP_INCLUDED
