public abstract class Figura {
    private String color;

    public Figura(String color) {
        this.color = color;
    }

    public String getColor() {
        return color;
    }

    public abstract boolean move(int current_x, int current_y, int new_x, int new_y);
}