#include "vector.h"
#include <stdlib.h>

/**
 * Creeaza un vector dinamic gol, cu capacitatea initiala specificata
 */
vector creeaza_vector(int capacitate_initiala) {
    vector v;
    v.elems = (TElem *) malloc((size_t) capacitate_initiala * sizeof(TElem));
    v.lungime = 0;
    v.capacitate = capacitate_initiala;
    return v;
}

/**
 * Elibereaza memoria ocupata de vectorul dinamic
 */
void distruge_vector(vector *v) {
    free(v->elems);
    v->elems = NULL;
    v->lungime = 0;
    v->capacitate = 0;
}

/**
 * Distrug elementele din vector
 * @param v : vectorul de TElem Masina
 * @param destroy_elem Functia de destroy, pe care o sa il apelam
 */
void distruge_vector_cu_elemente(vector *v, DestroyFunction destroy_elem) {
    for (int i = 0; i < v->lungime; i++) {
        destroy_elem(v->elems[i]);
    }
    distruge_vector(v);
}

/**
 * Returneaza lungimea curenta a vectorului
 * @param v: vectorul nostru
*/
int get_lungime_vector(const vector *v) {
    return v->lungime;
}

/**
 * Returneaza elementul de pe pozitia data
 * @param v: vectorul de TElem
 * @param pozitie: int, pozitia pe care vrem sa o accesam
 */
TElem get_elem_vector(const vector *v, int pozitie) {
    return v->elems[pozitie];
}

/**
 * Inlocuieste elementul de pe pozitia data
 * @param v: vectorul
 * @param pozitie: pozitia unde vrem sa facem inlocuirea
 * @param elem: TElem, valoarea pe care vrem sa o pune in pozitie
 */
void set_elem_vector(vector *v, int pozitie, TElem elem) {
    v->elems[pozitie] = elem;
}

/**
 * Mareste capacitatea vectorului dinamic
 * @param v: vectorul nostru
 */
void redimensioneaza_vector(vector *v) {
    int capacitate_noua = 2 * v->capacitate;
    TElem *elems_noi = (TElem *) malloc((size_t) capacitate_noua * sizeof(TElem));

    for (int i = 0; i < v->lungime; i++) {
        elems_noi[i] = v->elems[i];
    }

    free(v->elems);
    v->elems = elems_noi;
    v->capacitate = capacitate_noua;
}

/**
 * Adauga elementul la sfarsitul vectorului
 * Daca vectorul este plin, acesta este redimensionat
 * @param v: vectorul
 * @param elem: elementul care vrem sa il punem in @v
 */
void adauga_elem_vector(vector *v, TElem elem) {
    if (v->lungime == v->capacitate) {
        redimensioneaza_vector(v);
    }

    v->elems[v->lungime] = elem;
    v->lungime++;
}
