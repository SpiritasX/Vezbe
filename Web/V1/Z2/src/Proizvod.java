import java.util.ArrayList;

public abstract class Proizvod {
    private int ID;
    private String naziv;
    private Brojac b = new Brojac();
    private char tip;
    private ArrayList<Proizvod> listaProizvoda = new ArrayList<Proizvod>();

    public Proizvod(String naziv, char tip) throws Greska {
        for (Proizvod p : listaProizvoda)
            if (p.getNaziv().equals(naziv))
                throw new Greska("Greska");

        this.naziv = naziv;
        this.tip = tip;

        int next_id = b.getNext();
        if (next_id > 50)
            throw new Greska("Greska");

        this.ID = next_id;
    }

    public String getNaziv() { return this.naziv; }
    public void setNaziv(String naziv) { this.naziv = naziv; }
    public int getID() { return this.ID; }
    public char getTip() { return this.tip; }

    public void dodajUListuProizvoda(Proizvod p) {
        listaProizvoda.add(p);
    }

    public Proizvod nadjiProizvod(String naziv) {
        for (Proizvod p : listaProizvoda)
            if (p.getNaziv().equals(naziv))
                return p;
        return null;
    }

    @Override
    public String toString() {
        return this.ID + " " + this.tip + " " + this.naziv;
    }
}
