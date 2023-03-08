public class Firma extends Proizvodjac {
    protected String PIB;

    public Firma(String ime, String PIB) {
        super(ime);
        this.PIB = PIB;
    }

    public void dodajProizvod(Proizvod p, float cena) {
        int idx = -1;

        for (Proizvod pr : this.N)
            if (pr.getNaziv().equals(p.getNaziv()))
                idx = this.N.indexOf(pr);

        if (idx >= 0) {
            this.cene.remove(idx);
            this.N.remove(idx);
        }

        this.N.add(p);
        this.cene.add(cena * 1.4f);
    }

    @Override
    public String toString() {
        return this.PIB;
    }
}
