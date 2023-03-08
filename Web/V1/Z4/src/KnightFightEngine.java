import java.util.ArrayList;

public class KnightFightEngine {
    private int moves;
    private String next;
    private Figura[][] board = new Figura[8][8];

    public int getMoves() {
        return moves;
    }

    public String getNext() {
        return next;
    }

    public void initilize() {
        Knight white_knight = new Knight("S", "Bela");
        Knight black_knight = new Knight("S", "Crna");

        Figura[] array = { white_knight, white_knight, white_knight, new King("K", "Bela"), black_knight, black_knight, black_knight, new King("K", "Crna") };

        for (int i = 0; i < 8; i++) {
            deployFigure(array[i], Math.round(i / 8.0f) * 7);
        }

        this.next = "Bela";
    }

    public void deployFigure(Figura f, int y) {
        int x;
        do {
            x = (int) (Math.random() * 8.0f);
        } while(board[y][x] != null);
        board[y][x] = f;
    }

    public void printBoard() {
        System.out.println("\t\tA\t\tB\t\tC\t\tD\t\tE\t\tF\t\tG\t\tH");
        for (int i = 0; i < 8; i++) {
            System.out.print(i + "\t\t");
            for (int j = 0; j < 8; j++) {
                if (this.board[i][j] == null)
                    System.out.print("+\t\t");
                else
                    System.out.print(this.board[i][j] + "\t");
            }
            System.out.println();
        }
    }

    public boolean move(char current_x, int current_y, char new_x, int new_y) {
        int curr_x = (int)(current_x - 'A');
        int newr_x = (int)(new_x - 'A');

        if(this.board[current_y][curr_x] == null)
            return false;

        if(!this.board[current_y][curr_x].getColor().equals(this.next))
            return false;

        if(!this.board[current_y][curr_x].move(curr_x, current_y, newr_x, new_y))
            return false;

        if(this.board[new_y][newr_x] != null && this.board[new_y][newr_x].getColor().equals(this.board[current_y][curr_x].getColor()))
            return false;

        this.board[new_y][newr_x] = this.board[current_y][curr_x];
        this.board[current_y][curr_x] = null;
        this.moves++;
        if (this.next.equals("Bela"))
            this.next = "Crna";
        else
            this.next = "Bela";
        return true;
    }

    public boolean isEnd() {
        int res = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (this.board[i][j] != null)
                    if (this.board[i][j].toString().charAt(0) == 'K')
                        res++;
        return res == 2 ? false : true;
    }

    public String getWinner() {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (this.board[i][j] != null)
                    if (this.board[i][j].toString().charAt(0) == 'K')
                        return this.board[i][j].getColor();
        return "";
    }

    public ArrayList<Figura> getFigures(String color) {
        ArrayList<Figura> figures = new ArrayList<Figura>();
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (this.board[i][j] != null)
                    if (this.board[i][j].getColor().equals(color))
                        figures.add(this.board[i][j]);
        return figures;
    }

    public int[] getPosition(Figura f) {
        int[] pos = new int[2];
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (this.board[i][j] == f) {
                    pos[0] = j;
                    pos[1] = i;
                }
        return pos;
    }
}
