#ifndef OS_HPP_INCLUDED
#define OS_HPP_INCLUDED

#include "dijagnostika.hpp"

#include <mutex>
#include <condition_variable>
#include <vector>
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
    mutex m;
    condition_variable cv;
    int trenutna_staza;
    bool zavrseno;
    int ukupno_vreme;
    vector<shared_ptr<Zahtev>> zahtevi;
public:
    OS(Dijagnostika& d, int t) : dijagnostika(d), trenutna_staza(t) {
        zavrseno = false;
        ukupno_vreme = 0;
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

        zahtevi.push_back(zahtev);

        while (!zahtev->obradjen) {
            dijagnostika.proces_ceka(id_procesa, broj_staze);
            cv.notify_one();
            zahtev->cv.wait(lock);
        }
    }

    // Metoda koju poziva nit koja simulira deo operativnog sistema koji upravlja diskom, kako bi se obradio jedan pristigli zahtev
    //
    // Prema uslovima zadatka, metoda treba da obradi zahtev kojim se pristupa onoj stazi koja je najbliža stazi na kojoj je trenutno glava diska
    //
    // Povratna vrednost metode treba da bude broj staze koji je obrađen.
    int obradi_zahtev() {
        unique_lock<mutex> lock(m);

        while (zahtevi.empty()) {
            cv.wait(lock);
        }

        int najmanji = 99999;
        // potencijalno malo sporo za puno zahteva?
        auto i = zahtevi.begin();
        for (auto it = zahtevi.begin(); it != zahtevi.end(); it++) {
            if (abs((*it)->staza - trenutna_staza) < najmanji) {
                najmanji = abs((*it)->staza - trenutna_staza);
                i = it;
            }
        }

        shared_ptr<Zahtev> zahtev = *i;
        zahtev->cv.notify_one();
        zahtev->obradjen = true;
        int vreme = 10 * abs(trenutna_staza - zahtev->staza);
        trenutna_staza = zahtev->staza;
        zahtevi.erase(i);

        lock.unlock();
        this_thread::sleep_for(milliseconds(vreme));
        lock.lock();

        ukupno_vreme += vreme;

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
