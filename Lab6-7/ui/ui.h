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

public:
    UI(Service& srv);

    void run();
};

#endif //LAB6_7_UI_H