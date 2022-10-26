abstract class Vagon {
    protected int capacitatePasageri;
    protected int capacitateColete;

    public Vagon(int capacitatePasageri, int capacitateColete) {
        this.capacitatePasageri = capacitatePasageri;
        this.capacitateColete = capacitateColete;
    }
    public int getCapacitateColete() {
        return this.capacitateColete;
    }
    public int getCapacitatePasageri() {
        return this.capacitatePasageri;
    }
}
abstract class VagonAutomat extends Vagon{
    public VagonAutomat(int cp, int cc) {
        super(cp, cc);
    }
    public void deschidereAutomataUsi() {
        System.out.println("Deschidere automata usi");
    }
    public void inchidereAutomataUsi() {
        System.out.println("Inchidere automata usi");
    }
}
class CalatoriA extends VagonAutomat {
    private static final int CAPACITATE_PASAGERI = 40;
    private static final int CAPACITATE_COLETE = 300;

    public CalatoriA() {
        super(CAPACITATE_PASAGERI, CAPACITATE_COLETE);
    }
}
class CalatoriB extends VagonAutomat {
    private static final int CAPACITATE_PASAGERI = 50;
    private static final int CAPACITATE_COLETE = 400;

    public CalatoriB() {
        super(CAPACITATE_PASAGERI, CAPACITATE_COLETE);
    }
    public void blocareAutomataGeamuri() {
        System.out.println("Blocare automata geamuri");
    }
}
class Marfa extends Vagon {
    private static final int CAPACITATE_PASAGERI = 0;
    private static final int CAPACITATE_COLETE = 4300;

    public Marfa() {
        super(CAPACITATE_PASAGERI, CAPACITATE_COLETE);
    }
    public void deschidereManualaUsi() {
        System.out.println("Deschidere manuala usi");
    }
    public void inchidereManualaUsi() {
        System.out.println("Inchidere manuala usi");
    }
}
class Tren {
    private int numarVagoane = 0;
    private Vagon[] vagoane = new Vagon[15];

    public boolean adaugaVagon(Vagon v) {
        if(numarVagoane == 15) return false;
        vagoane[numarVagoane++] = v;
        return true;
    }
    public void afisareTipuriVagoane() {
        int calatoriA = 0, calatoriB = 0, marfa = 0, capacitate, i;
        for(i = 0; i < this.numarVagoane; ++i) {
            capacitate = vagoane[i].getCapacitatePasageri();
            if(capacitate == 40) calatoriA++;
            else if(capacitate == 50) calatoriB++;
            else marfa++;
        }
        System.out.println("CalatoriA: " + calatoriA + "\nCalatoriB: " + calatoriB + "\nMarfa: " + marfa);
    }
    public int capacitateTotalaColete() {
        int suma = 0;
        for(int i = 0; i < numarVagoane; ++i) {
            suma += vagoane[i].getCapacitateColete();
        }
        return suma;
    }
    public boolean equals(Object obj) {
        if(obj instanceof Tren) {
            if(this.capacitateTotalaColete() == ((Tren)obj).capacitateTotalaColete())
                return true;
        }
        return false;
    }
}
class Main {
    public static void main(String[] argv) {
        Tren tren = new Tren();
        tren.adaugaVagon(new Marfa());
        tren.adaugaVagon(new Marfa());
        tren.adaugaVagon(new CalatoriA());
        tren.adaugaVagon(new Marfa());        
        tren.adaugaVagon(new CalatoriB());
        tren.adaugaVagon(new Marfa());

        tren.afisareTipuriVagoane();

        Tren tren1 = new Tren();
        Tren tren2 = new Tren();

        tren1.adaugaVagon(new CalatoriB());
        tren2.adaugaVagon(new Marfa());

        System.out.println(tren1.equals(tren2));                                                                                                                                                              
    }
}