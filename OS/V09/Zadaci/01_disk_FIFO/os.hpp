#ifndef OS_HPP_INCLUDED
#define OS_HPP_INCLUDED

#include "dijagnostika.hpp"

#include <mutex>
#include <condition_variable>
#include <queue>
#include <cmath>

using namespace std;
using namespace chrono;

struct Zahtev {
    condition_variable cv;
    int id;
    int staza;
    bool obradjen;
    Zahtev(int id, int staza) : id(id), staza(staza), obradjen(false) {}
};

class OS {
private:
    Dijagnostika& dijagnostika;
    int ukupno_vreme;
    int trenutna_staza;
    mutex m;
    condition_variable cv;
    bool zavrseno;

    queue<shared_ptr<Zahtev>> zahtevi;

public:
    OS(Dijagnostika& d, int t) : dijagnostika(d), trenutna_staza(t) {
        ukupno_vreme = 0;
        zavrseno = false;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se uputio zahtev ka U/I uređaju
    //
    // id_procesa - ID procesa koji upućuje zahtev
    // broj_staze - broj staze diska kojoj nit želi da pristupi
    //
    // Metoda treba da formira novi zahtev i uputi ga U/I uređaju na obradu. Proces će biti blokiran dok god se ovaj zahtev ne izvrši. Pre nego što stupi u blokadu, potrebno je pozvati dijagnostika.proces_ceka.
    void uputi_UI_zahtev(int id_procesa, int broj_staze) {
        unique_lock<mutex> lock(m);

        shared_ptr<Zahtev> zahtev = make_shared<Zahtev>(id_procesa, broj_staze);
        zahtevi.push(zahtev);

        while (!zahtev->obradjen && !zavrseno) {
            dijagnostika.proces_ceka(id_procesa, broj_staze);
            cv.notify_one();
            zahtev->cv.wait(lock);
        }
    }

    // Metoda koju poziva nit koja simulira deo operativnog sistema koji upravlja diskom, kako bi se obradio jedan pristigli zahtev
    //
    // Prema uslovima zadatka, metoda treba da obradi zahtev koji je najranije pristigao.
    //
    // Na kraju simulacije, treba ispisati na standardni izlaz ukupno utroseno vreme u ms.
    //
    // Povratna vrednost metode treba da bude broj staze koji je obrađen.
    int obradi_zahtev() {
        unique_lock<mutex> lock(m);

        while (zahtevi.empty() && !zavrseno) {
            cv.wait(lock);
        }

        shared_ptr<Zahtev> zahtev = zahtevi.front();
        zahtev->obradjen = true;
        zahtev->cv.notify_one();
        int vreme = 10 * abs(trenutna_staza - zahtev->staza);
        trenutna_staza = zahtev->staza;
        ukupno_vreme += vreme;

        lock.unlock();
        this_thread::sleep_for(milliseconds(vreme));
        lock.lock();
        zahtevi.pop();
        return trenutna_staza;
    }

    // Metoda koja vraca sumu svih vremena potrosenih za obradu zahteva
    int dobaviUkupnoTrajanje() {
        unique_lock<mutex> lock(m);
        return ukupno_vreme;
    }

    // Metoda koja postavlja signal za kraj izvršavanja i pokreće obrađivač iz čekanja kako bi program mogao da se završi
    void zavrsi() {
        unique_lock<mutex> lock(m);
        zavrseno = true;
    }
};

#endif // OS_HPP_INCLUDED
