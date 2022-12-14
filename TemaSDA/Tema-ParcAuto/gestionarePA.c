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
void adauga_parc_in_complex(COMPLEX_AUTO complex, PARC_AUTO parc) {
    if(complex == NULL) throw_error("Complex is NULL");
    if(parc == NULL) throw_error("Parc is NULL");
    if(complex -> numar_parcuri == 5) throw_error("Complex is full");
    complex -> parcuri[complex -> numar_parcuri++] = parc;
}
int este_parc_in_complex(COMPLEX_AUTO complex, int ID) {
    int i; if(complex == NULL) throw_error("Complex is NULL");
    for(i = 0; i < complex -> numar_parcuri; ++i) 
        if(complex -> parcuri[i] -> ID == ID) return i;
    return -1;
}
MASINA scoate_masina_dupa_ID_PARC(COMPLEX_AUTO complex, int ID) {
    if(complex == NULL) throw_error("Complex is NULL");
    int index = este_parc_in_complex(complex, ID);
    if(index == -1) throw_error("The park doesn't exist");
    
    return pop(complex -> parcuri[index] -> masini);
}
void dealloc_complex(COMPLEX_AUTO complex) {
    int i;
    for(i = 0; i < complex -> numar_parcuri; ++i) {
        dealloc_stack(complex -> parcuri[i] -> masini);
        free(complex -> parcuri[i]);
    }
    free(complex);
}
void dealloc_parc(PARC_AUTO parc) {
    dealloc_stack(parc -> masini);
    free(parc);
}