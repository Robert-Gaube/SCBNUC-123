import java.util.*;

interface Propozitie {
    Propozitie faraImplicatii();
}
class PropozitieAtomica implements Propozitie {
    private String nume;

    public PropozitieAtomica(String nume) {
        this.nume = nume;
    }
    public Propozitie faraImplicatii() {
        return new PropozitieAtomica(this.nume);
    }
    public String toString() {
        return this.nume;
    }
}
class Negatie implements Propozitie {
    private Propozitie propozitie;
    
    public Negatie(Propozitie propozitie) {
        this.propozitie = propozitie;
    }
    public Propozitie faraImplicatii() {
        return new Negatie(propozitie.faraImplicatii());
    }
    public String toString() {
        return "!" + propozitie;
    }
}
class SauMultiplu implements Propozitie {
    private ArrayList<Propozitie> propozitii;

    public SauMultiplu(ArrayList<Propozitie> propozitii) {
        this.propozitii = propozitii;
    }
    public Propozitie faraImplicatii() {
        ArrayList<Propozitie> l = new ArrayList<Propozitie>();
        for(Propozitie prop : propozitii) {
            l.add(prop.faraImplicatii());
        }
        return new SauMultiplu(l);
    }
    public String toString() {
        String output = "(";
        int i;
        for(i = 0; i < propozitii.size() - 1; ++i) {
            output += propozitii.get(i) + " | ";
        }

        return output + propozitii.get(propozitii.size() - 1) + ")";
    }
}
class Implicatie implements Propozitie {
    private Propozitie propozitie1;
    private Propozitie propozitie2;

    public Implicatie(Propozitie propozitie1, Propozitie propozitie2) {
        this.propozitie1 = propozitie1;
        this.propozitie2 = propozitie2;
    }
    public Propozitie faraImplicatii() {
        Propozitie tempA = new Negatie(propozitie1.faraImplicatii());
        Propozitie tempB = propozitie2.faraImplicatii();

        ArrayList<Propozitie> l = new ArrayList<Propozitie>();
        l.add(tempA);
        l.add(tempB);
        return new SauMultiplu(l);
    }
    public String toString() {
        return "(" + propozitie1 + " -> " + propozitie2 + ")";
    }
}
class Main {
    public static void main(String[] argv) {
        PropozitieAtomica prop1 = new PropozitieAtomica("A");
        PropozitieAtomica prop2 = new PropozitieAtomica("B");
        PropozitieAtomica prop3 = new PropozitieAtomica("C");

        Implicatie implicatie1 = new Implicatie(prop2, prop3);
        System.out.println(implicatie1);
        System.out.println(implicatie1.faraImplicatii());

        Negatie prop4 = new Negatie(prop1);
        ArrayList<Propozitie> l = new ArrayList<Propozitie>();
        l.add(prop1);
        l.add(prop2);
        l.add(prop4);
        SauMultiplu prop5 = new SauMultiplu(l);

        System.out.println(prop1);
        System.out.println(prop1.faraImplicatii());

        System.out.println(prop4);
        System.out.println(prop5);
    }
}