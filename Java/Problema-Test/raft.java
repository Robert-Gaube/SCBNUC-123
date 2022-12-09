class Document {
    private String text;
    private String numeAutor;

    public Document(String text, String numeAutor) {
        this.text = text;
        this.numeAutor = numeAutor;
    }
    public String toString() {
        return text + " " + numeAutor;
    }
}
class Dosar {
    private Document[] documente;
    private int numarDocumente;

    public Dosare(int numarMaxDocumente) {
        this.numarDocumente = 0;
        this.documente = new Document[numarMaxDocumente];
    }
    public boolean adaugaDocument(Document d) {
        if(numarDocumente == documente.length) return false;

        documente[numarDocumente++] = d;
        return true;
    }
    public String toString() {
        String output = "Dosar: ";
        for(int i = 0; i < numarDocumente; ++i) {
            output += " -> " + documente[i];
        }
        return output;
    }
}
class Raft {
    private Dosar[] dosare;
    private int numarDosare;

    public Raft(int numarMaxDosare) {
        this.numarDosare = 0;
        this.dosare = new Dosar[numarMaxDosare];
    }
    public boolean adaugaDocument(Document d) {
        if(numarDocumente == documente.length) return false;

        documente[numarDocumente++] = d;
        return true;
    }
}