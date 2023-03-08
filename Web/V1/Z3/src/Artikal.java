public class Artikal {
    private String naziv;
    private JedinicaMere jm;

    public Artikal(String naziv, String jm) throws Exception {
        this.naziv = naziv;
        this.jm = new JedinicaMere(jm);
    }

    public JedinicaMere getJm() {
        return jm;
    }

    public void setJm(JedinicaMere jm) {
        this.jm = jm;
    }

    @Override
    public String toString() {
        return this.naziv;
    }
}
