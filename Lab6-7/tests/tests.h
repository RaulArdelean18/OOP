#ifndef LAB6_7_TESTS_H
#define LAB6_7_TESTS_H

void test_domain();
void test_domain_default_constructor();
void test_domain_operator_equal();
void test_domain_copy_constructor();

void test_repo_adauga_si_cauta();
void test_repo_exceptii();
void test_repo_sterge_si_modifica();

void test_service_crud();
void test_service_exceptii();
void test_service_filtrari();
void test_service_sortari();
void test_service_sortare_an_gen();
void test_service_elemente_identice();
void test_cmp_functions();
void test_cmp_an_gen();

void test_validator();

void test_cos_goleste();
void test_cos_adauga_in_cos();
void test_cos_adauga_inexistent();
void test_cos_genereaza();
void test_cos_genereaza_biblioteca_goala();
void test_cos_exporta_csv();
void test_cos_exporta_html();
void test_cos_exporta_format_invalid();
void test_gen_frequences();

void test_undo_adauga();
void test_undo_sterge();
void test_undo_modifica();
void test_undo_multiplu();
void test_undo_lista_goala();
void test_salveaza_si_incarca_fisier();
void test_incarca_fisier_inexistent();
void test_salveaza_fisier_continut();

void ruleaza_toate_testele();

#endif //LAB6_7_TESTS_H