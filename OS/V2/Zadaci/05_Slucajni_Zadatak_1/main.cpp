/*
    Ako zamislite jedinični kvadrat centriran oko koordinatnog početka i krug upisan
    u taj kvadrat. Verovatnoća da će nasumično odabrana tačka u okviru kvadrata
    biti i u krugu, pod uslovom da je distribucija ravnomerna, je ravna odnosu njihovih
    površina, tj, ravna je PI/4. Iskoristiti ovaj podataka da kroz Monte Karlo simulaciju
    izračunate vrednost broja PI tako što probate ovaj eksperiment veliki broj puta i vodite
    računa o tome koliko puta dobijete tačku u krugu, a koliko puta van kruga, te na kraju
    simulacije izračunate izmerenu verovatnoću i na osnovu nje, sračunate vrednost broja pi.
*/

#include <iostream>
#include <chrono>
#include <random>

#define NUMBER_OF_POINTS 10000000
#define SQUARE_SIDE 10000

typedef std::chrono::high_resolution_clock hrc_t;

hrc_t::time_point start = hrc_t::now();

int main() {
    std::default_random_engine generator;
    hrc_t::duration d = hrc_t::now() - start;
    generator.seed(d.count());
    
    double number_of_points_in_circle = 0;

    std::uniform_int_distribution<int> dist(-SQUARE_SIDE, SQUARE_SIDE);

    for (int i = 0; i < NUMBER_OF_POINTS; i++) {
        int x = dist(generator);
        int y = dist(generator);

        int distance = x * x + y * y;

        if (distance <= SQUARE_SIDE * SQUARE_SIDE)
            number_of_points_in_circle++;
    }

    std::cout << 4.0 * number_of_points_in_circle / NUMBER_OF_POINTS << std::endl;
}