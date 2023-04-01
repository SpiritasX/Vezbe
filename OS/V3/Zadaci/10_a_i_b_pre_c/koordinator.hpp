#ifndef KOORDINATOR_HPP_INCLUDED
#define KOORDINATOR_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

using namespace std;

class Koordinator {
private:
    const int cekam_niti;     // Konstanta koja govori koliko niti se čeka na završetak pre nego što se aktivira poslednja.
    mutex m;
    condition_variable cv;
    int num = 0;
public:
    Koordinator(int cn) : cekam_niti(cn) {
        // Proširiti po potrebi ...
    }

    // Metoda koju na svom KRAJU zovu niti (a i b) koje ne čekaju (izvršavaju se odmah).
    void zavrsio() {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        num++;
        if (num == cekam_niti)
            cv.notify_one();
    }

    // Metodu koju na svom POČETKU zovu niti (c) koje čekaju (ne izvršavaju se odmah).
    void cekam() {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        while (num != cekam_niti)
            cv.wait(lock);
    }
};

#endif // KOORDINATOR_HPP_INCLUDED
