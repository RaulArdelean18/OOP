//
// Created by Raul_A on 30/03/2026.
//

#include "repo.h"
#include <algorithm>

void Repo::adauga(const Domain& c) {
    auto it = std::find_if(carti.begin(), carti.end(), [&](const Domain& d) {
        return d.get_titlu() == c.get_titlu();
    });
    if (it != carti.end()) {
        throw DuplicatException("Exista deja o carte cu acest titlu!");
    }
    carti.push_back(c);
}

void Repo::sterge(const std::string& titlu) {
    auto it = std::find_if(carti.begin(), carti.end(), [&](const Domain& d) {
        return d.get_titlu() == titlu;
    });
    if (it == carti.end()) {
        throw NotFoundException("Nu exista carte cu titlul dat!");
    }
    carti.erase(it);
}

void Repo::modifica(const std::string& titlu, const Domain& carte_noua) {
    auto it = std::find_if(carti.begin(), carti.end(), [&](const Domain& d) {
        return d.get_titlu() == titlu;
    });
    if (it == carti.end()) {
        throw NotFoundException("Nu exista carte cu titlul dat!");
    }
    *it = carte_noua;
}

const Domain& Repo::cauta(const std::string& titlu) const {
    auto it = std::find_if(carti.begin(), carti.end(), [&](const Domain& d) {
        return d.get_titlu() == titlu;
    });
    if (it == carti.end()) {
        throw NotFoundException("Nu exista carte cu titlul dat!");
    }
    return *it;
}

const std::vector<Domain>& Repo::get_all() const {
    return carti;
}