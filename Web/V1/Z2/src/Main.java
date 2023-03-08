import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        Poljoprivredni grasak = null;
        Poljoprivredni repa = null;
        Industrijski secer = null;

        try {
            grasak = new Poljoprivredni("Grasak");
            repa = new Poljoprivredni("Repa");
            secer = new Industrijski("Secer");
        } catch(Greska g) {
            return;
        }

        Poljoprivrednik marko = new Poljoprivrednik("Marko Markovic");
        Firma poljolink = new Firma("Poljolink", "123");

        try {
            marko.dodajProizvod(grasak, 50);
            marko.dodajProizvod(repa, 100);
            marko.dodajProizvod(grasak, 100);
        } catch(Greska g) {
            return;
        }

        poljolink.dodajProizvod(secer, 400);
        poljolink.dodajProizvod(repa, 100);

        ArrayList<Proizvodjac> proizvodjaci = new ArrayList<Proizvodjac>();
        proizvodjaci.add(marko);
        proizvodjaci.add(poljolink);

        for (Proizvodjac p : proizvodjaci)
            System.out.println(p);
    }
}
