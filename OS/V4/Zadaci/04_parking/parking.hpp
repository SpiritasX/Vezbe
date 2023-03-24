#ifndef PARKING_HPP_INCLUDED
#define PARKING_HPP_INCLUDED

#include "automobil.hpp"
#include <mutex>
#include <condition_variable>

using namespace std;

enum Stanje {
    SLOBODAN,
    ZAUZET
};

class Parking {
private:
    Automobil& automobil;
    Stanje stanje;
    mutex m;
    condition_variable slobodan;
public:
    Parking(Automobil& a) : automobil(a), stanje(SLOBODAN) {
        // Proširiti po potrebi ...
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
        automobil.ceka(rbr);
        unique_lock<mutex> lock(m);
        // Mora biti while iako mi sami uvek pozivamo notify_one na dobar nacin
        // Lazno budjenje moze da se desi
        // wait_for
        while (stanje == Stanje::ZAUZET)
            slobodan.wait(lock);
        stanje = Stanje::ZAUZET;
        automobil.parkira(rbr);
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
        stanje = Stanje::SLOBODAN;
        slobodan.notify_one();
    }
};

#endif // PARKING_HPP_INCLUDED
