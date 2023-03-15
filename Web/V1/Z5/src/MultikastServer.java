public class MultikastServer extends Server {
    public MultikastServer(String adresa) {
        super(adresa);
    }

    protected void obradi(Klijent klijent) {
        for (Klijent k : prijavljeniKlijenti)
            k.prihvatiOdgovor("Server " + getAdresa() + " svima salje poruku, jer se javio " + klijent + ".");
    }
}
