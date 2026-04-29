//
// Created by Raul_A on 30/03/2026.
//

#ifndef LAB6_7_REPO_H
#define LAB6_7_REPO_H

#include "../Domain/domain.h"
#include "../exceptions/exceptions.h"
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class AbstractRepo {
public:
    virtual void adauga(const Domain& c)=0;
    virtual void sterge(const string& titlu) = 0;
    virtual void modifica(const string& titlu, const Domain& carte_noua) = 0;
    virtual const Domain& cauta(const string& titlu) const = 0;
    virtual const vector<Domain> get_all() const = 0;
    virtual ~AbstractRepo() = default;
};

class Repo: public AbstractRepo {
private:
    std::vector<Domain> carti;

public:
    /**
     * Adauga o carte in lista
     * @param c cartea care se adauga
     */
    void adauga(const Domain& c) override;

    /**
     * Sterge o carte dupa titlu
     * @param titlu titlul cartii
     */
    void sterge(const string& titlu) override;

    /**
     * Modifica o carte identificata dupa titlu
     * @param titlu titlul cartii care se modifica
     * @param carte_noua noua carte
     */
    void modifica(const string& titlu, const Domain& carte_noua) override;

    /**
     * Cauta o carte dupa titlu
     * @param titlu titlul cautat
     * @return cartea gasita
     */
    const Domain& cauta(const string& titlu) const override;

    /**
     * Returneaza toate cartile
     * @return vectorul de carti
     */
    const vector<Domain> get_all() const override;
};

class RepoMap: public AbstractRepo {
private:
    unordered_map<string,Domain> carti;
public:
    void adauga(const Domain& c) override;
    void sterge(const string& titlu) override;
    void modifica(const string& titlu, const Domain& carte_noua) override;
    const Domain& cauta(const string& titlu) const override;
    const vector<Domain> get_all() const override;
};


#endif //LAB6_7_REPO_H