//
// Created by Raul_A on 30/03/2026.
//

#include "service.h"
#include <algorithm>
#include "../validator/validator.h"

Service::Service(Repo &repo_ref) : repo(repo_ref) {
}

void Service::adauga_carte(const string &titlu, const string &autor, const string &gen, const int &anul_ap) const {
    const Domain c(titlu, autor, gen, anul_ap);
    Validator::valideaza(c);
    repo.adauga(c);
}

void Service::sterge_carte(const string &titlu) const {
    repo.sterge(titlu);
}

void Service::modifica_carte(const string &titlu_vechi, const string &titlu_nou, const string &autor_nou,
                             const string &gen_nou, const int &anul_ap_nou) const {
    Domain c_noua(titlu_nou, autor_nou, gen_nou, anul_ap_nou);
    Validator::valideaza(c_noua);
    repo.modifica(titlu_vechi, c_noua);
}

const Domain &Service::cauta_carte(const string &titlu) const {
    return repo.cauta(titlu);
}

const MyVector<Domain> &Service::get_all() const {
    return repo.get_all();
}

MyVector<Domain> Service::filtrare_titlu(const string &titlu) const {
    MyVector<Domain> rezultat;
    const MyVector<Domain> &carti = repo.get_all();

    for (const auto & i : carti) {
        if (i.get_titlu() == titlu) {
            rezultat.push_back(i);
        }
    }
    return rezultat;
}

MyVector<Domain> Service::filtrare_an(const int &anul_ap) const {
    MyVector<Domain> rezultat;
    const MyVector<Domain> &carti = repo.get_all();

    for (const auto & i : carti) {
        if (i.get_anul_ap() == anul_ap) {
            rezultat.push_back(i);
        }
    }
    return rezultat;
}

bool Service::cmp_titlu(const Domain &c1, const Domain &c2) {
    return c1.get_titlu() < c2.get_titlu();
}

bool Service::cmp_autor(const Domain &c1, const Domain &c2) {
    return c1.get_autor() < c2.get_autor();
}

bool Service::cmp_an_gen(const Domain &c1, const Domain &c2) {
    if (c1.get_anul_ap() == c2.get_anul_ap()) {
        return c1.get_gen() < c2.get_gen();
    }
    return c1.get_anul_ap() < c2.get_anul_ap();
}

MyVector<Domain> Service::sortare_titlu() const {
    MyVector<Domain> rezultat = repo.get_all();
    sort(rezultat.begin(),rezultat.end(), Service::cmp_titlu);
    return rezultat;
}

MyVector<Domain> Service::sortare_autor() const {
    MyVector<Domain> rezultat = repo.get_all();
    sort(rezultat.begin(),rezultat.end(), Service::cmp_autor);
    return rezultat;
}

MyVector<Domain> Service::sortare_an_gen() const {
    MyVector<Domain> rezultat = repo.get_all();
    sort(rezultat.begin(),rezultat.end(), Service::cmp_an_gen);
    return rezultat;
}
