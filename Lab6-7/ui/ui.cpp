//
// Created by Raul_A on 30/03/2026.
//

#include "ui.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

UI::UI(Service& srv) : srv(srv) {
}

void UI::print_meniu() const {
    cout << "\n===== MENIU BIBLIOTECA =====\n";
    cout << "1. Adauga carte\n";
    cout << "2. Sterge carte\n";
    cout << "3. Modifica carte\n";
    cout << "4. Cauta carte\n";
    cout << "5. Afiseaza toate cartile\n";
    cout << "6. Filtrare dupa titlu\n";
    cout << "7. Filtrare dupa anul aparitiei\n";
    cout << "8. Sortare dupa titlu\n";
    cout << "9. Sortare dupa autor\n";
    cout << "10. Sortare dupa an + gen\n";
    cout << "0. Iesire\n";
    cout << "Alegeti optiunea: ";
}

void UI::ui_adauga() {
    string titlu, autor, gen;
    int anul_ap;

    cout << "Titlu: ";
    cin >> ws;
    getline(cin, titlu);

    cout << "Autor: ";
    getline(cin, autor);

    cout << "Gen: ";
    getline(cin, gen);

    cout << "Anul aparitiei: ";
    cin>>anul_ap;

    try {
        srv.adauga_carte(titlu, autor, gen, anul_ap);
        cout << "Carte adaugata cu succes!\n";
    } catch (const exception& e) {
        cout << e.what() << '\n';
    }
}

void UI::ui_sterge() {
    string titlu;

    cout << "Titlul cartii de sters: ";
    cin >> ws;
    getline(cin, titlu);

    try {
        srv.sterge_carte(titlu);
        cout << "Carte stearsa cu succes!\n";
    } catch (const exception& e) {
        cout << e.what() << '\n';
    }
}

void UI::ui_modifica() {
    string titlu_vechi, titlu_nou, autor_nou, gen_nou;
    int anul_ap_nou;

    cout << "Titlul cartii de modificat: ";
    cin >> ws;
    getline(cin, titlu_vechi);

    cout << "Titlu nou: ";
    getline(cin, titlu_nou);

    cout << "Autor nou: ";
    getline(cin, autor_nou);

    cout << "Gen nou: ";
    getline(cin, gen_nou);

    cout << "Anul aparitiei nou: ";
    cin>>anul_ap_nou;

    try {
        srv.modifica_carte(titlu_vechi, titlu_nou, autor_nou, gen_nou, anul_ap_nou);
        cout << "Carte modificata cu succes!\n";
    } catch (const exception& e) {
        cout << e.what() << '\n';
    }
}

void UI::ui_cauta() const {
    string titlu;

    cout << "Titlul cautat: ";
    cin >> ws;
    getline(cin, titlu);

    try {
        const Domain& c = srv.cauta_carte(titlu);
        cout << "Carte gasita:\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    } catch (const exception& e) {
        cout << e.what() << '\n';
    }
}

void UI::ui_afiseaza() const {
    const vector<Domain>& carti = srv.get_all();

    if (carti.empty()) {
        cout << "Nu exista carti in lista.\n";
        return;
    }

    for (const auto& c : carti) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::ui_filtrare_titlu() const {
    string titlu;
    cout << "Titlul pentru filtrare: ";
    cin >> ws;
    getline(cin, titlu);

    vector<Domain> rezultat = srv.filtrare_titlu(titlu);

    if (rezultat.empty()) {
        cout << "Nu exista carti care sa respecte filtrul dat.\n";
        return;
    }

    for (const auto& c : rezultat) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::ui_filtrare_an() const {
    int an;
    cout << "Anul pentru filtrare: ";
    cin >> ws;
    cin>>an;

    vector<Domain> rezultat = srv.filtrare_an(an);

    if (rezultat.empty()) {
        cout << "Nu exista carti care sa respecte filtrul dat.\n";
        return;
    }

    for (const auto& c : rezultat) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::ui_sortare_titlu() const {
    vector<Domain> rezultat = srv.sortare_titlu();

    if (rezultat.empty()) {
        cout << "Nu exista carti in lista.\n";
        return;
    }

    for (const auto& c : rezultat) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::ui_sortare_autor() const {
    vector<Domain> rezultat = srv.sortare_autor();

    if (rezultat.empty()) {
        cout << "Nu exista carti in lista.\n";
        return;
    }

    for (const auto& c : rezultat) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::ui_sortare_an_gen() const {
    vector<Domain> rezultat = srv.sortare_an_gen();

    if (rezultat.empty()) {
        cout << "Nu exista carti in lista.\n";
        return;
    }

    for (const auto& c : rezultat) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::run() {
    while (true) {
        print_meniu();

        int cmd;
        cin >> cmd;

        switch (cmd) {
            case 1:
                ui_adauga();
                break;
            case 2:
                ui_sterge();
                break;
            case 3:
                ui_modifica();
                break;
            case 4:
                ui_cauta();
                break;
            case 5:
                ui_afiseaza();
                break;
            case 6:
                ui_filtrare_titlu();
                break;
            case 7:
                ui_filtrare_an();
                break;
            case 8:
                ui_sortare_titlu();
                break;
            case 9:
                ui_sortare_autor();
                break;
            case 10:
                ui_sortare_an_gen();
                break;
            case 0:
                cout << "Aplicatia se inchide.\n";
                return;
            default:
                cout << "Optiune invalida!\n";
        }
    }
}