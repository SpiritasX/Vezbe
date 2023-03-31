#ifndef NITI_HPP_INCLUDED
#define NITI_HPP_INCLUDED

#include <vector>
#include <thread>

#include "suma_vektora.hpp"

using namespace std;

// v - vektor A čije elemente treba sumirati
// v - vektor B čije elemente treba sumirati
// povratna vrednost - suma korespondentnih elemenata vektora A i B, izračunata pozivanjem dve niti
vector<double> sumiraj(vector<double> a, vector<double> b) {
    // Implementirati ...
    vector<double> zbir(a.size());
    thread nit1 = thread(f, a.begin(), a.begin() + (int)(a.size() / 2), b.begin(), zbir.begin());
    thread nit2 = thread(f, a.begin() + (int)(a.size() / 2), a.end(), b.begin() + (int)(b.size() / 2), zbir.begin() + (int)(zbir.size() / 2));
    nit1.join();
    nit2.join();
    return zbir;
}

#endif // NITI_HPP_INCLUDED
