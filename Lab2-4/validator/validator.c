#include "validator.h"
#include <string.h>

/**
 * Verifica daca numarul de inmatriculare este valid
 *
 * @param nr_inmatriculare - sirul care trebuie verificat
 *
 * returneaza 1 daca sirul nu este gol, altfel 0
 */
int valideaza_nr_inmatriculare(const char *nr_inmatriculare) {
    return strlen(nr_inmatriculare) > 0;
}

/**
 * Verifica daca modelul este valid
 *
 * @param model - sirul care trebuie verificat
 *
 * returneaza 1 daca sirul nu este gol, altfel 0
 */
int valideaza_model(const char *model) {
    return strlen(model) > 0;
}

/**
 * Verifica daca categoria este valida
 *
 * @param categorie - sirul care trebuie verificat
 *
 * returneaza 1 daca sirul nu este gol, altfel 0
 */
int valideaza_categorie(const char *categorie) {
    return strlen(categorie) > 0;
}

/**
 * Verifica daca toate campurile unei masini sunt valide
 *
 * @param m - pointer la masina verificata
 *
 * returneaza 1 daca toate campurile sunt valide, altfel 0
 */
int valideaza_masina(const Masina *m) {
    if (!valideaza_nr_inmatriculare(get_nr_inmatriculare(m))) {
        return 0;
    }
    if (!valideaza_model(get_model(m))) {
        return 0;
    }
    if (!valideaza_categorie(get_categorie(m))) {
        return 0;
    }
    return 1;
}
