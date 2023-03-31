/*
Napisati konkurentni program koji stvara 2 niti od funkcije f. Funkcija f treba da prolazi kroz petlju dužine 10000 elemenata i ispisuje parne ili neparne brojeve (među tih 10000 elemenata).

Ispis parnih ili neparnih brojeva se vrši pozivom funkcija ispisi_parne i ispisi_neparne. U funkciji ispisi_parne prvo se pre ispisa zaključava muteks m1, a potom muteks m2. U funkciji ispisi_neparne prvo se pre ispisa zaključava muteks m2, a potom muteks m1.

Sva zaključavanja se vrše kroz objekte klase unique_lock.

Pratiti izvršavanje programa.
*/

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
std::mutex m2;

void ispis_parne(int x) {
    std::unique_lock<std::mutex> lock1(m1);
    std::unique_lock<std::mutex> lock2(m2);
    std::cout << x << " ";
}

void ispis_neparne(int x) {
    std::unique_lock<std::mutex> lock1(m2);
    std::unique_lock<std::mutex> lock2(m1);
    std::cout << x << " ";
}

void f(int n) {
    for (int i = 0; i < n; i++) {
        if (i % 2)
            ispis_parne(i);
        else
            ispis_neparne(i);
    }
}

int main() {
    int n = 10000;
    std::thread nit1 = std::thread(f, n);
    std::thread nit2 = std::thread(f, n);
    nit1.join();
    nit2.join();
    return 0;
}