#include <stdio.h>
#include "stiva.h"
#include "gestionarePA.h"

int main() {
    PARC_AUTO parc1 = init_parc_auto(1);
    PARC_AUTO parc2 = init_parc_auto(2);
    PARC_AUTO parc3 = init_parc_auto(3);
    PARC_AUTO parc4 = init_parc_auto(4);
    PARC_AUTO parc5 = init_parc_auto(5);
    PARC_AUTO parc6 = init_parc_auto(6);

    COMPLEX_AUTO complex = init_complex_auto();
    
    MASINA masina1 = new_masina("1-I");
    MASINA masina2 = new_masina("2-I");
    MASINA masina3 = new_masina("3-I");
    MASINA masina4 = new_masina("4-I");
    MASINA masina5 = new_masina("5-I");
    MASINA masina6 = new_masina("6-I");
    MASINA masina7 = new_masina("7-I");

    adauga_masina_in_parc(parc1, masina1);
    adauga_masina_in_parc(parc1, masina3);
    adauga_masina_in_parc(parc1, masina5);
    adauga_masina_in_parc(parc1, masina7);

    adauga_masina_in_parc(parc3, masina2);
    adauga_masina_in_parc(parc3, masina4);
    adauga_masina_in_parc(parc3, masina6);

    adauga_parc_in_complex(complex, parc1);
    adauga_parc_in_complex(complex, parc2);
    adauga_parc_in_complex(complex, parc3);
    adauga_parc_in_complex(complex, parc4);
    adauga_parc_in_complex(complex, parc5);

    MASINA masina_out1 = scoate_masina_dupa_ID_PARC(complex, 3);
    printf("%s\n", masina_out1.numar_inmatriculare);

    masina_out1 = scoate_masina_dupa_ID_PARC(complex, 3);
    printf("%s\n", masina_out1.numar_inmatriculare);

    dealloc_complex(complex);
    dealloc_parc(parc6);

    return 0;
}