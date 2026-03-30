//
// Created by Raul_A on 30/03/2026.
//

#include "service.h"
#include <algorithm>

Service::Service(Repo &repo) : repo(repo) {
}

void Service::adauga_carte(const string &titlu, const string &autor, const string &gen, const int &anul_ap) {
    Domain c(titlu, autor, gen, anul_ap);
    repo.adauga(c);
}

void Service::sterge_carte(const string &titlu) {
    repo.sterge(titlu);
}

void Service::modifica_carte(const string &titlu_vechi, const string &titlu_nou, const string &autor_nou,
                             const string &gen_nou, const int &anul_ap_nou) {
    Domain c_noua(titlu_nou, autor_nou, gen_nou, anul_ap_nou);
    repo.modifica(titlu_vechi, c_noua);
}

const Domain &Service::cauta_carte(const string &titlu) const {
    return repo.cauta(titlu);
}

const vector<Domain> &Service::get_all() const {
    return repo.get_all();
}

vector<Domain> Service::filtrare_titlu(const string &titlu) const {
    vector<Domain> rezultat;
    const vector<Domain> &carti = repo.get_all();

    for (size_t i = 0; i < carti.size(); i++) {
        if (carti[i].get_titlu() == titlu) {
            rezultat.push_back(carti[i]);
        }
    }
    return rezultat;
}

vector<Domain> Service::filtrare_an(const int &anul_ap) const {
    vector<Domain> rezultat;
    const vector<Domain> &carti = repo.get_all();

    for (size_t i = 0; i < carti.size(); i++) {
        if (carti[i].get_anul_ap() == anul_ap) {
            rezultat.push_back(carti[i]);
        }
    }
    return rezultat;
}

bool cmp_titlu(const Domain &c1, const Domain &c2) {
    return c1.get_titlu() < c2.get_titlu();
}

bool cmp_autor(const Domain &c1, const Domain &c2) {
    return c1.get_autor() < c2.get_autor();
}

bool cmp_an_gen(const Domain &c1, const Domain &c2) {
    if (c1.get_anul_ap() == c2.get_anul_ap()) {
        return c1.get_gen() < c2.get_gen();
    }
    return c1.get_anul_ap() < c2.get_anul_ap();
}

vector<Domain> Service::sortare_titlu() const {
    vector<Domain> rezultat = repo.get_all();
    sort(rezultat.begin(), rezultat.end(), cmp_titlu);
    return rezultat;
}

vector<Domain> Service::sortare_autor() const {
    vector<Domain> rezultat = repo.get_all();
    sort(rezultat.begin(), rezultat.end(), cmp_autor);
    return rezultat;
}

vector<Domain> Service::sortare_an_gen() const {
    vector<Domain> rezultat = repo.get_all();
    sort(rezultat.begin(), rezultat.end(), cmp_an_gen);
    return rezultat;
}
