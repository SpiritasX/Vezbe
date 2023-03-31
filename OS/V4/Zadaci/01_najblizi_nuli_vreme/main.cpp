/*
Napraviti konkurentni program koji pronalazi element najbliži broju 0 u zadatom vektoru brojeva.

Pretragu podeliti u 3 programske niti. Ulazni vektor brojeva treba da sadrži 900.000 slučajno generisanih brojeva.

Za svaku nit, evidentirati trenutke kada je izvršavanje počelo i kada se završilo. Na kraju programa, ispisati koliko je trajalo izvršavanje svake niti u milisekundama.
*/

#include <iostream>
#include <thread>
#include <vector>
#include <random>

using namespace std;
using namespace chrono;

typedef vector<double>::const_iterator cit;

struct vreme {
    system_clock::time_point pocetak;
    system_clock::time_point kraj;
};

void f(cit pocetak, cit kraj, double & min, struct vreme * v) {
	// Implementirati...
    (*v).pocetak = system_clock::now();
    cout << (*v).pocetak.time_since_epoch().count() << endl;
    min = *pocetak;
    for (cit i = pocetak; i != kraj; i++)
        if (abs(*i) < abs(min))
            min = *i;
    (*v).kraj = system_clock::now();
}

const int BROJ_NITI = 3;
const long DUZINA = 90000000;

int main() {
    long SEGMENT = DUZINA / BROJ_NITI;
    default_random_engine gen;

    gen.seed(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());// Inicijalizacija generatora slučajnih brojeva da pri svakom pokretanju daje različite brojeve
    uniform_real_distribution<double> real_dist(-1e5, 1e5);

    vector<double> v(DUZINA);
    // Puni se vektor pseudo-slučajnim brojevima
    for (int i = 0; i < DUZINA; i++)
       v[i] = real_dist(gen);

    double minimumi[BROJ_NITI];  // Niz elemenata najbližih nuli - svaka programska nit će dati svoj međurezltat
    struct vreme vremena[BROJ_NITI]; // Niz struktura u koji će biti upisani podaci o trajanju izvršavanja svake niti

    thread niti[BROJ_NITI];

	// Implementirati...

    for (int i = 0; i < BROJ_NITI; i++) {
        niti[i] = thread(f, v.begin() + i * SEGMENT, v.begin() + (i + 1) * SEGMENT, ref(minimumi[i]), vremena + i);
    }

    for (int i = 0; i < BROJ_NITI; i++)
        niti[i].join();
    
    double res = minimumi[0];
    for (int i = 1; i < BROJ_NITI; i++)
        if (abs(minimumi[i]) < abs(res))
            res = minimumi[i];
    
    cout << "Closest to 0 is " << res << endl;

    for (int i = 0; i < BROJ_NITI; i++) {
        duration<double> d = vremena[i].kraj - vremena[i].pocetak;
        cout << "Thread " << i + 1 << " took " << d.count() << " seconds." << endl;
    }

    return 0;
}

