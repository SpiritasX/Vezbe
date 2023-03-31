#ifndef NITI_HPP_INCLUDED
#define NITI_HPP_INCLUDED

#include <vector>
#include <thread>

#include "suma_vektora.hpp"

using namespace std;

// v - vektor čije elemente treba sumirati
// n - koliko niti treba pokrenuti
// povratna vrednost - suma svih elemenata vektora, izračunata pokretanjem n niti (svaka nit treba da obradi jedan deo elemenata)
double sumiraj(vector<double> v, int n) {
    // Implementirati ...
    double zbir = 0;
    int pomeraj = (int)(v.size() / n) + 1;
    thread *niti = new thread[n];
    for (int i = 0; i < n; i++) {
        niti[i] = thread(f, v.begin() + i * pomeraj, v.begin() + (i + 1) * pomeraj, ref(zbir));
        niti[i].join();
    }
    return zbir;
}

#endif // NITI_HPP_INCLUDED
