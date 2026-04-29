//
// Created by Raul_A on 27/04/2026.
//

#ifndef LAB6_7_UNDO_H
#define LAB6_7_UNDO_H

#include "../repo/repo.h"
#include "../Domain/domain.h"

// Clasa abstracta cu o singura metoda doUndo
class ActiuneUndo {
public:
    virtual void doUndo() = 0;

    virtual ~ActiuneUndo() = default;
};

// Undo pentru operatia de adaugare: stergem elementul adaugat
class UndoAdauga : public ActiuneUndo {
private:
    AbstractRepo &repo;
    Domain carte_adaugata;

public:
    UndoAdauga(AbstractRepo &repo_ref, const Domain &carte)
        : repo(repo_ref), carte_adaugata(carte) {
    }

    void doUndo() override {
        repo.sterge(carte_adaugata.get_titlu());
    }
};

// Undo pentru operatia de stergere: readaugam elementul sters
class UndoSterge : public ActiuneUndo {
private:
    AbstractRepo &repo;
    Domain carte_stearsa;

public:
    UndoSterge(AbstractRepo &repo_ref, const Domain &carte)
        : repo(repo_ref), carte_stearsa(carte) {
    }

    void doUndo() override {
        repo.adauga(carte_stearsa);
    }
};

// Undo pentru operatia de modificare: restauram cartea originala
class UndoModifica : public ActiuneUndo {
private:
    AbstractRepo &repo;
    std::string titlu_nou; // titlul curent (dupa modificare)
    Domain carte_originala; // cartea de dinainte de modificare
public:
    UndoModifica(AbstractRepo &repo_ref, const std::string &titlu_dupa, const Domain &carte_inainte)
        : repo(repo_ref), titlu_nou(titlu_dupa), carte_originala(carte_inainte) {
    }

    void doUndo() override {
        repo.modifica(titlu_nou, carte_originala);
    }
};

#endif //LAB6_7_UNDO_H
