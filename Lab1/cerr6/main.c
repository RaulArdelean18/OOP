#include <stdio.h>
#include <stdlib.h>

/**
 * Descriere: calculeaza pozitia unui element (i, j) intr-un vector
 * Parametri: i - linia, j - coloana
 * Preconditii: i >= 0, 0 <= j <= i
 * Postconditii: ceturneaza indexul calculat prin formula i*(i+1)/2 + j
 */
int idx(int i, int j)
{
    return i * (i + 1) / 2 + j;
}

/**
 * Descriere: calculeaza elementele triunghiului lui Pascal
 * Parametri: n - numarul de linii dorite
 * Preconditii: n >= 0
 * Postconditii: afiseaza triunghiul pe ecran si elibereaza memoria utilizata
 */
void PascalTriangle(int n)
{
    long long all = (long long)(n + 1) * (n + 2) / 2;
    long long *mat = malloc(all * sizeof(long long));
    if (!mat)
        exit(1); /// dau eroare 1, ca sa stiu daca crapa programul

    mat[idx(0, 0)] = 1;

    for (int i = 1; i <= n; i++)
    {
        mat[idx(i, 0)] = 1;
        mat[idx(i, i)] = 1;
        for (int j = 1; j < i; j++)
        {
            mat[idx(i, j)] = mat[idx(i - 1, j - 1)] + mat[idx(i - 1, j)];
        }
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("%lld ", mat[idx(i, j)]);
        }
        printf("\n");
    }

    free(mat);
}

/**
 * Descriere: afiseaza un meniu interactiv pentru utilizator
 * Parametri: nu are
 * Preconditii: nu are
 * Postconditii: ruleaza programul pana la alegerea optiunii de iesire
 */
void ui()
{
    while (1)
    {
        printf("=== Generator triunghiul lui Pascal ====\n\n");

        char opt;

        printf("1. Doresc afisarea triunghiul lui Pascal | 2. Exit\n\n");
        printf("Optiunea: ");
        scanf(" %c", &opt);

        if (opt == '1')
        {
            int n;
            printf("Introduceti n, numarul de linii din triunghiul lui Pascal:");
            scanf("%d", &n);

            PascalTriangle(n);
        }
        else if (opt == '2')
        {
            break;
        }
        else
        {
            printf("Optiune invalida, repetati\n\n");
        }
    }
}

int main()
{
    ui();
    return 0;
}