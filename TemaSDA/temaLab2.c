/*Fisierul are urmatorul antet:

Cod  Denumire

Fiecarei ocupatii ii corespunde o linie din fisier, incepand cu a doua linie (dupa antet): cod_ocupatie nume_ocupatie. Intre cod si ocupatie este un tab, iar numele ocupatiei poate fi format din mai multe cuvinte. Presupunand ca numele nici unei ocupatii nu ocupa mai mult de 350 de caractere si nici codul mai mult de 6 caractere, se cere:

·         Sa se citeasca datele din fisier intr-un tablou de forma <cod, ocupatie >

·         Se citeste de la tastatura, de pe prima linie, codul unei ocupatii, iar de pe a doua linie un cuvant.

·         Stiind ca aceste ocupatii sunt ordonate descrescator dupa cod, sa se aplice cautarea binara performanta si sa se afiseze denumirea ocupatiei pentru orice cod citit anterior de la tastatura sau mesajul "COD INEXISTENT", in cazul in care codul nu exista in fisier.

·         Pornind de la principiul algoritmului de cautare prin tehnica fanionului sa se parcurga tabloul si sa se afiseze pe ecran, prima ocupatie care contine cuvantul citit de la tastatura (de pe a doua linie) sau mesajul "CUVANTUL NU EXISTA", in cazul in care cuvantul nu exista in fisier.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "COR_Descrescator.txt"

typedef struct{
    int cod;
    char ocupatie[350];
}ELEMENT;

void throw_error(const char* msg){
    printf("Eroare: %s\n", msg);
    exit(-1);
}

void citire(ELEMENT *elemente, int *nr_elemente){
    FILE *in = fopen(FILENAME, "r");
    if(in == NULL) throw_error("Fisierul nu s-a deschis cu succes");
    int i = 0;
    fgets(elemente[0].ocupatie, 350, in);  

    while(fscanf(in, "%d", &elemente[i].cod) == 1){
        fgetc(in); // Stergere tab
        if(fgets(elemente[i].ocupatie, 350, in) == NULL) throw_error("Format fisier nasol");
        elemente[i].ocupatie[strcspn(elemente[i++].ocupatie, "\r\n")] = 0;
    }
    *nr_elemente = i;
    if(fclose(in) != 0) throw_error("Fisierul nu s-a inchis cu succes");
}

void afisare_elemente(ELEMENT *elemente, int nr){
    int i;
    for(i = 0; i < nr; ++i){
        printf("%d: %s\n", elemente[i].cod, elemente[i].ocupatie);
    }
}
int rabin_karp(const char *haystack, const char *needle){
    long stackSize = strlen(haystack), needleSize = strlen(needle), i, searchHash = 0, needleHash = 0;
    if(stackSize < needleSize) return 0;
    long long power = 1;
    for(i = 0; i < needleSize; ++i){
        needleHash = needleHash * 128 + needle[i];
        searchHash = searchHash * 128 + haystack[i];
        power *= 128;
    }
    power /= 128;

    for(const char *p = haystack; *(p + needleSize - 1); ++p){
        if(needleHash == searchHash && strncmp(p, needle, needleSize) == 0) return 1;
        searchHash = (searchHash - *p * power) * 128 + *(p + needleSize);
    }
    return 0;
}
int cautare_cod(ELEMENT *elemente, int nr, int cod){
    int stanga = 0, dreapta = nr, mid;
    while(stanga < dreapta){
        mid = (stanga + dreapta) / 2;
        if(cod < elemente[mid].cod) stanga = mid + 1;
        else dreapta = mid;
    }
    if(dreapta >= nr) return -1;
    else if(elemente[dreapta].cod == cod) return dreapta;
    else return -1;
}
int cautare_ocupatie_cuvant(ELEMENT *elemente, int nr, const char *cuvant){
    elemente[nr].cod = 0;
    strcpy(elemente[nr].ocupatie, cuvant);
    int i = 0;
    while(rabin_karp(elemente[i].ocupatie, cuvant) == 0){
        //printf("%s\n", elemente[i].ocupatie);
        i++;
    }
    if(i >= nr) return -1;
    else return i;
}
int main(){
    ELEMENT *elemente = (ELEMENT*)malloc(sizeof(ELEMENT) * 4500);
    int numar_elemente;
    if(elemente == NULL) throw_error("Nu exista suficient spatiu");
    citire(elemente, &numar_elemente);

    int cod; char cuvant[300];
    scanf("%d", &cod);
    scanf("%s", cuvant);

    int rez = cautare_cod(elemente, numar_elemente, cod);
    if(rez == -1) printf("COD INEXISTENT\n");
    else printf("%s", elemente[rez].ocupatie);

    rez = cautare_ocupatie_cuvant(elemente, numar_elemente, cuvant);
    if(rez != -1) printf("CUVANTUL NU EXISTA");
    else printf("%s", elemente[rez].ocupatie);

    free(elemente);
    return 0;
}