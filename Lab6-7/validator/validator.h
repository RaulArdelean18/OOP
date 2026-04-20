//
// Created by Raul_A on 06/04/2026.
//

#ifndef LAB6_7_VALIDATOR_H
#define LAB6_7_VALIDATOR_H

#include "../domain/domain.h"
#include "../exceptions/exceptions.h"

class Validator {
public:
    static void valideaza(const Domain& c);
};

#endif