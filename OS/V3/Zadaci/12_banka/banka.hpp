#ifndef BANKA_HPP_INCLUDED
#define BANKA_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "valuta.hpp"
#include "kredit.hpp"

using namespace std;

class Banka {
private:
    Kredit& kredit;
    mutex m;
    condition_variable cv;
    int dsaldo;
    int esaldo;
public:

    Banka(Kredit& kr, int inicijalni_dsaldo, int inicijalni_esaldo) : kredit(kr) {
        // Prosiriti po potrebi ...
        this->dsaldo = inicijalni_dsaldo;
        this->esaldo = inicijalni_esaldo;
    }

    // Metoda koju poziva nit koja simulira klijenta banke, kada klijent zatraži kredit od banke.
    // Ukoliko banka nema odgovarajuća sredstva kako bi omogućila kredit, metoda će blokirati dok se ta sredstva ne oslobode.
    //
    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // valuta - Valuta u kojem je novčani iznos
    //
    // Potrebno je pozvati metodu kredit.ceka kada nema sredstava odgovarajuće valute da se odobri kredit.
    // Potrebno je pozvati metodu kredit.dobio kada se kredit realizuje.
    void uzmi_kredit(int rbr, int svota, Valuta valuta) {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        int saldo = (valuta == Valuta::DINAR) ? dsaldo : esaldo;

        while (svota > saldo) {
            kredit.ceka(rbr, svota, valuta);
            cv.wait(lock);
            saldo = (valuta == Valuta::DINAR) ? dsaldo : esaldo;
        }

        saldo -= svota;

        if (valuta == Valuta::DINAR)
            dsaldo = saldo;
        else
            esaldo = saldo;
        
        kredit.dobio(rbr, svota, saldo, valuta);
    }

    // Metoda koju poziva nit koja simulira klijenta banke, kada klijent vrati kredit koji je prethodno uzeo od banke.
    //
    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // valuta - Valuta u kojem je novčani iznos
    //
    // Potrebno je pozvati metodu kredit.vratio kada je kredit vraćen.
    void vrati_kredit(int rbr, int svota, Valuta valuta) {
        // Implementirati ...
        unique_lock<mutex> lock(m);
        int saldo = (valuta == Valuta::DINAR) ? dsaldo : esaldo;
        saldo += svota;
        kredit.vratio(rbr, svota, saldo, valuta);

        if (valuta == Valuta::DINAR)
            dsaldo = saldo;
        else
            esaldo = saldo;
        
        cv.notify_one();
    }
};

#endif // BANKA_HPP_INCLUDED
