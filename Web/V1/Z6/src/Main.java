import java.util.ArrayList;
import java.util.GregorianCalendar;
import java.util.Calendar;

public class Main {
    public static void main(String[] args) {
        Calendar c = new GregorianCalendar(2012, 7, 3);
        Festival arsenal = new Festival("Arsenal fest", 7, c.getTime());

        Bend goblini = new Bend("Goblini");
        Bend eo = new Bend("Elektricni orgazam");

        StudentMuzicar ivana= new StudentMuzicar("Ivana", "Ivanovic", "Pop");

        ArrayList<jeIzvodjac> izvodjaci = new ArrayList<jeIzvodjac>();
        izvodjaci.add(goblini);
        izvodjaci.add(eo);
        izvodjaci.add(ivana);

        for (jeIzvodjac i : izvodjaci)
            arsenal.prijava(i);

        System.out.println(arsenal.ispisiRaspored());

        arsenal.odjava(goblini);

        System.out.println(arsenal.ispisiRaspored());
    }
}
