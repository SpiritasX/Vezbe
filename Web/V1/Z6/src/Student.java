public class Student {
    private String ime;
    private String prezime;

    public Student(String ime, String prezime) {
        this.ime = ime;
        this.prezime = prezime;
    }

    public String getIme() { return this.ime; }
    public String getPrezime() { return this.prezime; }

    @Override
    public String toString() {
        return ime + " " + prezime;
    }
}
