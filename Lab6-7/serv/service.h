//
// Created by Raul_A on 30/03/2026.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H

#include "../repo/repo.h"
#include "../undo/undo.h"
#include "../utils/vector.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;

class Service {
private:
    AbstractRepo &repo;
    std::vector<Domain> cos;

    // Lista de actiuni undo
    std::vector<std::unique_ptr<ActiuneUndo>> istoricUndo;

public:
    explicit Service(AbstractRepo &repo_ref);

    // ===== Comparatoare =====
    static bool cmp_titlu(const Domain &c1, const Domain &c2);
    static bool cmp_autor(const Domain &c1, const Domain &c2);
    static bool cmp_an_gen(const Domain &c1, const Domain &c2);

    // ===== CRUD =====
    void adauga_carte(const std::string &titlu, const std::string &autor,
                      const std::string &gen, int anul_ap);

    void sterge_carte(const string &titlu);

    void modifica_carte(const std::string &titlu_vechi, const std::string &titlu_nou,
                        const std::string &autor_nou, const std::string &gen_nou, int anul_ap_nou);

    const Domain &cauta_carte(const string &titlu) const;
    std::vector<Domain> get_all() const;

    // ===== Filtrare & Sortare =====
    std::vector<Domain> filtrare_titlu(const string &titlu) const;
    std::vector<Domain> filtrare_an(int anul_ap) const;
    std::vector<Domain> sortare_titlu() const;
    std::vector<Domain> sortare_autor() const;
    std::vector<Domain> sortare_an_gen() const;

    // ===== Cos =====
    void goleste_cos();
    void adauga_in_cos(const std::string &titlu);
    void genereaza_cos(int nr);
    const std::vector<Domain>& get_cos() const;
    void exporta_cos(const std::string &nume_fisier, const std::string &format) const;

    // ===== Frecvente genuri =====
    std::map<std::string, int> gen_frequences() const;

    // ===== Undo =====
    void undo();

    // ===== Salvare/Incarcare fisier repo =====
    void salveaza_fisier(const std::string &cale) const;
    void incarca_fisier(const std::string &cale);
};

#endif //LAB6_7_SERVICE_H