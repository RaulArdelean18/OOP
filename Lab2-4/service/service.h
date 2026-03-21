#ifndef OOP_SERVICE_H
#define OOP_SERVICE_H
#include "../repo/repo.h"

/**
 * Tip de date care modeleaza stratul service
 *
 * campuri:
 * - repo: pointer catre repository-ul aplicatiei
 */
typedef struct {
    Repo *repo;
} Service;

void init_service(Service *srv, Repo *repo);
int service_adauga_masina(Service *srv, const char *nr_inmatriculare, const char *model, const char *categorie);
int service_actualizeaza_masina(Service *srv, const char *nr_inmatriculare, const char *model_nou,
                                const char *categorie_noua);
int service_inchiriaza_masina(Service *srv, const char *nr_inmatriculare);
int service_returneaza_masina(Service *srv, const char *nr_inmatriculare);
int service_get_lungime(Service *srv);
Masina *service_get_masina(Service *srv, int pozitie);

/**
 * Construieste un vector cu toate masinile al caror model este egal cu modelul dat.
 *
 * param srv: pointer la service
 * param model: modelul dupa care se face filtrarea
 *
 * return: vector de elemente de tip Masina* ce contine doar masinile care respecta criteriul;
 *         vectorul returnat contine doar referinte la masinile din repository, deci se distruge
 *         numai containerul, nu si elementele lui
 */
vector service_filtreaza_masini_dupa_model(Service *srv, const char *model);

/**
 * Construieste un vector cu toate masinile din categoria data.
 *
 * param srv: pointer la service
 * param categorie: categoria dupa care se face filtrarea
 *
 * return: vector de elemente de tip Masina* ce contine doar masinile care respecta criteriul;
 *         vectorul returnat contine doar referinte la masinile din repository, deci se distruge
 *         numai containerul, nu si elementele lui
 */
vector service_filtreaza_masini_dupa_categorie(Service *srv, const char *categorie);

/**
 * Construieste o copie sortata a listei de masini dupa model.
 *
 * param srv: pointer la service
 * param crescator: 1 pentru ordine crescatoare, 0 pentru ordine descrescatoare
 *
 * return: vector de elemente de tip Masina* ordonat dupa model; vectorul contine doar referinte
 *         la masinile din repository, deci se distruge numai containerul, nu si elementele lui
 */
vector service_sorteaza_masini_dupa_model(Service *srv, int crescator);

/**
 * Construieste o copie sortata a listei de masini dupa categorie.
 *
 * param srv: pointer la service
 * param crescator: 1 pentru ordine crescatoare, 0 pentru ordine descrescatoare
 *
 * return: vector de elemente de tip Masina* ordonat dupa categorie; vectorul contine doar referinte
 *         la masinile din repository, deci se distruge numai containerul, nu si elementele lui
 */
vector service_sorteaza_masini_dupa_categorie(Service *srv, int crescator);

#endif
