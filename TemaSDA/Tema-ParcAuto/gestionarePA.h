#ifndef GESTIONAREPA_H
#define GESTIONAREPA_H

typedef struct complex_auto* COMPLEX_AUTO;
typedef struct parc_auto* PARC_AUTO;

typedef struct {
    char numar_inmatriculare[9];
}MASINA;

MASINA new_masina(char*);
COMPLEX_AUTO init_complex_auto();
PARC_AUTO init_parc_auto(int);
void adauga_masina_in_parc(PARC_AUTO, MASINA);
void adauga_parc_in_complex(COMPLEX_AUTO, PARC_AUTO);
int este_parc_in_complex(COMPLEX_AUTO, int);
MASINA scoate_masina_dupa_ID_PARC(COMPLEX_AUTO, int);
void dealloc_complex(COMPLEX_AUTO);
void dealloc_parc(PARC_AUTO);

#endif /* GESTIONAREPA_H */