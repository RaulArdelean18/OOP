#include "test.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../domain/car.h"
#include "../validator/validator.h"
#include "../utils/vector.h"
#include "../repo/repo.h"
#include "../service/service.h"

static void destroy_int(TElem elem) {
    free(elem);
}

/*
 * Testeaza crearea unei masini, getterii si setterii
 */
static void test_domain() {
    Masina m = creeaza_masina("MM06WDK", "Logan", "mini", 0);

    assert(strcmp(get_nr_inmatriculare(&m), "MM06WDK") == 0);
    assert(strcmp(get_model(&m), "Logan") == 0);
    assert(strcmp(get_categorie(&m), "mini") == 0);
    assert(get_inchiriata(&m) == 0);

    Masina copie = copiaza_masina(&m);
    assert(strcmp(get_nr_inmatriculare(&copie), "MM06WDK") == 0);
    assert(copie.nr_inmatriculare != m.nr_inmatriculare);

    set_model(&m, "BMWX5");
    set_categorie(&m, "suv");
    set_inchiriata(&m, 1);

    assert(strcmp(get_model(&m), "BMWX5") == 0);
    assert(strcmp(get_categorie(&m), "suv") == 0);
    assert(get_inchiriata(&m) == 1);

    distruge_masina(&copie);
    distruge_masina(&m);
}

/**
 * Testeaza validarea campurilor unei masini
 */
static void test_validator() {
    Masina m_valid = creeaza_masina("CJ01ABC", "Logan", "mini", 0);
    Masina m_nr_invalid = creeaza_masina("", "Logan", "mini", 0);
    Masina m_model_invalid = creeaza_masina("CJ01ABC", "", "mini", 0);
    Masina m_categorie_invalida = creeaza_masina("CJ01ABC", "Logan", "", 0);

    assert(valideaza_nr_inmatriculare("CJ01ABC") == 1);
    assert(valideaza_nr_inmatriculare("") == 0);

    assert(valideaza_model("Logan") == 1);
    assert(valideaza_model("") == 0);

    assert(valideaza_categorie("mini") == 1);
    assert(valideaza_categorie("") == 0);

    assert(valideaza_masina(&m_valid) == 1);
    assert(valideaza_masina(&m_nr_invalid) == 0);
    assert(valideaza_masina(&m_model_invalid) == 0);
    assert(valideaza_masina(&m_categorie_invalida) == 0);

    distruge_masina(&m_valid);
    distruge_masina(&m_nr_invalid);
    distruge_masina(&m_model_invalid);
    distruge_masina(&m_categorie_invalida);
}

/**
 * Testeaza vectorul dinamic generic
 */
static void test_vector() {
    vector v = creeaza_vector(2);

    assert(get_lungime_vector(&v) == 0);

    int *a = (int *) malloc(sizeof(int));
    int *b = (int *) malloc(sizeof(int));
    int *c = (int *) malloc(sizeof(int));
    int *d = (int *) malloc(sizeof(int));
    *a = 10;
    *b = 20;
    *c = 30;
    *d = 40;

    adauga_elem_vector(&v, a);
    adauga_elem_vector(&v, b);

    assert(get_lungime_vector(&v) == 2);
    assert(*(int *) get_elem_vector(&v, 0) == 10);
    assert(*(int *) get_elem_vector(&v, 1) == 20);

    adauga_elem_vector(&v, c);
    assert(get_lungime_vector(&v) == 3);
    assert(*(int *) get_elem_vector(&v, 2) == 30);

    set_elem_vector(&v, 1, d);
    assert(*(int *) get_elem_vector(&v, 1) == 40);

    free(b);
    distruge_vector_cu_elemente(&v, destroy_int);
}

/**
 * Testeaza repository-ul
 */
