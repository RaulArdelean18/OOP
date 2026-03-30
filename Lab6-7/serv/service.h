//
// Created by Raul_A on 30/03/2026.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H

#include "../repo/repo.h"
#include <vector>
#include <string>
using namespace std;

bool cmp_titlu(const Domain& c1, const Domain& c2);
bool cmp_autor(const Domain& c1, const Domain& c2);
bool cmp_an_gen(const Domain& c1, const Domain& c2);

class Service {
private:
    Repo& repo;

public:
    Service(Repo& repo);

    void adauga_carte(const string& titlu, const string& autor,const string& gen, const int& anul_ap);
    void sterge_carte(const string& titlu);
    void modifica_carte(const string& titlu_vechi, const string& titlu_nou,const string& autor_nou, const string& gen_nou,const int& anul_ap_nou);
    const Domain& cauta_carte(const string& titlu) const;
    const vector<Domain>& get_all() const;
    vector<Domain> filtrare_titlu(const string& titlu) const;
    vector<Domain> filtrare_an(const int& anul_ap) const;
    vector<Domain> sortare_titlu() const;
    vector<Domain> sortare_autor() const;
    vector<Domain> sortare_an_gen() const;
};


#endif //LAB6_7_SERVICE_H
