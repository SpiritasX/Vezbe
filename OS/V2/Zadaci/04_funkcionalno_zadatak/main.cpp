/*
    Napraviti funkciju koja sortira dati vektor int-ova koristeći
    za određivanje da li je neki element manji ili veći od drugog
    prosleđenu funkciju. Demonstrirati ovo kroz lambda izraz.

    Bonus zadaci:
    1. Implementirati ovo da radi sa bilo kojim tipom kroz
    šablone.
    2. Implementirati ovo kroz quicksort algoritam.
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> a = { 1, 6, 5, 2, 0, 9 };

    for (auto i = a.begin(); i != a.end(); i++)
        std::cout << *i << " ";
    std::cout << std::endl;

    std::sort(a.begin(), a.end(), [](int a, int b){ return a < b; });

    for (int i : a)
        std::cout << i << " ";
    std::cout << std::endl;
}