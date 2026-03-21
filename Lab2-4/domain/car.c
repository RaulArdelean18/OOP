#include "car.h"
#include <stdlib.h>
#include <string.h>

static char *aloca_si_copiaza(const char *s) {
    size_t len = strlen(s);
    char *copie = (char *) malloc((len + 1) * sizeof(char));
    strcpy(copie, s);
    return copie;
}

/**
 * Creeaza si returneaza o masina noua.
 *
 * @param nr_inmatriculare - sir de caractere, numarul de inmatriculare al masinii
 * @param model - sir de caractere, modelul masinii
 * @param categorie - sir de caractere, categoria masinii
 * @param inchiriata - int, starea masinii:
 *      0 -> disponibila
 *      1 -> inchiriata
 *
 * returneaza o masina initializata cu valorile primite
 */
Masina creeaza_masina(const char *nr_inmatriculare, const char *model, const char *categorie, int inchiriata) {
    Masina car;
    car.nr_inmatriculare = aloca_si_copiaza(nr_inmatriculare);
    car.model = aloca_si_copiaza(model);
    car.categorie = aloca_si_copiaza(categorie);
    car.inchiriata = inchiriata;
    return car;
}

/**
 * Copy function
 * @param m: Masina
 * @return copie la @m
 */
Masina copiaza_masina(const Masina *m) {
    return creeaza_masina(m->nr_inmatriculare, m->model, m->categorie, m->inchiriata);
}

/**
 * Distrug masina @m
 * @param m: masina care vrem sa o distrugem
 */
void distruge_masina(Masina *m) {
    free(m->nr_inmatriculare);
    free(m->model);
    free(m->categorie);
    m->nr_inmatriculare = NULL;
    m->model = NULL;
    m->categorie = NULL;
    m->inchiriata = 0;
}

/**
 * Returneaza numarul de inmatriculare al masinii @m
 *
 * @param m - pointer la masina
 *
 * returneaza sirul de caractere salvat in campul nr_inmatriculare
 */
const char *get_nr_inmatriculare(const Masina *m) {
    return m->nr_inmatriculare;
}

/**
 * Returneaza modelul masinii @m
 *
 * @param m - pointer la masina
 *
 * returneaza sirul de caractere salvat in campul model
 */
const char *get_model(const Masina *m) {
    return m->model;
}

/**
 * Returneaza categoria masinii @m
 *
 * @param m - pointer la masina
 *
 * returneaza sirul de caractere salvat in campul categorie
 */
const char *get_categorie(const Masina *m) {
    return m->categorie;
}

/**
 * Returneaza starea de inchiriere a masinii @m
 *
 * @param m - pointer la masina
 *
 * returneaza:
 *      0 daca masina este disponibila
 *      1 daca masina este inchiriata
 */
int get_inchiriata(const Masina *m) {
    return m->inchiriata;
}

/**
 * Modifica modelul masinii @m
 *
 * @param m - pointer la masina care va fi modificata
 * model - noul model al masinii
 *
 * efect: campul model al masinii devine model
 */
void set_model(Masina *m, const char *model) {
    free(m->model);
    m->model = aloca_si_copiaza(model);
}

/**
 * Modifica categoria masinii @m
 *
 * @param m - pointer la masina care va fi modificata
 * categorie - noua categorie a masinii
 *
 * efect: campul categorie al masinii devine categorie
 */
void set_categorie(Masina *m, const char *categorie) {
    free(m->categorie);
    m->categorie = aloca_si_copiaza(categorie);
}

/**
 * Modifica starea de inchiriere a masinii @m
 *
 * @param m - pointer la masina care va fi modificata
 * inchiriata - noua stare a masinii
 *      0 -> disponibila
 *      1 -> inchiriata
 *
 * efect: campul inchiriata al masinii devine valoarea inchiriata
 */
void set_inchiriata(Masina *m, int inchiriata) {
    m->inchiriata = inchiriata;
}
