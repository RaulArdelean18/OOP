//
// Created by Raul_A on 30/03/2026.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H

#include "../repo/repo.h"
#include "../utils/vector.h"
#include <string>
using namespace std;

class Service {
private:
    Repo &repo;

public:
    Service(Repo &repo_ref);

    /**
     * Comparam titlul intre 2 carti
     * @param c1: prima carte
     * @param c2: a doua carte
     * @return
     */
    static bool cmp_titlu(const Domain &c1, const Domain &c2);

    /**
     * Comparam autorul intre 2 carti
     * @param c1: prima carte
     * @param c2: a doua carte
     * @return
     */
    static bool cmp_autor(const Domain &c1, const Domain &c2);

    /**
     * Comparam an gen intre 2 carti
     * @param c1: prima carte
     * @param c2: a doua carte
     * @return
     */
    static bool cmp_an_gen(const Domain &c1, const Domain &c2);

    /**
     * Adaugam cartea
     * @param titlu string, titlul cartii
     * @param autor string, autorul cartii
     * @param gen string, genul carti
     * @param anul_ap int, anul aparitie
     */
    void adauga_carte(const string &titlu, const string &autor, const string &gen, const int &anul_ap) const;

    /**
     * Stergem cartea cu titlul @titlu
     * @param titlu: string, titlul carti
     */
    void sterge_carte(const string &titlu) const;

    /**
     * Modifica cartea
     * @param titlu_vechi : string, titlul vechi
     * @param titlu_nou : string, titlul nou
     * @param autor_nou : string, noul autor
     * @param gen_nou : string, noul gen
     * @param anul_ap_nou : int, anul de aparitie nou
     */
    void modifica_carte(const string &titlu_vechi, const string &titlu_nou, const string &autor_nou,
                        const string &gen_nou, const int &anul_ap_nou) const;

    /**
     * Cautam cartea
     * @param titlu : string, titlul carti
     * @return obiectul carte
     */
    const Domain &cauta_carte(const string &titlu) const;

    /**
     * Get all
     * @return vector de carti cu toate cartile
     */
    const MyVector<Domain> &get_all() const;

    /**
     * Filtrare dupa titlu
     * @param titlu : string, titlul dupa care vrem sa filtrem
     * @return vector de obiecte de carti
     */
    MyVector<Domain> filtrare_titlu(const string &titlu) const;

    /**
     * Filtrare dupa an
     * @param anul_ap : int, anul aparitiei dupa care vrem sa filtrem
     * @return vector de obiecte de carti
     */
    MyVector<Domain> filtrare_an(const int &anul_ap) const;

    /**
     * Sortare titlu
     * @return vector de obiecte de carti
     */
    MyVector<Domain> sortare_titlu() const;

    /**
     * Sortare dupa autor
     * @return vector de obiecte de carti
     */
    MyVector<Domain> sortare_autor() const;

    /**
     * Sortare an aparitie, dupa cu genul
     * @return vector de obiecte de carti
     */
    MyVector<Domain> sortare_an_gen() const;
};

#endif //LAB6_7_SERVICE_H
