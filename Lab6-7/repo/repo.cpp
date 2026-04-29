#include "repo.h"
#include <algorithm>

// ===== Repo (vector) =====

void Repo::adauga(const Domain &c) {
    if (any_of(carti.begin(), carti.end(), [&](const Domain &d) { return d.get_titlu() == c.get_titlu(); }))
        throw DuplicatException("Exista deja o carte cu acest titlu!");
    carti.push_back(c);
}

void Repo::sterge(const string &titlu) {
    auto it = find_if(carti.begin(), carti.end(), [&](const Domain &d) { return d.get_titlu() == titlu; });
    if (it == carti.end()) throw NotFoundException("Nu exista carte cu titlul dat!");
    carti.erase(it);
}

void Repo::modifica(const string &titlu, const Domain &carte_noua) {
    auto it = find_if(carti.begin(), carti.end(), [&](const Domain &d) { return d.get_titlu() == titlu; });
    if (it == carti.end()) throw NotFoundException("Nu exista carte cu titlul dat!");
    *it = carte_noua;
}

const Domain &Repo::cauta(const string &titlu) const {
    auto it = find_if(carti.begin(), carti.end(), [&](const Domain &d) { return d.get_titlu() == titlu; });
    if (it == carti.end()) throw NotFoundException("Nu exista carte cu titlul dat!");
    return *it;
}

const vector<Domain> Repo::get_all() const { return carti; }

// ===== RepoMap =====

void RepoMap::adauga(const Domain &c) {
    if (carti.count(c.get_titlu())) throw DuplicatException("Exista deja o carte cu acest titlu!");
    carti.emplace(c.get_titlu(), c);
}

void RepoMap::sterge(const string &titlu) {
    if (!carti.count(titlu)) throw NotFoundException("Nu exista carte cu titlul dat!");
    carti.erase(titlu);
}

void RepoMap::modifica(const string &titlu, const Domain &carte_noua) {
    if (!carti.count(titlu)) throw NotFoundException("Nu exista carte cu titlul dat!");
    carti.erase(titlu);
    carti.emplace(carte_noua.get_titlu(), carte_noua);
}

const Domain &RepoMap::cauta(const string &titlu) const {
    auto it = carti.find(titlu);
    if (it == carti.end()) throw NotFoundException("Nu exista carte cu titlul dat!");
    return it->second;
}

const vector<Domain> RepoMap::get_all() const {
    vector<Domain> rezultat;
    for (const auto &[_, c]: carti) rezultat.push_back(c);
    return rezultat;
}
