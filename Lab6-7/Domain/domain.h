//
// Created by Raul_A on 30/03/2026.
//

#ifndef LAB6_7_DOMAIN_H
#define LAB6_7_DOMAIN_H
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

class Domain {
private:
    string titlu;
    string autor;
    string gen;
    int anul_ap;

public:
    Domain(const string &titlu_nou, const string &autor_nou, const string &gen_nou, int an_ap_nou);

    Domain(const Domain &other) : titlu(other.titlu), autor(other.autor), gen(other.gen), anul_ap(other.anul_ap) {
        std::cout << "Constructorul de copiere apelat pentru cartea: " << other.titlu << '\n';
    }

    Domain operator=(const Domain &other) {
        if (this != &other) {
            titlu = other.titlu;
            autor = other.autor;
            gen = other.gen;
            anul_ap = other.anul_ap;
        }

        return *this;
    }
    ;
    /**
    * Getter titlu
    * @return string, titlul carti
    */
    const string &get_titlu() const;

    /**
     * Getter autor
     * @return string, autorul carti
     */
    const string &get_autor() const;

    /**
     * Getter gen
     * @return string, genul carti
     */
    const string &get_gen() const;

    /**
     * Getter anul aparitiei
     * @return string, anul aparitie carti
     */
    int get_anul_ap() const;

    /**
     * Setter titlu
     */
    void setter_titlu(const string &titlu_nou);

    /**
     * Setter autor
     */
    void setter_autor(const string &autor_nou);

    /**
     * Setter gen
     */
    void setter_gen(const string &gen_nou);

    /**
     * Setter anul aparitie
     */
    void setter_anul_ap(const int anul_ap_nou);
};

#endif //LAB6_7_DOMAIN_H
