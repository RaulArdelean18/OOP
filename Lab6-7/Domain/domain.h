#ifndef LAB6_7_DOMAIN_H
#define LAB6_7_DOMAIN_H

#include <string>

class Domain {
private:
    std::string titlu;
    std::string autor;
    std::string gen;
    int anul_ap;

public:
    Domain();
    Domain(const std::string &titlu_nou, const std::string &autor_nou, const std::string &gen_nou, int an_ap_nou);
    Domain(const Domain &other);
    Domain& operator=(const Domain &other);

    const std::string &get_titlu() const;
    const std::string &get_autor() const;
    const std::string &get_gen() const;
    int get_anul_ap() const;

    void setter_titlu(const std::string &titlu_nou);
    void setter_autor(const std::string &autor_nou);
    void setter_gen(const std::string &gen_nou);
    void setter_anul_ap(int anul_ap_nou);
};

#endif //LAB6_7_DOMAIN_H