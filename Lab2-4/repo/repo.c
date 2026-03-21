#include "repo.h"
#include <stdlib.h>
#include <string.h>

/**
 * Functia de destroy TElem
 * @param elem: TElemul pe care vrem sa il distrugem
 */
static void destroy_masina_elem(TElem elem) {
    Masina *m = (Masina *) elem;
    distruge_masina(m);
    free(m);
}

/**
 * Initializeaza repository-ul cu un vector dinamic gol
 */
void init_repo(Repo *repo) {
    repo->masini = creeaza_vector(2);
}

/**
 * Elibereaza memoria asociata repository-ului
 */
void distruge_repo(Repo *repo) {
    distruge_vector_cu_elemente(&repo->masini, destroy_masina_elem);
}

/**
 * Returneaza numarul de masini memorate in repository
 */
int get_lungime_repo(const Repo *repo) {
    return get_lungime_vector(&repo->masini);
}

/**
 * Adauga o masina la finalul colectiei
 */
void adauga_masina_repo(Repo *repo, Masina m) {
    Masina *copie = (Masina *) malloc(sizeof(Masina));
    *copie = copiaza_masina(&m);
    adauga_elem_vector(&repo->masini, copie);
}

/**
 * Cauta masina dupa numarul de inmatriculare
 * Returneaza pozitia daca masina exista, altfel -1
 */
int cauta_masina_repo(const Repo *repo, const char *nr_inmatriculare) {
    for (int i = 0; i < get_lungime_vector(&repo->masini); i++) {
        Masina *m = (Masina *) get_elem_vector(&repo->masini, i);
        if (strcmp(get_nr_inmatriculare(m), nr_inmatriculare) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Actualizeaza modelul si categoria unei masini existente
 */
int actualizeaza_masina_repo(Repo *repo, const char *nr_inmatriculare, const char *model_nou,
                            const char *categorie_noua) {
    int pozitie = cauta_masina_repo(repo, nr_inmatriculare);
    if (pozitie == -1) {
        return 0;
    }

    Masina *m = get_masina_din_repo(repo, pozitie);
    set_model(m, model_nou);
    set_categorie(m, categorie_noua);
    return 1;
}

/**
 * Marcheaza masina drept inchiriata
 */
int inchiriaza_masina_repo(Repo *repo, const char *nr_inmatriculare) {
    int pozitie = cauta_masina_repo(repo, nr_inmatriculare);
    if (pozitie == -1) {
        return 0;
    }

    Masina *m = get_masina_din_repo(repo, pozitie);
    set_inchiriata(m, 1);
    return 1;
}

/**
 * Marcheaza masina drept disponibila
 */
int returneaza_masina_repo(Repo *repo, const char *nr_inmatriculare) {
    int pozitie = cauta_masina_repo(repo, nr_inmatriculare);
    if (pozitie == -1) {
        return 0;
    }

    Masina *m = get_masina_din_repo(repo, pozitie);
    set_inchiriata(m, 0);
    return 1;
}

/**
 * Returneaza masina de pe pozitia data
 */
Masina *get_masina_din_repo(const Repo *repo, int pozitie) {
    return (Masina *) get_elem_vector(&repo->masini, pozitie);
}
