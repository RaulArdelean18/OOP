#include "validator.h"
#include <stdexcept>
#include <string>

using namespace std;

void Validator::valideaza(const Domain& c) {
    string erori;

    if (c.get_titlu().empty()) erori += "Titlul nu poate fi vid!\n";
    if (c.get_autor().empty()) erori += "Autorul nu poate fi vid!\n";
    if (c.get_gen().empty()) erori += "Genul nu poate fi vid!\n";
    if (c.get_anul_ap() <= 0) erori += "Anul aparitiei trebuie sa fie pozitiv!\n";

    if (!erori.empty()) {
        throw runtime_error(erori);
    }
}