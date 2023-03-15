public interface Klijent {
    void prijaviSe(String adresa);
    void odjaviSe(String adresa);
    void posaljiZahtev(String adresa);
    void prihvatiOdgovor(String adresa);
    String getAdresa();
}
