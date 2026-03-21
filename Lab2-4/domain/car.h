#ifndef OOP_CAR_H
#define OOP_CAR_H

/**
 * Tipul de date care modeleaza o masina din firma de inchirieri
 *
 * campuri:
 * - nr_inmatriculare: numarul de inmatriculare al masinii
 * - model: modelul masinii
 * - categorie: categoria masinii
 * - inchiriata: starea masinii => 0 -> masina este disponibila, 1 -> masina este inchiriata
 */
typedef struct {
    char *nr_inmatriculare;
    char *model;
    char *categorie;
    int inchiriata;
} Masina;

/**
 * Creeaza o masina cu valorile primite
 *
 * @param nr_inmatriculare: sir de caractere, numarul de inmatriculare al masinii
 * @param model: sir de caractere, modelul masinii
 * @param categorie: sir de caractere, categoria masinii
 * @param inchiriata: int, starea masinii
 *      0 -> disponibila
 *      1 -> inchiriata
 *
 * return: o structura de tip Masina initializata cu valorile date
 */
Masina creeaza_masina(const char *nr_inmatriculare, const char *model, const char *categorie, int inchiriata);

/**
 * Getteri
 */
const char *get_nr_inmatriculare(const Masina *m);

const char *get_model(const Masina *m);

const char *get_categorie(const Masina *m);

int get_inchiriata(const Masina *m);

/**
 * Setteri
 */
void set_model(Masina *m, const char *model);

void set_categorie(Masina *m, const char *categorie);

void set_inchiriata(Masina *m, int inchiriata);

void distruge_masina(Masina *m);

Masina copiaza_masina(const Masina *m);

#endif