static void test_repo() {
    Repo repo;
    init_repo(&repo);

    assert(get_lungime_repo(&repo) == 0);

    Masina m1 = creeaza_masina("CJ10AAA", "Logan", "mini", 0);
    Masina m2 = creeaza_masina("CJ20BBB", "X5", "suv", 0);

    adauga_masina_repo(&repo, m1);
    adauga_masina_repo(&repo, m2);

    distruge_masina(&m1);
    distruge_masina(&m2);

    assert(get_lungime_repo(&repo) == 2);
    assert(cauta_masina_repo(&repo, "CJ10AAA") == 0);
    assert(cauta_masina_repo(&repo, "CJ20BBB") == 1);
    assert(cauta_masina_repo(&repo, "NUEXISTA") == -1);

    assert(actualizeaza_masina_repo(&repo, "CJ10AAA", "Sandero", "mini") == 1);

    Masina *m = get_masina_din_repo(&repo, 0);
    assert(strcmp(get_model(m), "Sandero") == 0);
    assert(strcmp(get_categorie(m), "mini") == 0);

    assert(inchiriaza_masina_repo(&repo, "CJ10AAA") == 1);
    m = get_masina_din_repo(&repo, 0);
    assert(get_inchiriata(m) == 1);

    assert(returneaza_masina_repo(&repo, "CJ10AAA") == 1);
    m = get_masina_din_repo(&repo, 0);
    assert(get_inchiriata(m) == 0);

    assert(actualizeaza_masina_repo(&repo, "MASINAINEXISTENTA", "A", "B") == 0);
    assert(inchiriaza_masina_repo(&repo, "MASINAINEXISTENTA") == 0);
    assert(returneaza_masina_repo(&repo, "MASINAINEXISTENTA") == 0);

    distruge_repo(&repo);
}

/**
 * Testeaza filtrarea de la sortare
 */
static void test_service_filtrare_sortare() {
    Repo repo;
    init_repo(&repo);
    Service srv;
    init_service(&srv, &repo);

    assert(service_adauga_masina(&srv, "CJ01AAA", "Logan", "mini") == 1);
    assert(service_adauga_masina(&srv, "CJ02BBB", "Duster", "suv") == 1);
    assert(service_adauga_masina(&srv, "CJ03CCC", "Logan", "sport") == 1);
    assert(service_adauga_masina(&srv, "CJ04DDD", "Arteon", "berlina") == 1);

    vector filtrate_model = service_filtreaza_masini_dupa_model(&srv, "Logan");
    assert(get_lungime_vector(&filtrate_model) == 2);
    assert(strcmp(get_nr_inmatriculare((Masina *) get_elem_vector(&filtrate_model, 0)), "CJ01AAA") == 0);
    assert(strcmp(get_nr_inmatriculare((Masina *) get_elem_vector(&filtrate_model, 1)), "CJ03CCC") == 0);
    distruge_vector(&filtrate_model);

    vector filtrate_model_goale = service_filtreaza_masini_dupa_model(&srv, "Inexistent");
    assert(get_lungime_vector(&filtrate_model_goale) == 0);
    distruge_vector(&filtrate_model_goale);

    vector filtrate_categorie = service_filtreaza_masini_dupa_categorie(&srv, "suv");
    assert(get_lungime_vector(&filtrate_categorie) == 1);
    assert(strcmp(get_nr_inmatriculare((Masina *) get_elem_vector(&filtrate_categorie, 0)), "CJ02BBB") == 0);
    distruge_vector(&filtrate_categorie);

    vector filtrate_categorie_goale = service_filtreaza_masini_dupa_categorie(&srv, "lux");
    assert(get_lungime_vector(&filtrate_categorie_goale) == 0);
    distruge_vector(&filtrate_categorie_goale);

    vector sortate_model_crescator = service_sorteaza_masini_dupa_model(&srv, 1);
    assert(strcmp(get_model((Masina *) get_elem_vector(&sortate_model_crescator, 0)), "Arteon") == 0);
    assert(strcmp(get_model((Masina *) get_elem_vector(&sortate_model_crescator, 1)), "Duster") == 0);
    assert(strcmp(get_model((Masina *) get_elem_vector(&sortate_model_crescator, 2)), "Logan") == 0);
    assert(strcmp(get_model((Masina *) get_elem_vector(&sortate_model_crescator, 3)), "Logan") == 0);
    distruge_vector(&sortate_model_crescator);

    vector sortate_model_descrescator = service_sorteaza_masini_dupa_model(&srv, 0);
    assert(strcmp(get_model((Masina *) get_elem_vector(&sortate_model_descrescator, 0)), "Logan") == 0);
    assert(strcmp(get_model((Masina *) get_elem_vector(&sortate_model_descrescator, 3)), "Arteon") == 0);
    distruge_vector(&sortate_model_descrescator);

    vector sortate_categorie_crescator = service_sorteaza_masini_dupa_categorie(&srv, 1);
    assert(strcmp(get_categorie((Masina *) get_elem_vector(&sortate_categorie_crescator, 0)), "berlina") == 0);
    assert(strcmp(get_categorie((Masina *) get_elem_vector(&sortate_categorie_crescator, 1)), "mini") == 0);
    assert(strcmp(get_categorie((Masina *) get_elem_vector(&sortate_categorie_crescator, 2)), "sport") == 0);
    assert(strcmp(get_categorie((Masina *) get_elem_vector(&sortate_categorie_crescator, 3)), "suv") == 0);
    distruge_vector(&sortate_categorie_crescator);

    vector sortate_categorie_descrescator = service_sorteaza_masini_dupa_categorie(&srv, 0);
    assert(strcmp(get_categorie((Masina *) get_elem_vector(&sortate_categorie_descrescator, 0)), "suv") == 0);
    assert(strcmp(get_categorie((Masina *) get_elem_vector(&sortate_categorie_descrescator, 3)), "berlina") == 0);
    distruge_vector(&sortate_categorie_descrescator);

    distruge_repo(&repo);
}

