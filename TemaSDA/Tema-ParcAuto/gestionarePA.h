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

#endif /* GESTIONAREPA_H */