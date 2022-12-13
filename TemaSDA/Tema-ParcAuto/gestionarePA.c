#include <string.h>
#include "stiva.h"
#include "gestionarePA.h"

define_stack(MASINA)

struct parc_auto{
    int ID;
    Stack(MASINA) masini;
};

struct complex_auto {
    PARC_AUTO parcuri[5];
    int numar_parcuri;
};

COMPLEX_AUTO init_complex_auto() {
    COMPLEX_AUTO ca = (COMPLEX_AUTO)malloc(sizeof(struct complex_auto));
    if(ca == NULL) throw_error("Not enough space");

    ca -> numar_parcuri = 0;
    return ca;
}
PARC_AUTO init_parc_auto(int ID) {
    PARC_AUTO pa = (PARC_AUTO)malloc(sizeof(struct parc_auto));
    if(pa == NULL) throw_error("Not enough space");

    pa -> ID = ID;
    pa -> masini = new_stack(MASINA);
    return pa;
}
MASINA new_masina(char *inmatriculare) {
    MASINA masina;
    strcpy(masina.numar_inmatriculare, inmatriculare);
    return masina;
}
void adauga_masina_in_parc(PARC_AUTO parc, MASINA masina) {
    if(parc == NULL) throw_error("Park is not initialized");
    push(parc -> masini, masina);
}