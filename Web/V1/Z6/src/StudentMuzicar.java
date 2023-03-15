public class StudentMuzicar extends Student implements jeIzvodjac {
    private String vrstaMuzike;

    public StudentMuzicar(String ime, String prezime, String vrstaMuzike) {
        super(ime, prezime);
        this.vrstaMuzike = vrstaMuzike;
    }

    public String getVrstaMuzike() { return this.vrstaMuzike; }

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
        return getIme() + " " + getPrezime() + " " + getVrstaMuzike();
    }
}
