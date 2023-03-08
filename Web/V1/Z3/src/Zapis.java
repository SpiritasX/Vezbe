public class Zapis extends Vrednosno {
    private Artikal artikal;
    private float kolicina;
    private float jedCena;

    public Zapis(Artikal artikal, float kolicina, float jedCena) {
        this.artikal = artikal;
        this.kolicina = kolicina;
        this.jedCena = jedCena;
    }

    public Artikal getArtikal() {
        return artikal;
    }

    public void setArtikal(Artikal artikal) {
        this.artikal = artikal;
    }

    public float getKolicina() {
        return kolicina;
    }

    public void setKolicina(float kolicina) {
        this.kolicina = kolicina;
    }

    public float getJedCena() {
        return jedCena;
    }

    public void setJedCena(float jedCena) {
        this.jedCena = jedCena;
    }

    public double vrednost() {
        return this.kolicina * this.jedCena;
    }

    @Override
    public String toString() {
        return "(" + this.artikal + ", " + this.kolicina + ", " + this.artikal.getJm() + ", " + vrednost() + ")";
    }
}
