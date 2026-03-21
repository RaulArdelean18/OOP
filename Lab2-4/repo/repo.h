#ifndef OOP_REPO_H
#define OOP_REPO_H

#include "../utils/vector.h"
#include "../domain/car.h"

/**
 * Tip de date care modeleaza repository-ul de masini
 *
 * campuri:
 * - masini: vectorul dinamic in care sunt memorate toate masinile
 */
typedef struct {
    vector masini;
} Repo;

void init_repo(Repo *repo);

void distruge_repo(Repo *repo);

int get_lungime_repo(const Repo *repo);

void adauga_masina_repo(Repo *repo, Masina m);

int cauta_masina_repo(const Repo *repo, const char *nr_inmatriculare);

int actualizeaza_masina_repo(Repo *repo, const char *nr_inmatriculare, const char *model_nou,
                             const char *categorie_noua);

int inchiriaza_masina_repo(Repo *repo, const char *nr_inmatriculare);

int returneaza_masina_repo(Repo *repo, const char *nr_inmatriculare);

Masina *get_masina_din_repo(const Repo *repo, int pozitie);

#endif
