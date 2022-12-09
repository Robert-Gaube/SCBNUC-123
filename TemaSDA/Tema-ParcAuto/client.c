#include <stdio.h>
#include "stiva.h"

typedef struct {
    char numar_inmatriculare[9];
}MASINA;

define_stack(MASINA);

typedef struct {
    int ID;
    Stack(MASINA) masini;
}PARC_AUTO;


int main() {

    return 0;
}