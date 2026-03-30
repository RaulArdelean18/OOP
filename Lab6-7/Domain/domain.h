//
// Created by Raul_A on 30/03/2026.
//

#ifndef LAB6_7_DOMAIN_H
#define LAB6_7_DOMAIN_H
#include <string>
using namespace std;

class Domain {
private:
    string titlu;
    string autor;
    string gen;
    int anul_ap;

public:
    Domain(const string &titlu, const string &autor, const string &gen, const int anul_ap);

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
    const int get_anul_ap() const;

    /**
     * Setter titlu
     */
    void setter_titlu(const string &titlu);

    /**
     * Setter autor
     */
    void setter_autor(const string &autor);

    /**
     * Setter gen
     */
    void setter_gen(const string &gen);

    /**
     * Setter anul aparitie
     */
    void setter_anul_ap(const int anul_ap);
};

#endif //LAB6_7_DOMAIN_H
