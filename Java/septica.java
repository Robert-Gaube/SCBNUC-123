import java.io.*;
import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

class Constants {
    public static final String[] types = new String[] {
        "trefla",
        "inima neagra",
        "inima rosie",
        "romb"
    };
    public static final int noShuffles = 40;
    public static final int noCards = 40;
    public static final int noPlayers = 10;
}
class Card {
    private int numar;
    private String tip;

    public Card(int numar, String tip) {
        this.numar = numar;
        this.tip = tip;
    }
    public int getNumar() {
        return numar;
    }
    public String getTip() {
        return tip;
    }
    public String toString() {
        return tip + ": " + numar;
    }
}
class Deck {
    private static Stack<Card> cards;
    private static Deck deck = null;

    public static Deck instance() {
        if (deck != null) return deck;

        deck = new Deck();
        cards = new Stack<Card>();

        return deck;
    }
    public void create() {
        if (deck == null) return;

        int i, j;
        for (i = 0; i < Constants.types.length; ++i) {
            for (j = 1; j <= 10; ++j) {
                cards.push(new Card(j, Constants.types[i]));
            }
        }
    }
    private static int randomCardIndex(int size) {
        int rand_int = ThreadLocalRandom.current().nextInt() % size;
        if (rand_int < 0) rand_int = -rand_int;
        return rand_int;
    }
    public void shuffle() {
        if (cards == null) return;
        
        int size = 0, i, index1, index2;
        Card aux; Card[] copy = new Card[cards.size()];

        while(!cards.isEmpty()) {
            copy[size++] = cards.pop();
        }
        for (i = 0; i < Constants.noShuffles; ++i) {
            index1 = Deck.randomCardIndex(size);
            index2 = Deck.randomCardIndex(size);
            aux = copy[index1];
            copy[index1] = copy[index2];
            copy[index2] = aux;
        }   
        for (i = 0; i < size; ++i) {
            cards.push(copy[i]);
            copy[i] = null;
        }
        copy = null;
    }
    public Card drawCard() {
        if (cards.isEmpty()) return null;
        return cards.pop();
    }
    public void addCards(Stack<Card> pile) {
        while (!pile.isEmpty()) cards.push(pile.pop());
    }
    public Card getTop() {
        if (cards.isEmpty()) return null;
        return cards.peek();
    }
    public String toString() {
        return cards.toString();
    }
}
class Player {
    private String name;
    private Player nextPlayer;
    private Card[] cards;
    private int noCards;

    public Player(String name) {
        this.name = name;
        this.nextPlayer = null;
        this.cards = new Card[Constants.noCards];
        this.noCards = 0;
    }
    public void setNextPlayer(Player p) {
        this.nextPlayer = p;
    }
    public void drawCards(int howMany, Deck deck) {
        for (int i = 0; i < howMany; ++i) cards[noCards++] = deck.drawCard();
    }
    private void deleteCard(int index) {
        cards[index] = null; noCards--;
        for (int i = index; i < noCards; ++i) cards[i] = cards[i + 1];
    }
    public void takeTurn(Game game) {
        int i, copyNoCards = noCards;
        Card top = game.getTop();

        System.out.print(name + "\nCe carte e jos: " + top + "\nCe carti am in mana:\n");
        this.showHand();
        System.out.println("\n");

        for (i = 0; i < noCards; ++i) {
            if (cards[i].getNumar() == top.getNumar() || cards[i].getTip().equals(top.getTip())) {
                game.putCardDown(cards[i]);
                this.deleteCard(i);
                break;
            }
        }

        if (i == copyNoCards){
            cards[noCards++] = game.drawCard();
        }
        if (noCards == 0) {
            System.out.println(name + " WIN!");
            return;
        }

        nextPlayer.takeTurn(game);
    }
    public void showHand() {
        for (int i = 0; i < noCards; ++i) {
            System.out.print(cards[i] + " ");
        }
    }
}

class Game {
    private Deck deck;
    private Player[] players;
    private Stack<Card> tableCards;
    private int noCards;
    private int noPlayers;

    public Game() {
        deck = Deck.instance();
        deck.create(); deck.shuffle();
        tableCards = new Stack<Card>();
        players = new Player[Constants.noPlayers];
        noCards = 0; noPlayers = 0;
    }
    public void addPlayer(Player p) {
        players[noPlayers++] = p;
    }
    public Card getTop() {
        return tableCards.peek();
    }
    public void remakeDeck() {
        Card top = this.getTop();
        deck.addCards(tableCards);
        deck.shuffle();
        tableCards.push(top);
    }
    public void putCardDown(Card d) {
        tableCards.push(d);
    }
    public Card drawCard() {
        Card card = deck.drawCard();
        if(card == null){
            this.remakeDeck();
            card = deck.drawCard();
        }
        return card;
    }
    public void showDeck() {
        System.out.println("\nDECK:\n" + deck + "\n");
    }
    public void start() {
        for(int i = 0; i < noPlayers; ++i) {
            players[i].setNextPlayer(players[(i + 1) % noPlayers]);
            players[i].drawCards(7, deck);
        }
        tableCards.push(deck.drawCard());

        players[0].takeTurn(this);
    }
}
class Main {
    public static void main(String[] argv) {
        Game game = new Game();

        Player player1 = new Player("Robert");
        Player player2 = new Player("Patricia");
        Player player3 = new Player("Ale");

        game.addPlayer(player1);
        game.addPlayer(player2);
        game.addPlayer(player3);

        game.start();
    }
}