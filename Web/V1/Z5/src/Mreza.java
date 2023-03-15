import java.util.ArrayList;

public class Mreza {
    private static ArrayList<RacunarNaMrezi> dostupniUredjaji = new ArrayList<RacunarNaMrezi>();
    private static int brUredjaja = 0;

    public static void registrujUredjaj(RacunarNaMrezi racunar) {
        dostupniUredjaji.add(racunar);
        brUredjaja++;
    }

    private static RacunarNaMrezi pronadji(String adresa) {
        for (RacunarNaMrezi racunar : dostupniUredjaji)
            if (racunar.getAdresa().equals(adresa))
                return racunar;
        return null;
    }

    public static void proslediZahtev(String adresa, Klijent klijent, String poruka) {
        for (RacunarNaMrezi racunar : dostupniUredjaji)
            if (racunar.getAdresa().equals(adresa))
                ((Server)racunar).prihvatiZahtev(klijent, poruka);
    }

    public static void proslediOdgovor(String adresa, String poruka) {
        for (RacunarNaMrezi racunar : dostupniUredjaji)
            if (racunar.getAdresa().equals(adresa))
                ((Klijent)racunar).prihvatiOdgovor(poruka);
    }
}
