#ifndef OOP_VECTOR_H
#define OOP_VECTOR_H

#include <stddef.h>

typedef void *TElem;

typedef void (*DestroyFunction)(TElem);

typedef struct {
    TElem *elems;
    int lungime;
    int capacitate;
} vector;

vector creeaza_vector(int capacitate_initiala);

void distruge_vector(vector *v);

void distruge_vector_cu_elemente(vector *v, DestroyFunction destroy_elem);

int get_lungime_vector(const vector *v);

TElem get_elem_vector(const vector *v, int pozitie);

void set_elem_vector(vector *v, int pozitie, TElem elem);

void adauga_elem_vector(vector *v, TElem elem);

void redimensioneaza_vector(vector *v);

#endif
