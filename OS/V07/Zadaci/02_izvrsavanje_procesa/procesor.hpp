#ifndef PROCESOR_HPP_INCLUDED
#define PROCESOR_HPP_INCLUDED

#include "dijagnostika.hpp"

#include <mutex>
#include <condition_variable>

using namespace std;
using namespace chrono;

class Procesor {
private:
    Dijagnostika& dijagnostika;
    mutex m;
    condition_variable cv;
    condition_variable ui_cv;
    bool procesor_zauzet;
    bool iniciran_prekid;

public:
    Procesor(Dijagnostika& d) : dijagnostika(d) {
        procesor_zauzet = false;
        iniciran_prekid = false;
    }

    // Pomoćna metoda koja vraća referencu na objekat Dijagnostika asociran sa ovim objektom
    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira proces, kako bi se izvršile sve naredbe procesa.
    //
    // id           - id procesa
    // broj_naredbi - ukupan broj naredbi koje ovaj proces izvršava
    //
    // Ukoliko je procesor već zauzet i ne mogu se izvršavati naredbe procesa, potrebno je pozvati metodu dijagnostika.proces_ceka a nakon toga proces treba da pređe u stanje čekanja.
    // Kada proces uspe da zauzme procesor, pre izvršenja naredbe treba da se pozove dijagnostika.proces_izvrsava.
    // Nakon što je proces izvršio naredbu, potrebno je pozvati dijagnostika.proces_zavrsio.
    void izvrsi_proces(int id, int broj_naredbi) {
        for (int i = 0; i < broj_naredbi; i++) {
            unique_lock<mutex> lock(m);

            while (procesor_zauzet) {
                dijagnostika.proces_ceka(id);
                cv.wait(lock);
            }
            
            dijagnostika.proces_izvrsava(id, i);

            procesor_zauzet = true;

            lock.unlock();
            this_thread::sleep_for(seconds(1));
            lock.lock();

            procesor_zauzet = false;
            
            dijagnostika.proces_zavrsio(id, i);

            if (iniciran_prekid)
                ui_cv.notify_one();
            else
                cv.notify_one();

            lock.unlock();
            this_thread::sleep_for(milliseconds(100));
        }
    }

    // Metoda koju poziva nit koja simulira obrađivač U/I prekida kako bi se inicirao i obradio prekid.
    //
    // Ukoliko je procesor već zauzet i ne može se obaviti obrađivanje prekida, potrebno je pozvati metodu dijagnostika.obradjivac_ceka a nakon toga obrađivač treba da pređe u stanje čekanja, dok se procesor ne oslobodi.
    // Kada obrađivač uspe da zauzme procesor, pre obrade prekida treba da se pozove dijagnostika.obradjivac_izvrsava.
    // Nakon što je obrađivač završio obradu, potrebno je pozvati dijagnostika.obradjivac_zavrsio.
    void prekini() {
        unique_lock<mutex> lock(m);
        iniciran_prekid = true;

        while (procesor_zauzet) {
            dijagnostika.obradjivac_ceka();
            ui_cv.wait(lock);
        }

        dijagnostika.obradjivac_izvrsava();

        procesor_zauzet = true;

        lock.unlock();
        this_thread::sleep_for(milliseconds(300));
        lock.lock();

        procesor_zauzet = false;

        dijagnostika.obradjivac_zavrsio();

        cv.notify_one();
        iniciran_prekid = false;
    }
};

#endif // PROCESOR_HPP_INCLUDED
