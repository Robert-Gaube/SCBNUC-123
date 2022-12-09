
abstract class Angajat implements Comparable<Angajat> {
    protected String nume;

    public Angajat(String nume) {
        this.nume = nume;
    }
    abstract public double calculSalar();
    abstract public Angajat createCopy();

    public int compareTo(Angajat angajat) {
        return this.nume.compareTo(angajat.nume);
    }
}
class AngajatCuSalarFix extends Angajat {
    private double salar;

    public AngajatCuSalarFix(String nume, double salar) {
        super(nume);
        this.salar = salar;
    }
    public double calculSalar() {
        return this.salar;
    }
    public void schimbaSalarFix(double salarNou) {
        this.salar = salarNou;
    }
    public Angajat createCopy() {
        return new AngajatCuSalarFix(this.nume, this.salar);
    }
    public String toString() {
        return nume + " " + salar;
    }
}
class AngajatCuOra extends Angajat {
    private double salarPeOra;
    private Double[] oreLucrate;
    private int numarOre;
    private double numarTotalOre;

    public AngajatCuOra(String nume, double salarPeOra) {
        super(nume);
        this.salarPeOra = salarPeOra;
        this.oreLucrate = new Double[31];
        this.numarOre = 0;
        this.numarTotalOre = 0;
    }
    public void adaugaOre(double ore) {
        if(numarOre == oreLucrate.length) return;

        oreLucrate[numarOre++] = ore;
        this.numarTotalOre += ore;
    }
    public void schimbaSalarPeOra(double salarNou) {
        this.salarPeOra = salarNou;
    }
    public double calculSalar() {
        return numarTotalOre * salarPeOra;
    }
    public Angajat createCopy() {
        return new AngajatCuOra(this.nume, this.salarPeOra);
    }
    public String toString() {
        return nume + " " + salarPeOra;
    }
}
class Firma {
    private int numarAngajati;
    private Angajat[] angajati;

    public Firma() {
        this.numarAngajati = 0;
        this.angajati = new Angajat[1024];
    }
    private void mutarePozitii(int x) {
        for(int i = numarAngajati; i > x; --i) angajati[i] = angajati[i - 1];
    }
    private int cautaAngajat(Angajat angajat) {
        int st = 0, dr = numarAngajati - 1, m;
        while(st <= dr) {
            m = (st + dr) / 2;
            if(angajat.compareTo(angajati[m]) > 0) st = m + 1;
            else if (angajat.compareTo(angajati[m]) < 0) dr = m - 1;
            else return m;
        }
        return -1;
    }
    public int angajeaza(Angajat angajat) {
        if(numarAngajati == angajati.length) return -1;
        if(cautaAngajat(angajat) != -1) return -2;

        int i;
        for(i = 0; i < numarAngajati && angajat.compareTo(angajati[i]) > 0; ++i);
        numarAngajati++;
        this.mutarePozitii(i);

        angajati[i] = angajat.createCopy();
        return 0;
    }
    public double salariuMediu() {
        if(this.numarAngajati == 0) return 0;

        double suma = 0;
        for(int i = 0; i < numarAngajati; ++i) suma += angajati[i].calculSalar();

        return suma / numarAngajati;
    }
    public void afisareAngajati() {
        for(int i = 0; i < numarAngajati; ++i) System.out.println(angajati[i]);
    }
}
class Main {
    public static void main(String[] argv) {
        Firma firma = new Firma();

        System.out.println(firma.salariuMediu());

        AngajatCuOra angajat1 = new AngajatCuOra("Patricia", 120);

        angajat1.adaugaOre(7);
        angajat1.adaugaOre(7);
        angajat1.adaugaOre(7);
        angajat1.adaugaOre(4);
        angajat1.adaugaOre(8);

        AngajatCuSalarFix angajat2 = new AngajatCuSalarFix("Robert", 4000);
        AngajatCuSalarFix angajat3 = new AngajatCuSalarFix("Alin", 25000);

        firma.angajeaza(angajat1);
        firma.angajeaza(angajat2);
        firma.angajeaza(angajat3);
        firma.angajeaza(angajat3);

        firma.afisareAngajati();

        System.out.println(firma.salariuMediu());
    }
}