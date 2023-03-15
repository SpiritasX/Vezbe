public abstract class RacunarNaMrezi {
    private String adresa;

    public RacunarNaMrezi(String adresa) {
        this.adresa = adresa;
    }

    public String getAdresa() {
        return this.adresa;
    }

    @Override
    public String toString() {
        return "Adresa: " + this.adresa;
    }

    public boolean equals(String adresa) {
        return this.adresa.equals(adresa);
    }

    public boolean equals(RacunarNaMrezi racunar) {
        return this.adresa.equals(racunar.getAdresa());
    }
}
