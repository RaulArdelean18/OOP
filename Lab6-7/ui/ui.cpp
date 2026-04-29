//
// Created by Raul_A on 30/03/2026.
//

#include "ui.h"
#include <iostream>
#include <string>

using namespace std;

UI::UI(Service &srv_ref) : srv(srv_ref) {
}

void UI::print_meniu() const {
    std::cout << "\n===== MENIU BIBLIOTECA =====\n";
    std::cout << "1. Adauga carte\n";
    std::cout << "2. Sterge carte\n";
    std::cout << "3. Modifica carte\n";
    std::cout << "4. Cauta carte\n";
    std::cout << "5. Afiseaza toate cartile\n";
    std::cout << "6. Filtrare dupa titlu\n";
    std::cout << "7. Filtrare dupa anul aparitiei\n";
    std::cout << "8. Sortare dupa titlu\n";
    std::cout << "9. Sortare dupa autor\n";
    std::cout << "10. Sortare dupa an + gen\n";
    std::cout << "11. Goleste cos\n";
    std::cout << "12. Adauga in cos (dupa titlu)\n";
    std::cout << "13. Genereaza cos aleator\n";
    std::cout << "14. Exporta cos (CSV/HTML)\n";
    std::cout << "15. Afiseaza cos\n";
    std::cout << "16. Afiseaza frecventa genurilor\n";
    std::cout << "0. Iesire\n";
    std::cout << "Alegeti optiunea: ";
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
    cin >> anul_ap;

    try {
        srv.adauga_carte(titlu, autor, gen, anul_ap);
        cout << "Carte adaugata cu succes!\n";
    } catch (const exception &e) {
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
    } catch (const exception &e) {
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
    cin >> anul_ap_nou;

    try {
        srv.modifica_carte(titlu_vechi, titlu_nou, autor_nou, gen_nou, anul_ap_nou);
        cout << "Carte modificata cu succes!\n";
    } catch (const exception &e) {
        cout << e.what() << '\n';
    }
}

void UI::ui_cauta() const {
    string titlu;

    cout << "Titlul cautat: ";
    cin >> ws;
    getline(cin, titlu);

    try {
        const Domain &c = srv.cauta_carte(titlu);
        cout << "Carte gasita:\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    } catch (const exception &e) {
        cout << e.what() << '\n';
    }
}

void UI::ui_afiseaza() const {
    const std::vector<Domain> &carti = srv.get_all();

    if (carti.empty()) {
        cout << "Nu exista carti in lista.\n";
        return;
    }

    for (const auto &c: carti) {
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

    std::vector<Domain> rezultat = srv.filtrare_titlu(titlu);

    if (rezultat.empty()) {
        cout << "Nu exista carti care sa respecte filtrul dat.\n";
        return;
    }

    for (const auto &c: rezultat) {
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
    cin >> an;

    std::vector<Domain> rezultat = srv.filtrare_an(an);

    if (rezultat.empty()) {
        cout << "Nu exista carti care sa respecte filtrul dat.\n";
        return;
    }

    for (const auto &c: rezultat) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::ui_sortare_titlu() const {
    std::vector<Domain> rezultat = srv.sortare_titlu();

    if (rezultat.empty()) {
        cout << "Nu exista carti in lista.\n";
        return;
    }

    for (const auto &c: rezultat) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::ui_sortare_autor() const {
    std::vector<Domain> rezultat = srv.sortare_autor();

    if (rezultat.empty()) {
        cout << "Nu exista carti in lista.\n";
        return;
    }

    for (const auto &c: rezultat) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::ui_sortare_an_gen() const {
    std::vector<Domain> rezultat = srv.sortare_an_gen();

    if (rezultat.empty()) {
        cout << "Nu exista carti in lista.\n";
        return;
    }

    for (const auto &c: rezultat) {
        cout << "-----------------------------\n";
        cout << "Titlu: " << c.get_titlu() << '\n';
        cout << "Autor: " << c.get_autor() << '\n';
        cout << "Gen: " << c.get_gen() << '\n';
        cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
    }
}

void UI::ui_goleste_cos() {
    srv.goleste_cos();
    std::cout << "Cosul a fost golit.\n";
    std::cout << "Total carti in cos: " << srv.get_cos().size() << "\n";
}

void UI::ui_adauga_in_cos() {
    std::string titlu;
    std::cout << "Titlul cartii de adaugat in cos: ";
    std::cin >> std::ws;
    std::getline(std::cin, titlu);
    try {
        srv.adauga_in_cos(titlu);
        std::cout << "Carte adaugata in cos!\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
    std::cout << "Total carti in cos: " << srv.get_cos().size() << "\n";
}

void UI::ui_genereaza_cos() {
    int nr;
    std::cout << "Numarul de carti pentru generare: ";
    std::cin >> nr;
    try {
        srv.genereaza_cos(nr);
        std::cout << "Cos generat aleator!\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
    std::cout << "Total carti in cos: " << srv.get_cos().size() << "\n";
}

void UI::ui_exporta_cos() const {
    std::string format, nume_fisier;
    std::cout << "Format export (CSV/HTML): ";
    std::cin >> std::ws;
    std::getline(std::cin, format);
    std::cout << "Numele fisierului (fara extensie): ";
    std::getline(std::cin, nume_fisier);
    try {
        srv.exporta_cos(nume_fisier, format);
        std::cout << "Cosul a fost exportat in " << nume_fisier << "."
                << (format == "CSV" ? "csv" : "html") << "\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
    std::cout << "Total carti in cos: " << srv.get_cos().size() << "\n";
}

void UI::afiseaza_carte(const Domain &c) {
    std::cout << "-----------------------------\n";
    std::cout << "Titlu: " << c.get_titlu() << '\n';
    std::cout << "Autor: " << c.get_autor() << '\n';
    std::cout << "Gen: " << c.get_gen() << '\n';
    std::cout << "Anul aparitiei: " << c.get_anul_ap() << '\n';
}

void UI::afiseaza_lista(const std::vector<Domain> &lista) {
    for (const auto &c: lista)
        afiseaza_carte(c);
}

void UI::ui_afiseaza_cos() const {
    const auto &cos = srv.get_cos();
    if (cos.empty()) {
        std::cout << "Cosul este gol.\n";
    } else {
        std::cout << "=== Cos de Inchirieri ===\n";
        afiseaza_lista(cos);
    }
    std::cout << "Total carti in cos: " << cos.size() << "\n";
}

void UI::afiseaza_map(const std::map<std::string, int> &freq) {
    for (auto x: freq) {
        std::cout << "Genul: " << x.first << " iar frecventa lui: " << x.second << '\n';
    }
}

void UI::ui_afiseaza_freq_gen() const {
    const auto &freq = srv.gen_frequences();
    if (freq.empty()) {
        std::cout << "Nu avem carti in Domain\n";
    } else {
        std::cout << "=== Genurile cu frecventele ===\n";
        afiseaza_map(freq);
    }
}

void UI::ui_undo() {
    try {
        srv.undo();
        std::cout << "Ultima operatie a fost anulata cu succes!\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
}

void UI::ui_salveaza_fisier() const {
    std::string cale;
    std::cout << "Calea fisierului CSV (ex: biblioteca.csv): ";
    std::cin >> std::ws;
    std::getline(std::cin, cale);
    try {
        srv.salveaza_fisier(cale);
        std::cout << "Biblioteca salvata cu succes in: " << cale << "\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
}

void UI::ui_incarca_fisier() {
    std::string cale;
    std::cout << "Calea fisierului CSV de incarcat (ex: biblioteca.csv): ";
    std::cin >> std::ws;
    std::getline(std::cin, cale);
    try {
        srv.incarca_fisier(cale);
        std::cout << "Biblioteca incarcata cu succes din: " << cale << "\n";
        std::cout << "Total carti: " << srv.get_all().size() << "\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
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
            case 10: ui_sortare_an_gen();
                break;
            case 11: ui_goleste_cos();
                break;
            case 12: ui_adauga_in_cos();
                break;
            case 13: ui_genereaza_cos();
                break;
            case 14: ui_exporta_cos();
                break;
            case 15: ui_afiseaza_cos();
                break;
            case 16: ui_afiseaza_freq_gen();
                break;
            case 17: ui_undo();
                break;
            case 18: ui_salveaza_fisier();
                break;
            case 19: ui_incarca_fisier();
                break;
            case 0:
                cout << "Aplicatia se inchide.\n";
                return;
            default:
                cout << "Optiune invalida!\n";
        }
    }
}
