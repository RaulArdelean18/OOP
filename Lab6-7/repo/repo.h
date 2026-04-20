//
// Created by Raul_A on 30/03/2026.
//

#ifndef LAB6_7_REPO_H
#define LAB6_7_REPO_H

#include "../Domain/domain.h"
#include "../exceptions/exceptions.h"
#include <string>
#include <vector>
using namespace std;

class Repo {
private:
    std::vector<Domain> carti;

public:
    /**
     * Adauga o carte in lista
     * @param c cartea care se adauga
     */
    void adauga(const Domain& c);

    /**
     * Sterge o carte dupa titlu
     * @param titlu titlul cartii
     */
    void sterge(const string& titlu);

    /**
     * Modifica o carte identificata dupa titlu
     * @param titlu titlul cartii care se modifica
     * @param carte_noua noua carte
     */
    void modifica(const string& titlu, const Domain& carte_noua);

    /**
     * Cauta o carte dupa titlu
     * @param titlu titlul cautat
     * @return cartea gasita
     */
    const Domain& cauta(const string& titlu) const;

    /**
     * Returneaza toate cartile
     * @return vectorul de carti
     */
    const std::vector<Domain>& get_all() const;
};


#endif //LAB6_7_REPO_H