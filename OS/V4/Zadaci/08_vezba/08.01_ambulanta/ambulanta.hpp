#ifndef AMBULANTA_HPP_INCLUDED
#define AMBULANTA_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "student.hpp"

using namespace std;

class Studentska_ambulanta {
private:
    Student& student;
    mutex mtx;
    condition_variable cv;
    const int max_m;
    const int max_f;
    int m;
    int f;
public:
    Studentska_ambulanta(Student& st, int muskih, int zenskih) : student(st), max_m(muskih), max_f(zenskih) {
        // Prosiriti po potrebi ...
        this->m = 0;
        this->f = 0;
    }

    // Metoda koju poziva nit koja simulira studenta u ambulanti kada student pokusava da udje u nju.
    // Ukoliko je ambulanta zauzeta, izvrsenje ove metode ce cekati da se ona oslobodi.
    //
    // rbr - Redni broj studenta
    // p   - Pol studenta
    //
    // Potrebno je pozvati metodu student.ceka kada student ne moze da stupi u ambulantu.
    // Potrebno je pozvati metodu student.ulazi kada student udje u ambulantu.
    void udji(int rbr, Pol p) {
        // Implementirati ...
        unique_lock<mutex> lock(mtx);

        int pol = (p == Pol::MUSKI) ? m : f;
        int max_pol = (p == Pol::MUSKI) ? max_m : max_f;

        while (pol >= max_pol) {
            student.ceka(rbr, p);
            cv.wait(lock);
            pol = (p == Pol::MUSKI) ? m : f;
        }

        pol++;
        if (p == Pol::MUSKI)
            m = pol;
        else
            f = pol;
        
        student.ulazi(rbr, p);
    }

    // Metoda koju poziva nit koja simulira studenta u ambulanti nakon sto je student pregledan i izlazi iz nje.
    //
    // rbr - Redni broj studenta
    // p   - Pol studenta
    void izadji(int rbr, Pol p) {
        // Implementirati ...
        unique_lock<mutex> lock(mtx);

        if (p == Pol::MUSKI)
            m--;
        else
            f--;

        cv.notify_one();
    }
};

#endif // AMBULANTA_HPP_INCLUDED
