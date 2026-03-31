//
// Created by Raul_A on 30/03/2026.
//

#include "domain.h"

Domain::Domain(const string &titlu_nou, const string &autor_nou, const string &gen_nou, int anul_ap_nou)
    : titlu(titlu_nou), autor(autor_nou), gen(gen_nou), anul_ap(anul_ap_nou) {
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

int Domain::get_anul_ap() const {
    return anul_ap;
}

void Domain::setter_titlu(const string &titlu_nou) {
    titlu = titlu_nou;
}

void Domain::setter_autor(const string &autor_nou) {
    autor = autor_nou;
}

void Domain::setter_gen(const string &gen_nou) {
    gen = gen_nou;
}

void Domain::setter_anul_ap(int anul_ap_nou) {
    anul_ap = anul_ap_nou;
}
