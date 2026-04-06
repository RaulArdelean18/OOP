//
// Created by Raul_A on 30/03/2026.
//

#ifndef LAB6_7_TESTS_H
#define LAB6_7_TESTS_H

#include "../domain/domain.h"
#include "../repo/repo.h"
#include "../serv/service.h"
#include "../utils/vector.h"
#include "../validator/validator.h"

void test_domain();

void test_repo_adauga_si_cauta();

void test_repo_adauga_duplicat();

void test_repo_sterge();

void test_repo_sterge_inexistent();

void test_repo_modifica();

void test_service_adauga();

void test_service_sterge();

void test_service_modifica();

void test_service_filtrare_titlu();

void test_service_filtrare_an();

void test_service_sortare_titlu();

void test_service_sortare_autor();

void test_service_sortare_an_gen_complet();

void ruleaza_toate_testele();

void test_repo_modifica_inexistent();

void test_repo_cauta_inexistent();

void test_service_filtrare_titlu_fara_rezultat();

void test_service_filtrare_an_fara_rezultat();

void test_service_sortare_pe_gol();

void test_service_sortare_an_gen_ramuri();

void test_service_sortare_an_gen_complet_2();

void test_domain_default_constructor();

void test_domain_operator_equal();

void test_domain_copy_constructor();

void test_validator();

void test_myvector_exceptii();
#endif //LAB6_7_TESTS_H
