import java.util.ArrayList;

public interface Proizvodi {
    public ArrayList<Proizvod> dajListuProizvoda();
    public float cena(String naziv);
    public float cena(Proizvod proizvod);
}
