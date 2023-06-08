#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "dijagnostika.hpp"
#include "naredba.hpp"
#include "povratna_vrednost.hpp"

#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;
using namespace chrono;

struct Zahtev {
    int kolicina;
    condition_variable cv;
    Zahtev(int kolicina) : kolicina(kolicina) {}
};

class Program {
private:
    Dijagnostika& dijagnostika;
    int slobodno_ram;
    int zauzeto_virtuelna;
    condition_variable vm;
    mutex m;
    bool zavrsen;

    queue<shared_ptr<Zahtev>> zahtevi;

    void _malloc(int kolicina) {
        unique_lock<mutex> lock(m);

        if (slobodno_ram < kolicina) {
            vm.notify_one();
            shared_ptr<Zahtev> zahtev = make_shared<Zahtev>(kolicina);
            zahtevi.push(zahtev);
            zahtev->cv.wait(lock);
        } else
            slobodno_ram -= kolicina;
        this_thread::sleep_for(seconds(1));
    }

public:
    Program(Dijagnostika& d, int kapacitet) : dijagnostika(d), slobodno_ram(kapacitet) {
        zauzeto_virtuelna = 0;
        zavrsen = false;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje programa, kako bi zauzela potrebnu memoriju
    //
    // naredba - naredba koja se izvršava (naredba kojom se zauzima memorija)
    // Vraća instancu klase Povratna_vrednost koja sadrži opis zauzeća memorije NAKON izvršenja naredbe.
    Povratna_vrednost izvrsi_naredbu(Naredba naredba) {
        // unique_lock<mutex> lock(m);
        for (int i = 0; i < naredba.ponavljanja; i++) {
            _malloc(naredba.kolicina_memorije);
        }
        return {slobodno_ram, zauzeto_virtuelna};
    }

    // Metoda koju poziva nit koja simulira deo operativnog sistema koji se bavi zauzimanjem virtuelne memorije kako bi se zauzela određena količina VM
    // Potrebnu količinu VM (kao i bilo koju drugu neophodnu informaciju) preneti u nekom izabranom polju klase.
    int zauzmi_virtuelnu_memoriju() {
        unique_lock<mutex> lock(m);
        
        while (zahtevi.empty() && !zavrsen)
            vm.wait(lock);
        
        if (zavrsen)
            return zauzeto_virtuelna;

        this_thread::sleep_for(seconds(1));
        zauzeto_virtuelna += zahtevi.front()->kolicina;
        zahtevi.front()->cv.notify_one();
        zahtevi.pop();
        return zauzeto_virtuelna;
    }

    void zavrsi() {
        unique_lock<mutex> lock(m);
        zavrsen = true;
        vm.notify_all();
    }
};

#endif // PROGRAM_HPP_INCLUDED
