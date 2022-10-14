#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "EleviMedie.txt"

typedef struct{
    char nume[300];
    double medie;
}ELEMENT;

int comp1 = 0, comp2 = 0;

void throw_error(const char *msg){
    printf("Eroare: %s\n", msg);
    exit(1);
}
void afisare_elemente(ELEMENT *elemente, int nr){
    int i;
    for(i = 0; i < nr; ++i){
        printf("%s: %lf\n", elemente[i].nume, elemente[i].medie);
    }
}
void citire(ELEMENT *elemente, int *nr){
    FILE *in = fopen(FILENAME, "r");
    if(in == NULL) throw_error("Fisierul nu a putut fi deschis");
    int i = 0;
    while(fgets(elemente[i].nume, 300, in)){
        elemente[i].nume[strcspn(elemente[i].nume, "\r\n")] = 0;
        if(fscanf(in, "%lf", &elemente[i].medie) != 1) throw_error("Something went wrong :/");
        fgetc(in); // Get newline
        i++;
    }
    *nr = i;
    if(fclose(in) != 0) throw_error("Fisierul nu a putut fi inchis");
}
int cautare_binara(ELEMENT *elemente, int n, double medie){
    int stanga = 0, mid, dreapta = n;
    while(stanga < dreapta){
        comp1++;
        mid = (stanga + dreapta) / 2;
        comp1++;
        if(elemente[mid].medie == medie) return mid;
        if(medie > elemente[mid].medie) dreapta = mid;
        else stanga = mid + 1;
        comp1++;
    }
    return -1;
}
int cautare_interpolare(ELEMENT *elemente, int n, double medie){
    int stanga = 0, mid, dreapta = n;
    while(stanga < dreapta){
        comp2++;
        mid = stanga + (medie - elemente[stanga].medie) * (dreapta - stanga) / (elemente[dreapta].medie - elemente[stanga].medie);
        comp2++;
        if(elemente[mid].medie == medie) return mid;
        if(medie > elemente[mid].medie) dreapta = mid;
        else stanga = mid + 1;
        comp2++;
    }
    return -1;
}
int main(){
    ELEMENT *elemente = (ELEMENT*)malloc(sizeof(ELEMENT) * 5010);
    if(elemente == NULL) throw_error("Nu exista suficient spatiu");
    int numar_elemente;
    citire(elemente, &numar_elemente);
    printf("Dupa %d comparatii: %d\n", comp1, cautare_binara(elemente, numar_elemente, 9.7));
    printf("Dupa %d comparatii: %d\n", comp2, cautare_interpolare(elemente, numar_elemente, 9.7));
    free(elemente);
    return 0;
}