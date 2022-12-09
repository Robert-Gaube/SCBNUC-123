class NumarNotFound extends Exception {
    public NumarNotFound() {
        super("Nu exista numarul");
    }
}
class VectorPlin extends Exception {
    public VectorPlin() {
        super("Vectorul este plin");
    }
}
class Vector {
    private Integer[] numere = new Integer[10];
    private int numarNumere = 0;

    private void adaugaNumar(int x) throws VectorPlin {
        if(numarNumere == 10) throw new VectorPlin();
        numere[numarNumere++] = x;
    }
    public void adaugaNumerePanaLa(int x) {
        int i;
        try {
            for(i = 1; i < x; ++i) this.adaugaNumar(i);
        }
        catch (VectorPlin e) {
            System.out.println(e);
        }
    }
    public int gasesteNumar(int x) throws NumarNotFound {
        int i;
        for(i = 0; i < numarNumere; ++i) {
            if(numere[i] == x) return i;
        }
        throw new NumarNotFound();
    }
}

class Main {
    public static void main(String[] argv) {
        Vector vector = new Vector();
        vector.adaugaNumerePanaLa(9);

        try {
            System.out.println(vector.gasesteNumar(5));
            System.out.println(vector.gasesteNumar(12));
        }
        catch (NumarNotFound e) {
            System.out.println(e);
        }

        vector.adaugaNumerePanaLa(4);
    }
}