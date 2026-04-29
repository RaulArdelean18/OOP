//
// Created by Raul_A on 30/03/2026.
//

#ifndef LAB6_7_UI_H
#define LAB6_7_UI_H

#include "../serv/service.h"
#include "../utils/vector.h"

class UI {
private:
    Service& srv;

    void print_meniu() const;

    void ui_adauga();
    void ui_sterge();
    void ui_modifica();
    void ui_cauta() const;
    void ui_afiseaza() const;
    void ui_filtrare_titlu() const;
    void ui_filtrare_an() const;
    void ui_sortare_titlu() const;
    void ui_sortare_autor() const;
    void ui_sortare_an_gen() const;

    void ui_goleste_cos();
    void ui_adauga_in_cos();
    void ui_genereaza_cos();
    void ui_exporta_cos() const;
    void ui_afiseaza_cos() const;
    void ui_afiseaza_freq_gen() const;

    void ui_undo();
    void ui_salveaza_fisier() const;
    void ui_incarca_fisier();

    static void afiseaza_map(const std::map<std::string,int>& freq);
    static void afiseaza_carte(const Domain& c);
    static void afiseaza_lista(const std::vector<Domain>& lista);

public:
    UI(Service& srv);

    void run();
};

#endif //LAB6_7_UI_H