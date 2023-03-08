public class Knight extends Figura {
    private String name;

    public Knight(String name, String color) {
        super(color);
        this.name = name;
    }

    public boolean move(int current_x, int current_y, int new_x, int new_y) {
        if (new_x > 8 || new_x < 0 || new_y > 8 || new_y < 0)
            return false;
        return true;
    }

    @Override
    public String toString() {
        return this.name + "[" + this.getColor() + "]";
    }
}
