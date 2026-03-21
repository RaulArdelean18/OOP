#include "service.h"
#include "../validator/validator.h"
#include <string.h>

/**
 * get_all function
 * @param srv: service, de unde apelez functiile
 * @return lista cu toate masinili
 */
static vector construieste_vector_cu_toate_masinile(Service *srv) {
    vector rezultat = creeaza_vector(service_get_lungime(srv) + 1);
    for (int i = 0; i < service_get_lungime(srv); i++) {
        adauga_elem_vector(&rezultat, service_get_masina(srv, i));
    }
    return rezultat;
}

/**
 * Sorteaza o lista intr-o ordine data
 * @param v : vectorul care vrem sa il sortam
 * @param cmp : comparatorul custom
 * @param crescator : in ce ordine vrem sa sortam vectorul
 */
static void sorteaza_vector(vector *v, int (*cmp)(const Masina *, const Masina *), int crescator) {
    for (int i = 0; i < get_lungime_vector(v) - 1; i++) {
        for (int j = i + 1; j < get_lungime_vector(v); j++) {
            Masina *mi = (Masina *) get_elem_vector(v, i);
            Masina *mj = (Masina *) get_elem_vector(v, j);
            int relatie = cmp(mi, mj);
            if ((crescator && relatie > 0) || (!crescator && relatie < 0)) {
                TElem aux = get_elem_vector(v, i);
                set_elem_vector(v, i, get_elem_vector(v, j));
                set_elem_vector(v, j, aux);
            }
        }
    }
}

/**
 * Compar dupa model
 * @param m1: prima masina
 * @param m2 a 2-a masina
 * @return : strcmp dintre m1 si m2
 */
static int compara_dupa_model(const Masina *m1, const Masina *m2) {
    return strcmp(get_model(m1), get_model(m2));
}

/**
 * Compar dupa categorie
 * @param m1: prima masina
 * @param m2 a 2-a masina
 * @return : strcmp dintre m1 si m2
 */
static int compara_dupa_categorie(const Masina *m1, const Masina *m2) {
    return strcmp(get_categorie(m1), get_categorie(m2));
}

/**
 * Initializeaza service-ul cu repository-ul dat
 *
 * srv - pointer la service
 * repo - pointer la repository
 *
 * efect: campul repo al service-ului va memora adresa repository-ului
 */
void init_service(Service *srv, Repo *repo) {
    srv->repo = repo;
}

/**
 * Adauga o masina noua in aplicatie
 *
 * srv - pointer la service
 * nr_inmatriculare - numarul de inmatriculare al masinii
 * model - modelul masinii
 * categorie - categoria masinii
 *
 * returneaza:
 * 1 daca masina a fost adaugata
 * 0 daca exista deja o masina cu acelasi numar de inmatriculare
 * -1 daca datele masinii sunt invalide
 */
int service_adauga_masina(Service *srv, const char *nr_inmatriculare, const char *model, const char *categorie) {
    Masina m = creeaza_masina(nr_inmatriculare, model, categorie, 0);

    if (!valideaza_masina(&m)) {
        distruge_masina(&m);
        return -1;
    }

    int pozitie = cauta_masina_repo(srv->repo, nr_inmatriculare);
    if (pozitie != -1) {
        distruge_masina(&m);
        return 0;
    }

    adauga_masina_repo(srv->repo, m);
    distruge_masina(&m);
    return 1;
}

/**
 * Actualizeaza modelul si categoria unei masini existente
 *
 * srv - pointer la service
 * nr_inmatriculare - numarul de inmatriculare al masinii cautate
 * model_nou - noul model
 * categorie_noua - noua categorie
 *
 * returneaza:
 * 1 daca masina a fost actualizata
 * 0 daca masina nu exista
 * -1 daca noile date sunt invalide
 */
int service_actualizeaza_masina(Service *srv, const char *nr_inmatriculare, const char *model_nou,
                                const char *categorie_noua) {
    int pozitie = cauta_masina_repo(srv->repo, nr_inmatriculare);
    if (pozitie == -1) {
        return 0;
    }

    Masina *veche = get_masina_din_repo(srv->repo, pozitie);
    Masina m_nou = creeaza_masina(nr_inmatriculare, model_nou, categorie_noua, get_inchiriata(veche));

    if (!valideaza_masina(&m_nou)) {
        distruge_masina(&m_nou);
        return -1;
    }

    distruge_masina(&m_nou);
    return actualizeaza_masina_repo(srv->repo, nr_inmatriculare, model_nou, categorie_noua);
}

