public class Brojac {
    private static int vrd;

    public int getNext() { return ++this.vrd; }

    public void reset() { this.vrd = 0; }
}
