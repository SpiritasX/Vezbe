import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        ArrayList<Vrednosno> red = new ArrayList<Vrednosno>();

        Korpa k1 = new Korpa(1000);
        Korpa k2 = new Korpa (1000);

        Mleko mleko = null;
        Secer secer = null;

        try {
            mleko = new Mleko();
            secer = new Secer();
        } catch(Exception e) {
            System.out.println(e.getMessage());
            System.exit(-1);
        }

        try {
            k1.dodaj(new Zapis(secer, 1.0f, 400));
            k1.dodaj(new Zapis(secer, 0.5f, 400));

            k2.dodaj(new Zapis(mleko, 1.0f, 150));
            k2.dodaj(new Zapis(mleko, 1.0f, 150));
        } catch (Exception e) {
            System.out.println(e.getMessage());
            System.exit(-1);
        }

        red.add(k1);
        red.add(k2);
        red.add(new Zapis(mleko, 0.7f, 150));

        double sum = 0;
        for (Vrednosno v : red)
            sum += v.vrednost();
        System.out.println(sum);

        System.out.println(k1);
    }
}
