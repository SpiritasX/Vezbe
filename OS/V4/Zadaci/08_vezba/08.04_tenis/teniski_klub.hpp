#ifndef TENISKI_KLUB_HPP_INCLUDED
#define TENISKI_KLUB_HPP_INCLUDED

#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>

#include "podaci.hpp"
#include "mec.hpp"

#define MAX_TERENA 30

using namespace std;
using namespace chrono;

class Teniski_klub {                             //Klasa deljenog resursa. Pravi se maksimalno 30 terena, ali ce u realnosti biti samo 3 terena.
private:
    Mec& mec;
    mutex m;
    condition_variable *cv;
    bool *free;
    default_random_engine gen;
    uniform_int_distribution<int> uid;
public:
    Teniski_klub(Mec& m, int ukupno_terena) : mec(m), uid(1000, 5000) {
        // Prosiriti po potrebi ...
        gen.seed(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());
        cv = new condition_variable[ukupno_terena];
        free = new bool[ukupno_terena];

        for (int i = 0; i < ukupno_terena; i++)
            free[i] = true;
    }

    // Metoda koju poziva nit koja simulira mec kako bi izvrsila teniski mec.
    // Metoda je blokirajuca - ako je zeljeni teren zauzet, izvrsenje ce blokirati dok se on ne oslobodi.
    //
    // broj_meca - Redni broj meca
    // na_terenu - Indeks terena na kojem mec treba da se odigra
    //
    // Potrebno je pozvati metodu mec.ceka kada je izabrani teren zauzet i mec mora da ceka.
    // Potrebno je pozvati metodu mec.pocinje kada se isprazni izabrani teren i mec moze da pocne.
    // Potrebno je pozvati metodu mec.zavrsen kada se mec zavrsi i mogu se proslediti izmereni vremenski intervali.
    void odigraj_mec(int broj_meca, int na_terenu) {
        // Implementirati ...
        Podaci p;
        p.dosao = high_resolution_clock::now();
        {
            unique_lock<mutex> lock(m);

            while(!free[na_terenu]) {
                mec.ceka(broj_meca, na_terenu);
                cv[na_terenu].wait(lock);
            }
            free[na_terenu] = false;
            mec.pocinje(broj_meca, na_terenu);
        }
        p.pocetak = high_resolution_clock::now();
        this_thread::sleep_for(milliseconds(uid(gen)));
        p.trajanje = high_resolution_clock::now() - p.pocetak;
        {
            unique_lock<mutex> lock(m);
            mec.zavrsen(broj_meca, p);
            free[na_terenu] = true;
            cv[na_terenu].notify_one();
        }
    }
};

#endif // TENISKI_KLUB_HPP_INCLUDED
