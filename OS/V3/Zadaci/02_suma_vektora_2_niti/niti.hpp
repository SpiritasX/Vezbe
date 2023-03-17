#ifndef NITI_HPP_INCLUDED
#define NITI_HPP_INCLUDED

#include <vector>
#include <thread>

#include "suma_vektora.hpp"

using namespace std;

// v - vektor čije elemente treba sumirati
// povratna vrednost - suma svih elemenata vektora, izračunata pokretanjem 2 niti (svaka treba da obradi jednu polovinu elemenata)
double sumiraj(vector<double> v) {
    // Implementirati ...

    ci half = v.begin() + v.size() / 2;

    double zbir1 = 0, zbir2 = 0;

    thread nit1(f, v.begin(), half, ref(zbir1));
    nit1.join();
    thread nit2(f, half, v.end(), ref(zbir2));
    nit2.join();

    return zbir1 + zbir2;
}

#endif // NITI_HPP_INCLUDED
