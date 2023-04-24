/**
 * Napisati C++ program koji cita podatke o uniformnim distribucijama iz ulazne datoteke i potom za
 * svaku distribuciju generise po 10 brojeva, racuna njihov prosek, i nalazi najmanji i najveci broj. 
 * 
 * U ulaznoj datoteci "distribucije.txt" se u svakom redu nalaze informacije o donjoj i gornjoj granici
 * intervala u kojem treba generisati brojeve. Informacije o gornjoj i donjoj granici su odvojene dvotackom.
 *  U pitanju su razlomljeni brojevi.
 * 
 * U izlaznoj datoteci "brojevi.csv" treba da se nalaze u jednom redu odvojeni zarezom prvo 10 
 * izgenerisanih brojeva a potom i prosek, najmanji element i najveci element.
 * 
 * Treba napraviti jednu nit koja ce samo citati ulazne podatke, jednu nit koja ce samo pisati gotove
 * brojeve u datoteku i 6 niti radnika koji ce na osnovu podataka iz ulazne datoteke generisati sve
 * neophodno za ispis u izlaznu datoteku.
*/

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <condition_variable>
#include <queue>

using namespace std;

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class UlazniPodaci {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    int br_radnika;
    condition_variable cv;
    bool kraj;
    queue<T> red;
public:
    UlazniPodaci(): kraj(false), br_radnika(0) {}  // na pocetku nije kraj i nema radnika

    void dodaj(T par) {
        unique_lock<mutex> lock(podaci_mx);
        red.push(par);
        cv.notify_one();
    }

    bool skloni(T &par) {
        unique_lock<mutex> lock(podaci_mx);

        while(red.empty() && !kraj)
            cv.wait(lock);
        
        if (red.empty())
            return false;
        
        par = red.front();
        red.pop();
        return true;
    }

    void prijaviSe() {
        unique_lock<mutex> lock(podaci_mx);
        br_radnika++;
    }

    void odjaviSe() {
        unique_lock<mutex> lock(podaci_mx);
        br_radnika--;
        if (br_radnika == 0) {
            kraj = true;
            cv.notify_all();
        }
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti pisaci u kolekciju su se odjavili.
    */
    bool jeLiKraj() {
        return red.empty() && kraj;
    }
};


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class IzlazniPodaci {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    bool kraj;
    int br_radnika;
    condition_variable cv;
    queue<T> red;
public:
    IzlazniPodaci(): kraj(false), br_radnika(0) {}  // na pocetku nije kraj i nema radnika

    void dodaj(T par) {
        unique_lock<mutex> lock(podaci_mx);
        red.push(par);
        cv.notify_one();
    }

    bool skloni(T &par) {
        unique_lock<mutex> lock(podaci_mx);

        while(red.empty() && !kraj)
            cv.wait(lock);
        
        if (red.empty())
            return false;
        
        par = red.front();
        red.pop();
        return true;
    }

    void prijaviSe() {
        unique_lock<mutex> lock(podaci_mx);
        br_radnika++;
    }

    void odjaviSe() {
        unique_lock<mutex> lock(podaci_mx);
        br_radnika--;
        if (br_radnika == 0) {
            kraj = true;
            cv.notify_all();
        }
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti pisaci u kolekciju su se odjavili.
    */
    bool jeLiKraj() {
        return red.empty() && kraj;
    }
};


/**
 * Logika radnika - niti koje vrse transformaciju ulaznih podataka u izlazne podatke spremne za ispis.
*/
void radnik(UlazniPodaci<pair<double, double>> &ulaz, IzlazniPodaci<vector<double>> &izlaz) {
    izlaz.prijaviSe();
    pair<double, double> par;
    vector<double> v;
    random_device rd;
    mt19937 gen(rd());

    while(ulaz.skloni(par)) {
        uniform_real_distribution<> dis(par.first, par.second);
        for(int i = 0; i < 10; i++)
            v.push_back(dis(gen));
        auto max = v.begin();
        auto min = v.begin();
        double avg = 0;
        for(auto i = v.begin(); i != v.end(); i++)
        {
            avg += *i;
            if (*i < *min)
                min = i;
            if (*i > *max)
                max = i;
        }
        avg /= v.size();

        v.push_back(avg);
        v.push_back(*min);
        v.push_back(*max);

        izlaz.dodaj(v);
    }
    izlaz.odjaviSe();
}

/**
 * Logika citaca_iz_datoteke - nit koja radi citanje iz ulazne datoteke i salje u ulaznu kolekciju za radnike
*/
void citacf(string ime_ulazne_dat, UlazniPodaci<pair<double, double>> &ulaz) {
    ulaz.prijaviSe();
    ifstream input(ime_ulazne_dat);
    pair<double, double> par;
    while (!input.eof()) {
        input >> par.first >> par.second;
        ulaz.dodaj(par);
    }
    ulaz.odjaviSe();
}

/**
 * Logika pisaca_u_datoteku - nit koja radi pisanje u izlaznu datoteku podataka dobijenih od radnika
*/
void pisacf(IzlazniPodaci<vector<double>> &izlaz, string ime_izlazne_dat) {
    ofstream file(ime_izlazne_dat);
    vector<double> v;

    while(izlaz.skloni(v)) {
        file << *v.begin();
        for(auto i = v.begin() + 1; i != v.end(); i++)
            file << "," << *i;
        file << endl;
    }
}

int main() {
    UlazniPodaci<pair<double, double>> ulazni_podaci;  // bafer podataka koje salje citac_iz_datoteke a obradjuju radnici
    IzlazniPodaci<vector<double>> izlazni_podaci;  // bafer podataka koje pripremaju radnici a ispisuju se u datoteku u pisacu_u_datoteku
    thread citac{citacf, "distribucije.txt", ref(ulazni_podaci)},  // stvaranje niti citaca_iz_datoteke
           pisac{pisacf, ref(izlazni_podaci), "brojevi.csv"},      // stvaranje niti pisaca_u_datoteku
           radnici[6];

    for (auto &nit: radnici)
        nit = thread(radnik, ref(ulazni_podaci), ref(izlazni_podaci));  // stvaranje niti radnika

    for (auto &nit: radnici)
        nit.join();
    citac.join();
    pisac.join();

    return 0;
}
