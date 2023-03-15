public class Main {
    public static void main(String[] args) {
        Server uns = new Server("uns");
        Server ftn = new Server("ftn");
        MultikastServer twitter = new MultikastServer("twitter");

        VebKlijent ivica = new VebKlijent("ivica", "chrome");
        VebKlijent marica = new VebKlijent("marica", "mozilla");

        Mreza.registrujUredjaj(uns);
        Mreza.registrujUredjaj(ftn);
        Mreza.registrujUredjaj(twitter);
        Mreza.registrujUredjaj(ivica);
        Mreza.registrujUredjaj(marica);

        ivica.prijaviSe("uns");
        ivica.prijaviSe("twitter");
        marica.prijaviSe("twitter");

        ivica.posaljiZahtev("uns");
        ivica.posaljiZahtev("twitter");
        ivica.posaljiZahtev("ftn");
        ivica.posaljiZahtev("twitter");

        ivica.odjaviSe("uns");
        ivica.odjaviSe("twitter");
        marica.odjaviSe("twitter");
    }
}
