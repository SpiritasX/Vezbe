public class King extends Figura {
    private String name;

    public King(String name, String color) {
        super(color);
        this.name = name;
    }

    public boolean move(int current_x, int current_y, int new_x, int new_y) {
        return !(current_x - new_x < -1 || current_x - new_x > 1 || new_x > 8 || new_x < 0 || new_y > 8 || new_y < 0);
    }

    @Override
    public String toString() {
        return this.name + "[" + this.getColor() + "]";
    }
}