/**
 * Testeaza service-ul
 */
static void test_service() {
    Repo repo;
    init_repo(&repo);

    Service srv;
    init_service(&srv, &repo);

    assert(service_get_lungime(&srv) == 0);

    assert(service_adauga_masina(&srv, "B01AAA", "Logan", "mini") == 1);
    assert(service_get_lungime(&srv) == 1);

    assert(service_adauga_masina(&srv, "B01AAA", "AltModel", "suv") == 0);
    assert(service_get_lungime(&srv) == 1);

    assert(service_adauga_masina(&srv, "", "Logan", "mini") == -1);
    assert(service_adauga_masina(&srv, "B02BBB", "", "mini") == -1);
    assert(service_adauga_masina(&srv, "B03CCC", "Logan", "") == -1);

    assert(service_actualizeaza_masina(&srv, "B01AAA", "BMWX5", "suv") == 1);

    Masina *m = service_get_masina(&srv, 0);
    assert(strcmp(get_model(m), "BMWX5") == 0);
    assert(strcmp(get_categorie(m), "suv") == 0);

    assert(service_actualizeaza_masina(&srv, "NUEXISTA", "A", "B") == 0);
    assert(service_actualizeaza_masina(&srv, "B01AAA", "", "suv") == -1);
    assert(service_actualizeaza_masina(&srv, "B01AAA", "Audi", "") == -1);

    assert(service_inchiriaza_masina(&srv, "B01AAA") == 1);
    m = service_get_masina(&srv, 0);
    assert(get_inchiriata(m) == 1);

    assert(service_inchiriaza_masina(&srv, "B01AAA") == -1);
    assert(service_inchiriaza_masina(&srv, "NUEXISTA") == 0);

    assert(service_returneaza_masina(&srv, "B01AAA") == 1);
    m = service_get_masina(&srv, 0);
    assert(get_inchiriata(m) == 0);

    assert(service_returneaza_masina(&srv, "B01AAA") == -1);
    assert(service_returneaza_masina(&srv, "NUEXISTA") == 0);

    distruge_repo(&repo);

    test_service_filtrare_sortare();
}

/**
 * Ruleaza toate testele aplicatiei
 */
void run_all_tests() {
    test_domain();
    test_validator();
    test_vector();
    test_repo();
    test_service();

    printf("Toate testele au trecut cu succes.\n");
}
