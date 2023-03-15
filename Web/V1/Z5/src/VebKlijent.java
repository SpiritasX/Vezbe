public class VebKlijent extends RacunarNaMrezi implements Klijent {
    private String imeBrauzera;

    public VebKlijent(String adresa, String imeBrauzera) {
        super(adresa);
        this.imeBrauzera = imeBrauzera;
    }

    @Override
    public void prijaviSe(String adresa) {
        Mreza.proslediZahtev(adresa, this, "prijava");
    }

    @Override
    public void odjaviSe(String adresa) {
        Mreza.proslediZahtev(adresa, this, "odjava");
    }

    @Override
    public void posaljiZahtev(String adresa) {
        Mreza.proslediZahtev(adresa, this,  "ping");
    }

    @Override
    public void prihvatiOdgovor(String poruka) {
        System.out.println(toString() + ":" + poruka);
    }

    @Override
    public String toString() {
        return this.getAdresa() + "[" + this.imeBrauzera + "]";
    }
}
