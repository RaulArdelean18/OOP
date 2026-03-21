#ifndef OOP_VALIDATOR_H
#define OOP_VALIDATOR_H

#include "../domain/car.h"

int valideaza_masina(const Masina *m);

int valideaza_nr_inmatriculare(const char *nr_inmatriculare);

int valideaza_model(const char *model);

int valideaza_categorie(const char *categorie);

#endif
