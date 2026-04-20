#include "tests.h"
#include "../Domain/domain.h"
#include "../repo/repo.h"
#include "../serv/service.h"
#include "../validator/validator.h"
#include "../exceptions/exceptions.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

void test_domain() {
    Domain c("Ion", "Rebreanu", "roman", 1920);
    assert(c.get_titlu() == "Ion");
    assert(c.get_autor() == "Rebreanu");
    assert(c.get_gen() == "roman");
    assert(c.get_anul_ap() == 1920);

    c.setter_titlu("Morometii");
    c.setter_autor("Preda");
    c.setter_gen("epic");
    c.setter_anul_ap(1955);

    assert(c.get_titlu() == "Morometii");
    assert(c.get_autor() == "Preda");
    assert(c.get_gen() == "epic");
    assert(c.get_anul_ap() == 1955);
}

void test_domain_default_constructor() {
    Domain d;
    assert(d.get_titlu().empty());
    assert(d.get_autor().empty());
    assert(d.get_gen().empty());
    assert(d.get_anul_ap() == 0);
}

void test_domain_operator_equal() {
    Domain a("t1", "a1", "g1", 2000);
    Domain b("t2", "a2", "g2", 2001);
    b = a;
    assert(b.get_titlu() == "t1");
    assert(b.get_autor() == "a1");
    assert(b.get_gen() == "g1");
    assert(b.get_anul_ap() == 2000);
    //b = b; // self-assignment
    assert(b.get_titlu() == "t1");
}

void test_domain_copy_constructor() {
    Domain a("Ion", "Pop", "Drama", 1999);
    Domain b(a);
    assert(b.get_titlu() == "Ion");
    assert(b.get_autor() == "Pop");
    assert(b.get_gen() == "Drama");
    assert(b.get_anul_ap() == 1999);
}

void test_repo_adauga_si_cauta() {
    Repo repo;
    repo.adauga(Domain("Ion", "Rebreanu", "roman", 1920));
    repo.adauga(Domain("Baltagul", "Sadoveanu", "roman", 1930));
    assert(repo.get_all().size() == 2);
    assert(repo.cauta("Ion").get_autor() == "Rebreanu");
    assert(repo.cauta("Baltagul").get_anul_ap() == 1930);
}

