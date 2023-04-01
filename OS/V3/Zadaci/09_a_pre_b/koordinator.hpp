#ifndef KOORDINATOR_HPP_INCLUDED
#define KOORDINATOR_HPP_INCLUDED

#include <condition_variable>
#include <mutex>
#include <chrono>

using namespace std;

class Koordinator {
    bool finished = false;
    condition_variable cv;
    mutex m;
public:
    // Funkcija se poziva nakon što je prva nit završila svoj posao, kako bi signalizirala pokretanje druge niti.
    void prvi_zavrsio() {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        cv.notify_one();
        finished = true;
    }

    // Blokirajuća funkcija koja se poziva na početku druge niti kako bi nit čekala dok se prva nit ne završi.
    void drugi_ceka() {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        while (!finished)
            cv.wait(lock);
    }
};

#endif // KOORDINATOR_HPP_INCLUDED
