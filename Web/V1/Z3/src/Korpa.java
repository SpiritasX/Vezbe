import java.util.ArrayList;

public class Korpa extends Vrednosno {
    private ArrayList<Zapis> sadrzaj = new ArrayList<Zapis>();
    private int max;

    public Korpa(int max) {
        this.max = max;
    }

    public void dodaj(Zapis zapis) throws Exception {
        if (vrednost() + zapis.vrednost() > this.max)
            throw new Exception("Vrednost korpe je presla maksimalnu!");

        this.sadrzaj.add(zapis);
    }

    public double vrednost() {
        double sum = 0;
        for (Zapis z : this.sadrzaj)
            sum += z.vrednost();
        return sum;
    }

    @Override
    public String toString() {
        String str = "\n[";
        for (Zapis z : this.sadrzaj)
            str += z + ", ";
        str = str.substring(0, str.length() - 2);
        str += "]\n";
        return str;
    }
}
