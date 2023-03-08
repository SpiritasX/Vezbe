public class JedinicaMere {
    private String oznaka;

    public JedinicaMere(String oznaka) throws Exception {
        if (!oznaka.equals("kom") && !oznaka.equals("l") && !oznaka.equals("m") && !oznaka.equals("kg"))
            throw new Exception("Nevazeca oznaka");

        this.oznaka = oznaka;
    }

    @Override
    public String toString() {
        return this.oznaka;
    }
}
