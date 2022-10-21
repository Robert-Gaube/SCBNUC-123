/*Se citesc din standard input (stdin) urmatoarele date, reprezentand nume de studenti, genul (M/F) si media lor anuala (numar intreg):

- un numar N

- N intrari de forma <nota: numar intreg> <gen: un caracter> <nume-prenume: string>

- un <nume-prenume: string> - pentru cerinta 1 (*)

- un <nume-prenume: string> pentru cerinta 2 (**)

1. Sa se sorteze studentii crescator dupa nume-prenume (lexicografic), folosind o variantă modificată a sortării prin inserție, pornind de la mijloc înspre capete, si sa se afiseze indexul primului nume de student citit (*). 

2. Sa se sorteze studentii dupa urmatoarea regula, folosind o sortare simpla, si sa se afiseze indexul celui de-al doilea nume de student citit (**).

    - studentii cu media mai mica decat 5 vor fi plasati inaintea celorlalti studenti (indiferent de nume sau gen);

    - studentii cu aceeasi categorie de medie (mai mica decat 5 sau mai mare sau egala cu 5) vor fi sortati in functie de gen, studentii de gen feminin fiind plasati intotdeauna inaintea celor de gen masculin;

    - studentii de acelasi gen vor fi sortati alfabetic (crescator), in functie de nume-prenume.*/

#include <stdio.h>
#include <string.h>

typedef enum Gen{M, F} GEN;

typedef struct{
    int medie;
    GEN gen;
    char nume[100];
}ELEMENT;

void citire(ELEMENT *elemente, int *numar_elemente){
    int i;  char gen, *copy;
    scanf("%d", numar_elemente);

    for(i = 0; i < *numar_elemente; ++i){
        copy = elemente[i].nume;
        scanf("%d %c ", &elemente[i].medie, &gen);
        elemente[i].gen = gen == 'M' ? M : F;
        fgets(copy, 100, stdin), copy[strcspn(copy, "\n\r")] = 0;
    }
}
void afisare_elemente(ELEMENT *elemente, int numar_elemente){
    puts("");
    for(int i = 0; i < numar_elemente; ++i)
        printf("%d %c %s\n", elemente[i].medie, elemente[i].gen == M ? 'M' : 'F', elemente[i].nume);
    puts("");
}
int comparare_nume(ELEMENT el1, ELEMENT el2){
    return strcmp(el1.nume, el2.nume);
}
void sortare_dupa_nume(ELEMENT *elemente, int numar_elemente){
    int mijloc = numar_elemente / 2, i, j, stanga = mijloc, dreapta = mijloc; ELEMENT element;
    strcpy(elemente[numar_elemente].nume, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
    for(i = 0; i < mijloc; ++i){
        element = elemente[++dreapta];
        for(j = dreapta - 1; j >= stanga && comparare_nume(elemente[j], element) > 0; --j){
                elemente[j + 1] = elemente[j];
        }
        elemente[j + 1] = element;
    
        element = elemente[--stanga];
        for(j = stanga + 1; j <= dreapta && comparare_nume(elemente[j], element) < 0; ++j){
            elemente[j - 1] = elemente[j];
        }
        elemente[j - 1] = element;
    }
}
int comparare(ELEMENT el1, ELEMENT el2){
    if(el1.medie < 5 && el2.medie > 4) return -1;
    if(el2.medie < 5 && el1.medie > 4) return 1;

    if(el1.gen == F && el2.gen == M) return -1;
    if(el2.gen == F && el1.gen == M) return 1;

    return strcmp(el1.nume, el2.nume);

}
void sortare_specifica(ELEMENT *elemente, int numar_elemente){
    int i, j; ELEMENT element;
    for(i = 1; i < numar_elemente; ++i){
        element = elemente[i];
        for(j = i - 1; j >= 0 && comparare(elemente[j], element) > 0; --j){
            elemente[j + 1] = elemente[j];
        }
        elemente[j + 1] = element;
    }
}
void gets(char *sir){
    fgets(sir, 100, stdin);
    sir[strcspn(sir, "\n\r")] = 0;
}
int cauta_nume(const char *nume, ELEMENT *elemente, int numar_elemente){
    int i;
    for(i = 0; i < numar_elemente; ++i)
        if(strcmp(elemente[i].nume, nume) == 0) return i;
    return -1;
}

int main(){
    ELEMENT elemente[100]; int numar_elemente = 0;
    citire(elemente, &numar_elemente);
    char nume1[100], nume2[100];
    gets(nume1); gets(nume2);
    sortare_dupa_nume(elemente, numar_elemente);
    printf("%d\n", cauta_nume(nume1, elemente, numar_elemente));
    sortare_specifica(elemente, numar_elemente);
    printf("%d\n", cauta_nume(nume2, elemente, numar_elemente));
    return 0;
}