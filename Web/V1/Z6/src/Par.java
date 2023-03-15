import java.util.Objects;

public class Par {
    private Object key;
    private Object value;

    public Par(Object key, Object value) {
        this.key = key;
        this.value = value;
    }

    public Object getKey() { return this.key; }
    public Object getValue() { return this.value; }

    public void setValue(Object value) { this.value = value; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Par par = (Par) o;
        return Objects.equals(key, par.key) && Objects.equals(value, par.value);
    }
}