void test_repo_exceptii() {
    Repo repo;
    repo.adauga(Domain("Ion", "Rebreanu", "roman", 1920));

    bool aruncat = false;
    try { repo.adauga(Domain("Ion", "Rebreanu", "roman", 1920)); }
    catch (const DuplicatException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { repo.cauta("Morometii"); }
    catch (const NotFoundException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { repo.sterge("Morometii"); }
    catch (const NotFoundException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { repo.modifica("Morometii", Domain("Nou", "Autor", "gen", 2000)); }
    catch (const NotFoundException&) { aruncat = true; }
    assert(aruncat);
}

void test_repo_sterge_si_modifica() {
    Repo repo;
    repo.adauga(Domain("Ion", "Rebreanu", "roman", 1920));
    repo.adauga(Domain("Baltagul", "Sadoveanu", "roman", 1930));

    repo.sterge("Ion");
    assert(repo.get_all().size() == 1);
    assert(repo.get_all()[0].get_titlu() == "Baltagul");

    repo.modifica("Baltagul", Domain("Baltagul Nou", "Sadoveanu Nou", "drama", 2000));
    const Domain& c = repo.cauta("Baltagul Nou");
    assert(c.get_titlu() == "Baltagul Nou");
    assert(c.get_anul_ap() == 2000);
}

void test_service_crud() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("Ion", "Rebreanu", "roman", 1920);
    srv.adauga_carte("Baltagul", "Sadoveanu", "roman", 1930);
    assert(srv.get_all().size() == 2);
    assert(srv.cauta_carte("Ion").get_autor() == "Rebreanu");

    srv.sterge_carte("Ion");
    assert(srv.get_all().size() == 1);

    srv.modifica_carte("Baltagul", "Morometii", "Marin Preda", "roman", 1955);
    assert(srv.cauta_carte("Morometii").get_autor() == "Marin Preda");
}

void test_service_exceptii() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("Ion", "Rebreanu", "roman", 1920);

    bool aruncat = false;
    try { srv.cauta_carte("Morometii"); } catch (const NotFoundException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { srv.adauga_carte("Ion", "Rebreanu", "roman", 1920); } catch (const DuplicatException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { srv.sterge_carte("Morometii"); } catch (const NotFoundException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { srv.modifica_carte("Morometii", "Nou", "Autor", "gen", 2000); } catch (const NotFoundException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { srv.adauga_carte("", "Autor", "Gen", 2000); } catch (const ValidationException&) { aruncat = true; }
    assert(aruncat);
}

void test_service_filtrari() {
    Repo repo;
    Service srv(repo);
    assert(srv.filtrare_titlu("Ion").empty());
    assert(srv.filtrare_an(1920).empty());

    srv.adauga_carte("Ion", "Rebreanu", "roman", 1920);
    srv.adauga_carte("Alta", "Autor", "gen", 1920);
    srv.adauga_carte("Baltagul", "Sadoveanu", "roman", 1930);

    assert(srv.filtrare_titlu("Ion").size() == 1);
    assert(srv.filtrare_titlu("Morometii").empty());
    assert(srv.filtrare_an(1920).size() == 2);
    assert(srv.filtrare_an(2005).empty());
}

void test_service_sortari() {
    Repo repo;
    Service srv(repo);
    assert(srv.sortare_titlu().empty());
    assert(srv.sortare_autor().empty());
    assert(srv.sortare_an_gen().empty());

    srv.adauga_carte("Zeta", "B", "roman", 2000);
    srv.adauga_carte("Alpha", "C", "roman", 1990);
    srv.adauga_carte("Beta", "A", "roman", 1980);

    auto rez_titlu = srv.sortare_titlu();
    assert(rez_titlu[0].get_titlu() == "Alpha");
    assert(rez_titlu[2].get_titlu() == "Zeta");

    auto rez_autor = srv.sortare_autor();
    assert(rez_autor[0].get_autor() == "A");
    assert(rez_autor[2].get_autor() == "C");
}

void test_service_sortare_an_gen() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("C1", "A1", "z", 2000);
    srv.adauga_carte("C2", "A2", "a", 2000);
    srv.adauga_carte("C4", "A4", "b", 1990);
    srv.adauga_carte("C5", "A5", "c", 2010);

    auto rez = srv.sortare_an_gen();
    assert(rez[0].get_anul_ap() == 1990);
    assert(rez[1].get_anul_ap() == 2000 && rez[1].get_gen() == "a");
    assert(rez[2].get_anul_ap() == 2000 && rez[2].get_gen() == "z");
    assert(rez[3].get_anul_ap() == 2010);
}

void test_service_elemente_identice() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("Titlu1", "AutorX", "GenX", 2000);
    srv.adauga_carte("Titlu2", "AutorX", "GenX", 2000);
    assert(srv.sortare_autor()[0].get_autor() == "AutorX");
    assert(srv.sortare_an_gen()[0].get_gen() == "GenX");
}

void test_cmp_functions() {
    Domain a("Alpha", "X", "a", 2000);
    Domain b("Beta", "Y", "z", 2000);
    Domain c("C", "Z", "m", 1990);

    assert(Service::cmp_titlu(a, b));
    assert(!Service::cmp_titlu(b, a));
    assert(!Service::cmp_titlu(a, a));

    assert(Service::cmp_autor(a, b));
    assert(!Service::cmp_autor(b, a));
    assert(!Service::cmp_autor(a, a));

    assert(Service::cmp_an_gen(a, b));
    assert(!Service::cmp_an_gen(b, a));
    assert(Service::cmp_an_gen(c, a));
    assert(!Service::cmp_an_gen(a, c));
    assert(!Service::cmp_an_gen(a, a));
}

void test_cmp_an_gen() {
    Domain a{"C1", "A1", "z", 2000};
    Domain b{"C2", "A2", "a", 2000};
    Domain c{"C3", "A3", "b", 1990};
    Domain d{"C4", "A4", "c", 2010};
    Domain e{"C5", "A5", "z", 2000};

    assert(Service::cmp_an_gen(b, a) == true);
    assert(Service::cmp_an_gen(a, b) == false);
    assert(Service::cmp_an_gen(c, a) == true);
    assert(Service::cmp_an_gen(d, a) == false);
    assert(Service::cmp_an_gen(a, e) == false);
    assert(Service::cmp_an_gen(e, a) == false);
}

void test_validator() {
    Domain bun("Titlu", "Autor", "Gen", 2000);
    Validator::valideaza(bun);

    bool aruncat = false;
    try { Domain c("", "Autor", "Gen", 2000); Validator::valideaza(c); }
    catch (const ValidationException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { Domain c("Titlu", "", "Gen", 2000); Validator::valideaza(c); }
    catch (const ValidationException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { Domain c("Titlu", "Autor", "", 2000); Validator::valideaza(c); }
    catch (const ValidationException&) { aruncat = true; }
    assert(aruncat);

    aruncat = false;
    try { Domain c("Titlu", "Autor", "Gen", 0); Validator::valideaza(c); }
    catch (const ValidationException&) { aruncat = true; }
    assert(aruncat);
}

void test_cos_goleste() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("Ion", "Rebreanu", "roman", 1920);
    srv.adauga_in_cos("Ion");
    assert(srv.get_cos().size() == 1);
    srv.goleste_cos();
    assert(srv.get_cos().empty());
}

void test_cos_adauga_in_cos() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("Ion", "Rebreanu", "roman", 1920);
    srv.adauga_carte("Baltagul", "Sadoveanu", "roman", 1930);

    srv.adauga_in_cos("Ion");
    srv.adauga_in_cos("Ion");
    srv.adauga_in_cos("Baltagul");

    assert(srv.get_cos().size() == 3);
    assert(srv.get_cos()[0].get_titlu() == "Ion");
    assert(srv.get_cos()[2].get_titlu() == "Baltagul");
}

void test_cos_adauga_inexistent() {
    Repo repo;
    Service srv(repo);
    bool aruncat = false;
    try { srv.adauga_in_cos("Inexistent"); }
    catch (const NotFoundException&) { aruncat = true; }
    assert(aruncat);
}

void test_cos_genereaza() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("Ion", "Rebreanu", "roman", 1920);
    srv.adauga_carte("Baltagul", "Sadoveanu", "roman", 1930);
    srv.genereaza_cos(5);
    assert(srv.get_cos().size() == 5);
}

void test_cos_genereaza_biblioteca_goala() {
    Repo repo;
    Service srv(repo);
    bool aruncat = false;
    try { srv.genereaza_cos(3); }
    catch (const CosException&) { aruncat = true; }
    assert(aruncat);
}

void test_cos_exporta_csv() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("Ion", "Rebreanu", "roman", 1920);
    srv.adauga_in_cos("Ion");
    srv.exporta_cos("test_cos_output", "CSV");

    std::ifstream f("test_cos_output.csv");
    assert(f.is_open());
    std::string linie;
    std::getline(f, linie);
    assert(linie == "Titlu,Autor,Gen,Anul aparitiei");
    std::getline(f, linie);
    assert(linie.find("Ion") != std::string::npos);
    f.close();
    std::remove("test_cos_output.csv");
}

void test_cos_exporta_html() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("Ion", "Rebreanu", "roman", 1920);
    srv.adauga_in_cos("Ion");
    srv.exporta_cos("test_cos_output", "HTML");

    std::ifstream f("test_cos_output.html");
    assert(f.is_open());
    std::string continut((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    assert(continut.find("<table") != std::string::npos);
    assert(continut.find("Ion") != std::string::npos);
    f.close();
    std::remove("test_cos_output.html");
}

void test_cos_exporta_format_invalid() {
    Repo repo;
    Service srv(repo);
    bool aruncat = false;
    try { srv.exporta_cos("fisier", "PDF"); }
    catch (const CosException&) { aruncat = true; }
    assert(aruncat);
}

void ruleaza_toate_testele() {
    test_domain();
    test_domain_default_constructor();
    test_domain_operator_equal();
    test_domain_copy_constructor();

    test_repo_adauga_si_cauta();
    test_repo_exceptii();
    test_repo_sterge_si_modifica();

    test_service_crud();
    test_service_exceptii();
    test_service_filtrari();
    test_service_sortari();
    test_service_sortare_an_gen();
    test_service_elemente_identice();
    test_cmp_functions();
    test_cmp_an_gen();

    test_validator();

    test_cos_goleste();
    test_cos_adauga_in_cos();
    test_cos_adauga_inexistent();
    test_cos_genereaza();
    test_cos_genereaza_biblioteca_goala();
    test_cos_exporta_csv();
    test_cos_exporta_html();
    test_cos_exporta_format_invalid();

    std::cout << "Toate testele au trecut cu succes!\n";
}

int main() {
    ruleaza_toate_testele();
    return 0;
}