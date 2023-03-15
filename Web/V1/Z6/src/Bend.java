public class Bend implements jeIzvodjac {
    private String naziv;

    public Bend(String naziv) {
        this.naziv = naziv;
    }

    public String getNaziv() { return this.naziv; }


    @Override
    public void prijavaFestival(Festival festival) {
        festival.prijava(this);
    }

    @Override
    public void odjavaFestival(Festival festival) {
        festival.odjava(this);
    }

    @Override
    public String nastup(Festival festival) {
        return getNaziv();
    }
}
