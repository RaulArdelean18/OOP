#include "console.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Afiseaza lista de masini din parcul auto
 * @param v : vector, cu TElem Masina
 */
static void afiseaza_vector_masini(const vector *v) {
    if (get_lungime_vector(v) == 0) {
        printf("Nu exista masini care sa corespunda criteriului.\n");
        return;
    }

    for (int i = 0; i < get_lungime_vector(v); i++) {
        Masina *m = (Masina *)get_elem_vector(v, i);
        printf("Masina %d: %s | %s | %s | %s\n",
               i + 1,
               get_nr_inmatriculare(m),
               get_model(m),
               get_categorie(m),
               get_inchiriata(m) ? "inchiriata" : "disponibila");
    }
}

static void free_1(char *a) {
    free(a);
}

static void free_3(char *a, char *b, char *c) {
    free(a);
    free(b);
    free(c);
}

/**
 * Afiseaza meniul principal al aplicatiei
 */
void afisare_meniu() {
    //char *test_leak = (char *)malloc(100*sizeof(char));
    printf("\n===== FIRMA INCHIRIERI AUTO =====\n");
    printf("1. Adauga masina\n");
    printf("2. Actualizeaza masina\n");
    printf("3. Inchiriaza masina\n");
    printf("4. Returneaza masina\n");
    printf("5. Afiseaza toate masinile\n");
    printf("6. Filtreaza dupa model\n");
    printf("7. Filtreaza dupa categorie\n");
    printf("8. Sorteaza dupa model\n");
    printf("9. Sorteaza dupa categorie\n");
    printf("0. Iesire\n");
    printf("Alege optiunea: ");
    ///printf("%s",test_leak);
}

/**
 * Afiseaza toate masinile din aplicatie
 *
 * @param ui: pointer la consola
 */
void ui_afiseaza_masini(Console *ui) {
    int lungime = service_get_lungime(ui->srv);

    if (lungime == 0) {
        printf("Nu exista masini in aplicatie.\n");
        return;
    }

    for (int i = 0; i < lungime; i++) {
        Masina *m = service_get_masina(ui->srv, i);
        printf("Masina %d: %s | %s | %s | %s\n",
               i + 1,
               get_nr_inmatriculare(m),
               get_model(m),
               get_categorie(m),
               get_inchiriata(m) ? "inchiriata" : "disponibila");
    }
}

/**
 * Citeste datele unei masini si incearca sa o adauge in aplicatie
 *
 * @param ui: pointer la consola
 */
void ui_adauga_masina(Console *ui) {
    char *nr_inmatriculare = (char *)malloc(20 * sizeof(char));
    char *model = (char *)malloc(50 * sizeof(char));
    char *categorie = (char *)malloc(30 * sizeof(char));

    if (nr_inmatriculare == NULL || model == NULL || categorie == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        free_3(nr_inmatriculare, model, categorie);
        return;
    }

    printf("Numar inmatriculare: ");
    if (scanf("%19s", nr_inmatriculare) != 1) {
        printf("Eroare la citirea nr_inmatriculare\n");
        free_3(nr_inmatriculare, model, categorie);
        return;
    }

    printf("Model: ");
    if (scanf("%49s", model) != 1) {
        printf("Eroare la citirea modelului\n");
        free_3(nr_inmatriculare, model, categorie);
        return;
    }

    printf("Categorie: ");
    if (scanf("%29s", categorie) != 1) {
        printf("Eroare la citirea categoriei\n");
        free_3(nr_inmatriculare, model, categorie);
        return;
    }

    int rezultat = service_adauga_masina(ui->srv, nr_inmatriculare, model, categorie);

    if (rezultat == 1) {
        printf("Masina a fost adaugata cu succes.\n");
    } else if (rezultat == 0) {
        printf("Exista deja o masina cu acest numar de inmatriculare.\n");
    } else {
        printf("Date invalide.\n");
    }

    free_3(nr_inmatriculare, model, categorie);
}

/**
 * Citeste noile date ale unei masini si incearca sa o actualizeze
 *
 * @param ui: pointer la consola
 */
void ui_actualizeaza_masina(Console *ui) {
    char *nr_inmatriculare = (char *)malloc(20 * sizeof(char));
    char *model_nou = (char *)malloc(50 * sizeof(char));
    char *categorie_noua = (char *)malloc(30 * sizeof(char));

    if (nr_inmatriculare == NULL || model_nou == NULL || categorie_noua == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        free_3(nr_inmatriculare, model_nou, categorie_noua);
        return;
    }

    printf("Numar inmatriculare masina de actualizat: ");
    if (scanf("%19s", nr_inmatriculare) != 1) {
        printf("Eroare la citirea nr_inmatriculare\n");
        free_3(nr_inmatriculare, model_nou, categorie_noua);
        return;
    }

    printf("Model nou: ");
    if (scanf("%49s", model_nou) != 1) {
        printf("Eroare la citirea noului modelului\n");
        free_3(nr_inmatriculare, model_nou, categorie_noua);
        return;
    }

    printf("Categorie noua: ");
    if (scanf("%29s", categorie_noua) != 1) {
        printf("Eroare la citirea noii categorii\n");
        free_3(nr_inmatriculare, model_nou, categorie_noua);
        return;
    }

    int rezultat = service_actualizeaza_masina(ui->srv, nr_inmatriculare, model_nou, categorie_noua);

    if (rezultat == 1) {
        printf("Masina a fost actualizata cu succes.\n");
    } else if (rezultat == 0) {
        printf("Nu exista masina cu acest numar de inmatriculare.\n");
    } else {
        printf("Date invalide.\n");
    }

    free_3(nr_inmatriculare, model_nou, categorie_noua);
}

