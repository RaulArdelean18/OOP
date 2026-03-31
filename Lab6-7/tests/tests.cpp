#include "../tests/tests.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

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

    bool exceptie_adauga = false;
    try { repo.adauga(Domain("Ion", "Rebreanu", "roman", 1920)); }
    catch (const runtime_error&) { exceptie_adauga = true; }
    assert(exceptie_adauga);

    bool exceptie_cauta = false;
    try { repo.cauta("Morometii"); }
    catch (const runtime_error&) { exceptie_cauta = true; }
    assert(exceptie_cauta);

    bool exceptie_sterge = false;
    try { repo.sterge("Morometii"); }
    catch (const runtime_error&) { exceptie_sterge = true; }
    assert(exceptie_sterge);

    bool exceptie_modifica = false;
    try { repo.modifica("Morometii", Domain("Nou", "Autor", "gen", 2000)); }
    catch (const runtime_error&) { exceptie_modifica = true; }
    assert(exceptie_modifica);
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
    const Domain& c = srv.cauta_carte("Morometii");
    assert(c.get_autor() == "Marin Preda");
    assert(c.get_anul_ap() == 1955);
}

void test_service_exceptii() {
    Repo repo;
    Service srv(repo);
    srv.adauga_carte("Ion", "Rebreanu", "roman", 1920);

    bool exceptie = false;
    try { srv.cauta_carte("Morometii"); } catch (const runtime_error&) { exceptie = true; }
    assert(exceptie);

    exceptie = false;
    try { srv.adauga_carte("Ion", "Rebreanu", "roman", 1920); } catch (const runtime_error&) { exceptie = true; }
    assert(exceptie);

    exceptie = false;
    try { srv.sterge_carte("Morometii"); } catch (const runtime_error&) { exceptie = true; }
    assert(exceptie);

    exceptie = false;
    try { srv.modifica_carte("Morometii", "Nou", "Autor", "gen", 2000); } catch (const runtime_error&) { exceptie = true; }
    assert(exceptie);
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
    assert(srv.sortare_titlu().size() == 1);

    srv.adauga_carte("Alpha", "C", "roman", 1990);
    srv.adauga_carte("Beta", "A", "roman", 1980);

    vector<Domain> rez_titlu = srv.sortare_titlu();
    assert(rez_titlu[0].get_titlu() == "Alpha");
    assert(rez_titlu[2].get_titlu() == "Zeta");

    vector<Domain> rez_autor = srv.sortare_autor();
    assert(rez_autor[0].get_autor() == "A");
    assert(rez_autor[2].get_autor() == "C");
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

void test_cmp_functions() {
    Domain a("Alpha", "X", "a", 2000);
    Domain b("Beta", "Y", "z", 2000);
    Domain c("C", "Z", "m", 1990);
    Domain d("D", "T", "b", 2010);

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

void test_service_elemente_identice() {
    Repo repo;
    Service srv(repo);

    srv.adauga_carte("Titlu1", "AutorX", "GenX", 2000);
    srv.adauga_carte("Titlu2", "AutorX", "GenX", 2000);

    assert(srv.sortare_autor()[0].get_autor() == "AutorX");
    assert(srv.sortare_an_gen()[0].get_gen() == "GenX");
}

void ruleaza_toate_testele() {
    test_domain();

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

    cout << "Toate testele au trecut cu succes!\n";
}
int main() {
    ruleaza_toate_testele();
    return 0;
}