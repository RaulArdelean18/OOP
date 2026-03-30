//
// Created by Raul_A on 30/03/2026.
//

#include "domain.h"

Domain::Domain(const string &titlu, const string &autor, const string &gen, int anul_ap)
    : titlu(titlu), autor(autor), gen(gen), anul_ap(anul_ap) {
}

const string &Domain::get_titlu() const {
    return titlu;
}

const string &Domain::get_autor() const {
    return autor;
}

const string &Domain::get_gen() const {
    return gen;
}

const int Domain::get_anul_ap() const {
    return anul_ap;
}

void Domain::setter_titlu(const string &titlu) {
    this->titlu = titlu;
}

void Domain::setter_autor(const string &autor) {
    this->autor = autor;
}

void Domain::setter_gen(const string &gen) {
    this->gen = gen;
}

void Domain::setter_anul_ap(int anul_ap) {
    this->anul_ap = anul_ap;
}