/**
 * Citeste numarul de inmatriculare al unei masini si incearca sa o inchirieze
 *
 * @param ui: pointer la consola
 */
void ui_inchiriaza_masina(Console *ui) {
    char *nr_inmatriculare = (char *)malloc(20 * sizeof(char));

    if (nr_inmatriculare == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        return;
    }

    printf("Numar inmatriculare masina de inchiriat: ");

    if (scanf("%19s", nr_inmatriculare) != 1) {
        printf("Eroare la nr_inmatriculare a masinii de inchiriat\n");
        free_1(nr_inmatriculare);
        return;
    }

    int rezultat = service_inchiriaza_masina(ui->srv, nr_inmatriculare);

    if (rezultat == 1) {
        printf("Masina a fost inchiriata cu succes.\n");
    } else if (rezultat == 0) {
        printf("Nu exista masina cu acest numar de inmatriculare.\n");
    } else {
        printf("Masina este deja inchiriata.\n");
    }

    free_1(nr_inmatriculare);
}

/**
 * Citeste numarul de inmatriculare al unei masini si incearca sa o returneze
 *
 * @param ui: pointer la consola
 */
void ui_returneaza_masina(Console *ui) {
    char *nr_inmatriculare = (char *)malloc(20 * sizeof(char));

    if (nr_inmatriculare == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        return;
    }

    printf("Numar inmatriculare masina de returnat: ");

    if (scanf("%19s", nr_inmatriculare) != 1) {
        printf("Eroare la nr_inmatriculare a masinii de returnat\n");
        free_1(nr_inmatriculare);
        return;
    }

    int rezultat = service_returneaza_masina(ui->srv, nr_inmatriculare);

    if (rezultat == 1) {
        printf("Masina a fost returnata cu succes.\n");
    } else if (rezultat == 0) {
        printf("Nu exista masina cu acest numar de inmatriculare.\n");
    } else {
        printf("Masina este deja disponibila.\n");
    }

    free_1(nr_inmatriculare);
}

void ui_filtreaza_dupa_model(Console *ui) {
    char *model = (char *)malloc(50 * sizeof(char));

    if (model == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        return;
    }

    printf("Model cautat: ");
    if (scanf("%49s", model) != 1) {
        printf("Eroare la citirea modelului\n");
        free_1(model);
        return;
    }

    vector rezultat = service_filtreaza_masini_dupa_model(ui->srv, model);
    afiseaza_vector_masini(&rezultat);
    distruge_vector(&rezultat);

    free_1(model);
}

void ui_filtreaza_dupa_categorie(Console *ui) {
    char *categorie = (char *)malloc(30 * sizeof(char));

    if (categorie == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        return;
    }

    printf("Categorie cautata: ");
    if (scanf("%29s", categorie) != 1) {
        printf("Eroare la citirea categoriei\n");
        free_1(categorie);
        return;
    }

    vector rezultat = service_filtreaza_masini_dupa_categorie(ui->srv, categorie);
    afiseaza_vector_masini(&rezultat);
    distruge_vector(&rezultat);

    free_1(categorie);
}

static int citeste_directie_sortare() {
    int crescator;
    printf("1 pentru crescator, 0 pentru descrescator: ");
    if (scanf("%d", &crescator) != 1) {
        printf("Eroare la citirea directiei de sortare\n");
        return -1;
    }
    return crescator;
}

void ui_sorteaza_dupa_model(Console *ui) {
    int crescator = citeste_directie_sortare();
    if (crescator < 0 || crescator > 1) {
        printf("Eroare la citirea directiei de sortare\n");
        return;
    }

    vector rezultat = service_sorteaza_masini_dupa_model(ui->srv, crescator);
    afiseaza_vector_masini(&rezultat);
    distruge_vector(&rezultat);
}

void ui_sorteaza_dupa_categorie(Console *ui) {
    int crescator = citeste_directie_sortare();
    if (crescator < 0 || crescator > 1) {
        printf("Eroare la citirea directiei de sortare\n");
        return;
    }

    vector rezultat = service_sorteaza_masini_dupa_categorie(ui->srv, crescator);
    afiseaza_vector_masini(&rezultat);
    distruge_vector(&rezultat);
}

/**
 * Initializeaza consola cu service-ul primit
 *
 * @ui - pointer la consola
 * @srv - pointer la service
 */
void init_console(Console *ui, Service *srv) {
    ui->srv = srv;
}

/**
 * Ruleaza meniul principal al aplicatiei
 *
 * @ui - pointer la consola
 */
void run(Console *ui) {
    int optiune;

    while (1) {
        afisare_meniu();

        if (scanf("%d", &optiune) != 1) {
            printf("Eroare la citirea optiunii\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            continue;
        }

        if (optiune == 0) {
            printf("Aplicatia se inchide.\n");
            break;
        }

        switch (optiune) {
            case 1:
                ui_adauga_masina(ui);
                break;
            case 2:
                ui_actualizeaza_masina(ui);
                break;
            case 3:
                ui_inchiriaza_masina(ui);
                break;
            case 4:
                ui_returneaza_masina(ui);
                break;
            case 5:
                ui_afiseaza_masini(ui);
                break;
            case 6:
                ui_filtreaza_dupa_model(ui);
                break;
            case 7:
                ui_filtreaza_dupa_categorie(ui);
                break;
            case 8:
                ui_sorteaza_dupa_model(ui);
                break;
            case 9:
                ui_sorteaza_dupa_categorie(ui);
                break;
            default:
                printf("Optiune invalida.\n");
        }
    }
}