#include "service.h"
#include "../validator/validator.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

Service::Service(Repo &repo_ref) : repo(repo_ref) {}

void Service::adauga_carte(const std::string &titlu, const std::string &autor,
                            const std::string &gen, int anul_ap) const {
    const Domain c(titlu, autor, gen, anul_ap);
    Validator::valideaza(c);
    repo.adauga(c);
}

void Service::sterge_carte(const std::string &titlu) const {
    repo.sterge(titlu);
}

void Service::modifica_carte(const std::string &titlu_vechi, const std::string &titlu_nou,
                              const std::string &autor_nou, const std::string &gen_nou, int anul_ap_nou) const {
    Domain c_noua(titlu_nou, autor_nou, gen_nou, anul_ap_nou);
    Validator::valideaza(c_noua);
    repo.modifica(titlu_vechi, c_noua);
}

const Domain &Service::cauta_carte(const std::string &titlu) const {
    return repo.cauta(titlu);
}

const std::vector<Domain> &Service::get_all() const {
    return repo.get_all();
}

std::vector<Domain> Service::filtrare_titlu(const std::string &titlu) const {
    std::vector<Domain> rezultat;
    const auto& carti = repo.get_all();
    std::copy_if(carti.begin(), carti.end(), std::back_inserter(rezultat),
        [&](const Domain& d) { return d.get_titlu() == titlu; });
    return rezultat;
}

std::vector<Domain> Service::filtrare_an(int anul_ap) const {
    std::vector<Domain> rezultat;
    const auto& carti = repo.get_all();
    std::copy_if(carti.begin(), carti.end(), std::back_inserter(rezultat),
        [&](const Domain& d) { return d.get_anul_ap() == anul_ap; });
    return rezultat;
}

bool Service::cmp_titlu(const Domain &c1, const Domain &c2) {
    return c1.get_titlu() < c2.get_titlu();
}

bool Service::cmp_autor(const Domain &c1, const Domain &c2) {
    return c1.get_autor() < c2.get_autor();
}

bool Service::cmp_an_gen(const Domain &c1, const Domain &c2) {
    if (c1.get_anul_ap() == c2.get_anul_ap())
        return c1.get_gen() < c2.get_gen();
    return c1.get_anul_ap() < c2.get_anul_ap();
}

std::vector<Domain> Service::sortare_titlu() const {
    std::vector<Domain> rezultat = repo.get_all();
    std::sort(rezultat.begin(), rezultat.end(), Service::cmp_titlu);
    return rezultat;
}

std::vector<Domain> Service::sortare_autor() const {
    std::vector<Domain> rezultat = repo.get_all();
    std::sort(rezultat.begin(), rezultat.end(), Service::cmp_autor);
    return rezultat;
}

std::vector<Domain> Service::sortare_an_gen() const {
    std::vector<Domain> rezultat = repo.get_all();
    std::sort(rezultat.begin(), rezultat.end(), Service::cmp_an_gen);
    return rezultat;
}

void Service::goleste_cos() {
    cos.clear();
}

void Service::adauga_in_cos(const std::string &titlu) {
    const Domain& c = repo.cauta(titlu);
    cos.push_back(c);
}

void Service::genereaza_cos(int nr) {
    const auto& carti = repo.get_all();
    if (carti.empty())
        throw CosException("Nu exista carti in biblioteca pentru a genera cosul!");

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<Domain> sursa = carti;
    std::shuffle(sursa.begin(), sursa.end(), std::default_random_engine(static_cast<unsigned>(seed)));

    for (int i = 0; i < nr; i++)
        cos.push_back(sursa[static_cast<size_t>(i) % sursa.size()]);
}

const std::vector<Domain>& Service::get_cos() const {
    return cos;
}

void Service::exporta_cos(const std::string &nume_fisier, const std::string &format) const {
    if (format == "CSV") {
        std::ofstream f(nume_fisier + ".csv");
        if (!f.is_open())
            throw CosException("Nu s-a putut deschide fisierul pentru scriere!");
        f << "Titlu,Autor,Gen,Anul aparitiei\n";
        for (const auto& c : cos)
            f << c.get_titlu() << "," << c.get_autor() << ","
              << c.get_gen() << "," << c.get_anul_ap() << "\n";
    } else if (format == "HTML") {
        std::ofstream f(nume_fisier + ".html");
        if (!f.is_open())
            throw CosException("Nu s-a putut deschide fisierul pentru scriere!");
        f << "<!DOCTYPE html>\n<html>\n<head><meta charset=\"UTF-8\"><title>Cos Inchirieri</title></head>\n<body>\n";
        f << "<h1>Cos de Inchirieri</h1>\n";
        f << "<table border=\"1\">\n<tr><th>Titlu</th><th>Autor</th><th>Gen</th><th>Anul aparitiei</th></tr>\n";
        for (const auto& c : cos)
            f << "<tr><td>" << c.get_titlu() << "</td><td>" << c.get_autor()
              << "</td><td>" << c.get_gen() << "</td><td>" << c.get_anul_ap() << "</td></tr>\n";
        f << "</table>\n</body>\n</html>\n";
    } else {
        throw CosException("Format invalid! Folositi CSV sau HTML.");
    }
}