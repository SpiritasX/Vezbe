public class Poljoprivrednik extends Proizvodjac {
    public Poljoprivrednik(String ime) {
        super(ime);
    }

    public void dodajProizvod(Proizvod p, float cena) throws Greska {
        if (p.getTip() != 'P')
            throw new Greska("Greska");

        int idx = -1;

        for (Proizvod pr : this.N)
            if (pr.getNaziv().equals(p.getNaziv()))
                idx = this.N.indexOf(pr);

        if (idx >= 0) {
            this.N.remove(idx);
            this.cene.remove(idx);
        }

        this.N.add(p);
        this.cene.add(cena * 1.2f);
    }
}
