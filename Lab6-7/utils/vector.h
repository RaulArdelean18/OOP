//
// Created by Raul_A on 06/04/2026.
//

#ifndef LAB6_7_VECTOR_H
#define LAB6_7_VECTOR_H

#include <stdexcept>

template<typename T>
class MyVector {
private:
    T* elems;
    int lg;
    int cap;

    void redim() {
        cap *= 2;
        T* aux = new T[cap];
        for (int i = 0; i < lg; i++) {
            aux[i] = elems[i];
        }
        delete[] elems;
        elems = aux;
    }

public:
    MyVector() : elems(new T[2]), lg(0), cap(2) {
    }

    MyVector(const MyVector& other) : elems(new T[other.cap]), lg(other.lg), cap(other.cap) {
        for (int i = 0; i < lg; i++) {
            elems[i] = other.elems[i];
        }
    }

    MyVector& operator=(const MyVector& other) {
        if (this == &other) {
            return *this;
        }

        delete[] elems;
        cap = other.cap;
        lg = other.lg;
        elems = new T[cap];

        for (int i = 0; i < lg; i++) {
            elems[i] = other.elems[i];
        }

        return *this;
    }

    ~MyVector() {
        delete[] elems;
    }

    void push_back(const T& elem) {
        if (lg == cap) {
            redim();
        }
        elems[lg++] = elem;
    }

    void erase(int poz) {
        if (poz < 0 || poz >= lg) {
            throw std::out_of_range("Pozitie invalida!");
        }

        for (int i = poz; i < lg - 1; i++) {
            elems[i] = elems[i + 1];
        }
        lg--;
    }

    int size() const {
        return lg;
    }

    bool empty() const {
        return lg == 0;
    }

    T& operator[](int poz) {
        if (poz < 0 || poz >= lg) {
            throw std::out_of_range("Pozitie invalida!");
        }
        return elems[poz];
    }

    const T& operator[](int poz) const {
        if (poz < 0 || poz >= lg) {
            throw std::out_of_range("Pozitie invalida!");
        }
        return elems[poz];
    }

    T* begin() {
        return elems;
    }

    T* end() {
        return elems + lg;
    }

    const T* begin() const {
        return elems;
    }

    const T* end() const {
        return elems + lg;
    }
};

#endif //LAB6_7_VECTOR_H