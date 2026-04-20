#include "domain.h"

Domain::Domain() : titlu(""), autor(""), gen(""), anul_ap(0) {}

Domain::Domain(const std::string &titlu_nou, const std::string &autor_nou,
               const std::string &gen_nou, int anul_ap_nou)
    : titlu(titlu_nou), autor(autor_nou), gen(gen_nou), anul_ap(anul_ap_nou) {}

Domain::Domain(const Domain &other)
    : titlu(other.titlu), autor(other.autor), gen(other.gen), anul_ap(other.anul_ap) {}

Domain& Domain::operator=(const Domain &other) {
    if (this != &other) {
        titlu = other.titlu;
        autor = other.autor;
        gen = other.gen;
        anul_ap = other.anul_ap;
    }
    return *this;
}

const std::string &Domain::get_titlu() const { return titlu; }
const std::string &Domain::get_autor() const { return autor; }
const std::string &Domain::get_gen() const { return gen; }
int Domain::get_anul_ap() const { return anul_ap; }

void Domain::setter_titlu(const std::string &titlu_nou) { titlu = titlu_nou; }
void Domain::setter_autor(const std::string &autor_nou) { autor = autor_nou; }
void Domain::setter_gen(const std::string &gen_nou) { gen = gen_nou; }
void Domain::setter_anul_ap(int anul_ap_nou) { anul_ap = anul_ap_nou; }