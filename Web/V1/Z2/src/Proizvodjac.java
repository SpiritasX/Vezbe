import java.util.ArrayList;

public class Proizvodjac implements Proizvodi {
    protected ArrayList<Proizvod> N = new ArrayList<Proizvod>();
    protected ArrayList<Float> cene = new ArrayList<Float>();
    private String ime;

    public Proizvodjac(String ime) {
        this.ime = ime;
    }

    @Override
    public ArrayList<Proizvod> dajListuProizvoda() {
        return this.N;
    }

    public void dodajProizvod(Proizvod p, float cena) throws Greska {
        this.N.add(p);
        this.cene.add(cena);
    }

    public int nadjiProizvod(String naziv) {
        for (Proizvod p : this.N)
            if (p.getNaziv().equals(naziv))
                return this.N.indexOf(p);
        return -1;
    }

    public int nadjiProizvod(Proizvod p) {
        return this.N.indexOf(p);
    }

    @Override
    public float cena(String naziv) {
        int idx = -1;
        for (Proizvod p : this.N)
            if (p.getNaziv().equals(naziv))
                idx = this.N.indexOf(p);

        if (idx < 0)
            return -1;

        return cene.get(idx);
    }

    @Override
    public float cena(Proizvod proizvod) {
        int idx = this.N.indexOf(proizvod);

        if (idx < 0)
            return -1;

        return cene.get(idx);
    }

    @Override
    public String toString() {
        String str = "";

        str += this.ime;

        if (this instanceof Firma)
            str += ((Firma)this).PIB;

        for (Proizvod p : this.N)
            str += "\n" + p;

        return str;
    }
}
