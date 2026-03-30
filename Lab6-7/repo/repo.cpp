//
// Created by Raul_A on 30/03/2026.
//

#include "../repo/repo.h"
#include <stdexcept>

void Repo::adauga(const Domain& c) {
    for (const auto& carte : carti) {
        if (carte.get_titlu() == c.get_titlu()) {
            throw runtime_error("Exista deja o carte cu acest titlu!");
        }
    }
    carti.push_back(c);
}

void Repo::sterge(const string& titlu) {
    for (auto it = carti.begin(); it != carti.end(); it++) {
        if (it->get_titlu() == titlu) {
            carti.erase(it);
            return;
        }
    }
    throw runtime_error("Nu exista carte cu titlul dat!");
}

void Repo::modifica(const string& titlu, const Domain& carte_noua) {
    for (auto& carte : carti) {
        if (carte.get_titlu() == titlu) {
            carte = carte_noua;
            return;
        }
    }
    throw runtime_error("Nu exista carte cu titlul dat!");
}

const Domain& Repo::cauta(const string& titlu) const {
    for (const auto& carte : carti) {
        if (carte.get_titlu() == titlu) {
            return carte;
        }
    }
    throw runtime_error("Nu exista carte cu titlul dat!");
}

const vector<Domain>& Repo::get_all() const {
    return carti;
}