/**
 * Inchiriaza o masina existenta, daca aceasta este disponibila
 *
 * srv - pointer la service
 * nr_inmatriculare - numarul de inmatriculare al masinii
 *
 * returneaza:
 * 1 daca masina a fost inchiriata cu succes
 * 0 daca masina nu exista
 * -1 daca masina exista, dar este deja inchiriata
 */
int service_inchiriaza_masina(Service *srv, const char *nr_inmatriculare) {
    int pozitie = cauta_masina_repo(srv->repo, nr_inmatriculare);
    if (pozitie == -1) {
        return 0;
    }

    Masina *m = get_masina_din_repo(srv->repo, pozitie);
    if (get_inchiriata(m) == 1) {
        return -1;
    }

    return inchiriaza_masina_repo(srv->repo, nr_inmatriculare);
}

/**
 * Returneaza o masina, daca aceasta este inchiriata
 *
 * srv - pointer la service
 * nr_inmatriculare - numarul de inmatriculare al masinii
 *
 * returneaza:
 * 1 daca masina a fost returnata cu succes
 * 0 daca masina nu exista
 * -1 daca masina exista, dar este deja disponibila
 */
int service_returneaza_masina(Service *srv, const char *nr_inmatriculare) {
    int pozitie = cauta_masina_repo(srv->repo, nr_inmatriculare);
    if (pozitie == -1) {
        return 0;
    }

    Masina *m = get_masina_din_repo(srv->repo, pozitie);
    if (get_inchiriata(m) == 0) {
        return -1;
    }

    return returneaza_masina_repo(srv->repo, nr_inmatriculare);
}

/**
 * Returneaza numarul de masini din aplicatie
 *
 * srv - pointer la service
 *
 * returneaza numarul curent de masini memorate
 */
int service_get_lungime(Service *srv) {
    return get_lungime_repo(srv->repo);
}

/**
 * Returneaza masina de pe pozitia data
 *
 * srv - pointer la service
 * pozitie - indexul masinii dorite
 *
 * returneaza masina de pe pozitia pozitie
 */
Masina *service_get_masina(Service *srv, int pozitie) {
    return get_masina_din_repo(srv->repo, pozitie);
}

/**
 * Returneaza lista de masini care au modelul dat
 * @param srv: service, de unde apelez functiile service
 * @param model: modelul dupa care vrea sa dau filtrare
 * @return: vector cu masinile care au modelul "model"
 */
vector service_filtreaza_masini_dupa_model(Service *srv, const char *model) {
    vector rezultat = creeaza_vector(service_get_lungime(srv) + 1);

    for (int i = 0; i < service_get_lungime(srv); i++) {
        Masina *m = service_get_masina(srv, i);
        if (strcmp(get_model(m), model) == 0) {
            adauga_elem_vector(&rezultat, m);
        }
    }

    return rezultat;
}

/**
 * Returneaza lista de masini care au categoria data
 * @param srv: service, de unde apelez functiile service
 * @param categorie: categoria dupa care vrea sa dau filtrare
 * @return: vector cu masinile care au categoria "categorie"
 */
vector service_filtreaza_masini_dupa_categorie(Service *srv, const char *categorie) {
    vector rezultat = creeaza_vector(service_get_lungime(srv) + 1);

    for (int i = 0; i < service_get_lungime(srv); i++) {
        Masina *m = service_get_masina(srv, i);
        if (strcmp(get_categorie(m), categorie) == 0) {
            adauga_elem_vector(&rezultat, m);
        }
    }

    return rezultat;
}

/**
 * Returneaza lista de masini in ordine crescatoare / descrescatoare dupa model
 * @param srv service, de unde apelez functiile service
 * @param crescator: stare, daca vrem sa sortam crescator sau descrescator
 * @return: o lista cu masinile, sortate dupa model
 */
vector service_sorteaza_masini_dupa_model(Service *srv, int crescator) {
    vector rezultat = construieste_vector_cu_toate_masinile(srv);
    sorteaza_vector(&rezultat, compara_dupa_model, crescator);
    return rezultat;
}

/**
 * Returneaza lista de masini in ordine crescatoare / descrescatoare dupa masini
 * @param srv service, de unde apelez functiile service
 * @param crescator: stare, daca vrem sa sortam crescator sau descrescator
 * @return: o lista cu masinile, sortate dupa masini
 */
vector service_sorteaza_masini_dupa_categorie(Service *srv, int crescator) {
    vector rezultat = construieste_vector_cu_toate_masinile(srv);
    sorteaza_vector(&rezultat, compara_dupa_categorie, crescator);
    return rezultat;
}
