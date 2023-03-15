import java.util.ArrayList;

public class Server extends RacunarNaMrezi {
    protected ArrayList<Klijent> prijavljeniKlijenti = new ArrayList<Klijent>();
    protected int brPrijavljenihKlijenata = 0;

    public Server(String adresa) {
        super(adresa);
    }

    public void prihvatiZahtev(Klijent klijent, String poruka) {
        if (poruka.equals("prijava")) {
            prijavljeniKlijenti.add(klijent);
            brPrijavljenihKlijenata++;
        } else if (poruka.equals("odjava")) {
            prijavljeniKlijenti.remove(klijent);
            brPrijavljenihKlijenata--;
        } else if (poruka.equals("ping"))
            if (prijavljeniKlijenti.contains(klijent))
                obradi(klijent);
    }

    protected void obradi(Klijent klijent) {
        klijent.prihvatiOdgovor("Server " + getAdresa() + " salje poruku.");
    }
}
