abstract class Proprietate {
    protected String adresa;
    protected int suprafata;

    public Proprietate(String adresa, int suprafata) {
        this.adresa = adresa;
        this.suprafata = suprafata;
    }
    abstract int sumaDePlatit();
}
class Cladire extends Proprietate {
    public Cladire(String adresa, int suprafata) {
        super(adresa, suprafata);
    }
    public int sumaDePlatit() {
        return 500 * this.suprafata;
    }
    public String toString() {
        return "\tCladire:" + this.adresa + "\n\t\tSuprafata: " + this.suprafata + "\n\t\tCost: " + this.sumaDePlatit() + "\n"; 
    }
}
class Teren extends Proprietate{
    private int rang;

    public Teren(String adresa, int suprafata, int rang) {
        super(adresa, suprafata);
        this.rang = rang;
    }
    public int sumaDePlatit() {
        return 350 * this.suprafata / rang;
    }
    public String toString() {
        return "\tTeren:  " + this.adresa + "\n\t\tSuprafata: " + this.suprafata + " Rang: " + this.rang + "\n\t\tCost: " + this.sumaDePlatit() + "\n"; 
    }
}
class Contribuabil {
    private String nume;
    private String CNP;
    private Proprietate[] proprietati = new Proprietate[10];
    private int numarProprietati = 0;

    public Contribuabil(String nume, String CNP) {
        this.nume = nume;
        this.CNP = CNP;
    }
    public boolean addProprietate(Proprietate p) {
        if(this.numarProprietati == 10) return false;

        proprietati[numarProprietati++] = p;
        return true;
    }
    public int sumaTotala() {
        int suma = 0;
        for(int i = 0; i < this.numarProprietati; ++i) suma += proprietati[i].sumaDePlatit();
        return suma;
    }
    public void aviz() {
        System.out.println("Nume: " + nume + "\nProprietati: \n");
        for(int i = 0; i < numarProprietati; ++i) {
            System.out.println(proprietati[i]);
        }
    }
}
class Main {
    public static void main(String argv[]) {
        Contribuabil om1 = new Contribuabil("Ion", "176237812");
        Proprietate proprietate1 = new Cladire("Ion parvan nr 2", 10);
        Proprietate proprietate2 = new Teren("Ion parvan nr 2", 10, 1);
        om1.addProprietate(proprietate1);
        om1.addProprietate(proprietate2);
        om1.aviz();

        System.out.println("Suma totala: " + om1.sumaTotala());
    }
}
