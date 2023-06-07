#ifndef OS_HPP_INCLUDED
#define OS_HPP_INCLUDED

#include "dijagnostika.hpp"
#include "proces.hpp"

#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>

using namespace std;

struct UI_ZAHTEV {
    condition_variable cv;
    int id;
    bool odradjen;
    UI_ZAHTEV(int id) : id(id), odradjen(false) {}
};

class OS {
private:
    Dijagnostika& dijagnostika;
    int maks_uzastopnih_i;
    int aktivan_proces;
    mutex m;
    condition_variable cv;
    condition_variable ui_cv;
    queue<shared_ptr<UI_ZAHTEV>> ui_zahtevi;
	default_random_engine dr;
    bool zavrseno;

public:
    // d                 - Referenca na objekat Dijagnostika, koji služi za ispis stanja simulacije
    // maks_uzastopnih_i - Maksimalan dozvoljen broj uzastopnih STANDARD instrukcija, nakon kojeg obavezno sledi preključivanje
    OS(Dijagnostika& d, int maks_uzastopnih_i) : dijagnostika(d), maks_uzastopnih_i(maks_uzastopnih_i) {
	    dr.seed(chrono::steady_clock::now().time_since_epoch().count());
        zavrseno = false;
        aktivan_proces = 0;
    }

    // Pomoćna metoda koja vraća objekat klase Dijagnostika koji služi za ispis stanja simulacije
    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira proces kako bi se izvršile sve instrukcije procesa.
    //
    // p - Struktura koja sadrži opis procesa (ID procesa i instrukcije koje treba izvršiti)
    //
    // Ukoliko proces ne može da se izvrši (procesor je zauzet), proces mora da se uveže u red spremnih i treba pozvati metodu dijagnostika.proces_ceka.
    // Ukoliko dođe do toga da izvršenje procesa prestaje (dostignut je maksimalan dozvoljen broj uzastopnih STANDARD instrukcija ili su sve instrukcije procesa izvršene), potrebno je pozvati dijagnostika.proces_oslobadja_procesor.
    // Kada se izvrši STANDARD instrukcija nekog procesa, potrebno je pozvati dijagnostika.proces_izvrsio_standardnu.
    // Kada se izvršava UI instrukcija, potrebno je pozvati par metoda: dijagnostika.proces_ceka_na_UI kada se pokrene U/I operacija (nakon čega sledi čekanje na U/I podsistem) i dijagnostika.proces_zavrsio_UI kada se završi U/I operacija.
	void izvrsi_proces(Proces& p) {
        uniform_int_distribution dist(10, 50);
        int broj_izvrsenih = 0;

        for (auto it = p.instrukcije.begin(); it != p.instrukcije.end(); it++) {
            unique_lock<mutex> lock(m);
            
            if (p.instrukcije.empty())
                break;
            
            while (aktivan_proces != p.id && aktivan_proces != 0) {
                dijagnostika.proces_ceka(p.id);
                cv.wait(lock);
            }

            aktivan_proces = p.id;

            if (*it == INS_TYPE::UI) {
                shared_ptr<UI_ZAHTEV> zahtev = make_shared<UI_ZAHTEV>(p.id);
                ui_zahtevi.push(zahtev);
                dijagnostika.proces_ceka_na_UI(p.id);

                ui_cv.notify_one();
                aktivan_proces = 0;
                broj_izvrsenih = 0;

                cv.notify_one();

                while (!zahtev->odradjen)
                    zahtev->cv.wait(lock);
                
                dijagnostika.proces_zavrsio_UI(p.id);
            } else {
                lock.unlock();
                this_thread::sleep_for(chrono::milliseconds(dist(dr)));
                lock.lock();
                dijagnostika.proces_izvrsio_standardnu(p.id);
                broj_izvrsenih++;
            
                if (broj_izvrsenih >= 3) {
                    dijagnostika.proces_oslobadja_procesor(p.id);
                    aktivan_proces = 0;
                    broj_izvrsenih = 0;
                    cv.notify_one();
                    lock.unlock();
                    this_thread::sleep_for(chrono::milliseconds(100));
                }
            }
        }
        dijagnostika.proces_oslobadja_procesor(p.id);
        aktivan_proces = 0;
	}

    // Metoda koju poziva nit koja simulira obrađivač U/I zahteva kako bi se obradili trenutno pohranjeni U/I zahtevi.
    //
    // Potrebno je pozvati dijagnostika.ui_ceka kada ne postoje trenutno pohranjeni U/I zahtevi i obrađivač čeka na prvi.
    // Potrebno je pozvati dijagnostika.ui_zapocinje kada obrađivač krene u obradu U/I zahteva. Kada obrađivač završi taj zahtev, potrebno je pozvati dijagnostika.ui_zavrsio.
	void obradi_zahteve() {
        while (!zavrseno) {
            unique_lock<mutex> lock(m);

            while (ui_zahtevi.empty() && !zavrseno) {
                dijagnostika.ui_ceka();
                ui_cv.wait(lock);
            }

            if (zavrseno)
                return;

            uniform_int_distribution dist(100, 300);

            shared_ptr<UI_ZAHTEV> zahtev = ui_zahtevi.front();
            ui_zahtevi.pop();

            dijagnostika.ui_zapocinje(zahtev->id);

            lock.unlock();
            this_thread::sleep_for(chrono::milliseconds(dist(dr)));
            lock.lock();

            dijagnostika.ui_zavrsio(zahtev->id);
            zahtev->odradjen = true;
            zahtev->cv.notify_one();
        }
	}


    // Metoda koja služi da se prekine beskonačna obrada zahteva od strane obrađivača U/I zahteva.
    void zavrsi() {
        unique_lock<mutex> lock(m);
        zavrseno = true;
        ui_cv.notify_one();
    }
};

#endif // OS_HPP_INCLUDED
