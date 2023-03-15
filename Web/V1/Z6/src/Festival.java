import java.util.ArrayList;
import java.util.Date;

import static java.lang.Integer.MAX_VALUE;
import static java.lang.Integer.valueOf;
import static java.lang.Math.min;

public class Festival {
    private String naziv;
    private ArrayList<Par> raspored = new ArrayList<>();
    private Date pocetak;
    private int trajanje;
    private int brBina;
    private int brUcesnika;

    public Festival(String naziv, int trajanje, Date pocetak, int brBina) {
        this.naziv = naziv;
        this.trajanje = trajanje;
        this.pocetak = pocetak;
        this.brBina = brBina;
    }

    public Festival(String naziv, int trajanje, Date pocetak) {
        this.naziv = naziv;
        this.trajanje = trajanje;
        this.pocetak = pocetak;
        this.brBina = 1;
    }

    public void prijava(jeIzvodjac izvodjac) {
        int bina;
        int danPoRedu;
        if (raspored.size() == 0)
            bina = 1;
        else {
            int bine[] = new int[brBina];
            for (Par par : raspored) {
                String str = (String) par.getValue();
                bine[valueOf(str.substring(str.length() - 1)) - 1]++;
            }

            int min = 0;
            for (int i = 0; i < brBina; i++)
                if (bine[i] < bine[min])
                    min = i;
            bina = min + 1;
        }

        if (raspored.size() == 0)
            danPoRedu = 1;
        else {
            int dani[] = new int[trajanje];
            for (Par par : raspored) {
                String str = (String) par.getValue();
                dani[valueOf(str.substring(4, 5)) - 1]++;
            }

            int min = 0;
            for (int i = 0; i < trajanje; i++)
                if (dani[i] < dani[min])
                    min = i;
            danPoRedu = min + 1;
        }

        raspored.add(new Par(izvodjac, "Dan " + danPoRedu + ", " + "bina " + bina));
    }

    public void odjava(jeIzvodjac izvodjac) {
        for (Par par : raspored)
            if (par.getKey() == izvodjac) {
                raspored.remove(par);
                break;
            }
    }

    public String nastup(jeIzvodjac izvodjac) {
        for (Par par : raspored)
            if (par.getKey() == izvodjac)
                return naziv + "(" + pocetak + ")" + " " + izvodjac.nastup(this);
        return "";
    }

    public String ispisiRaspored() {
        String str = "Raspored:\n";
        for (Par par : raspored)
            str += ((jeIzvodjac)par.getKey()).nastup(this) + " " + par.getValue() + "\n";
        return str;
    }
}
