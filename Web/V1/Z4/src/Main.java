import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        KnightFightEngine game = new KnightFightEngine();
        game.initilize();
        game.printBoard();
        ArrayList<Figura> whites = new ArrayList<Figura>();
        ArrayList<Figura> blacks = new ArrayList<Figura>();
        whites = game.getFigures("Bela");
        blacks = game.getFigures("Crna");

        Figura w_king = null;
        Figura b_king = null;

        // TODO check i/j x/y order movement not working


        for (int i = 0; i < 4; i++) {
            if (whites.get(i).toString().equals("K[Bela]"))
                w_king = whites.get(i);
            if (blacks.get(i).toString().equals("K[Crna]"))
                b_king = blacks.get(i);
        }

        int[] w_king_pos = game.getPosition(w_king);
        int[] b_king_pos = game.getPosition(b_king);

        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        char[] move = new char[3];
        try {
            input.read(move, 0, 3);
        } catch (IOException ioe) {
            System.out.println(ioe.getMessage());
            System.exit(-1);
        }

        game.move((char)(w_king_pos[0] + 'A'), w_king_pos[1], move[0], (int)(move[1] - '0'));

        try {
            input.read(move, 0, 3);
        } catch (IOException ioe) {
            System.out.println(ioe.getMessage());
            System.exit(-1);
        }

        game.move((char)(b_king_pos[0] + 'A'), b_king_pos[1], move[0], (int)(move[1] - '0'));

        game.printBoard();
        if (game.isEnd()) {
            System.out.println(game.getWinner());
        }
    }
}
