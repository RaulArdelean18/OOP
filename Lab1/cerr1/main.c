#include <stdio.h>

/**
 * Verifica daca un numar natural este prim
 * @param n - numar intreg
 * PRE: n >= 0
 * POST: returneaza 1 daca n este prim, 0 altfel
 */
int prime(int n)
{
    if (n < 2)
        return 0;
    if (n < 4)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    for (int d = 5; d * d <= n; d += 6)
        if (n % d == 0 || n % (d + 2) == 0)
            return 0;

    return 1;
}

/**
 * Afiseaza toate numerele prime mai mici decat n
 * @param n - numar natural
 * PRE: n >= 0
 * POST: se afiseaza toate numerele prime < n
 */
void generate_numbers(int n)
{
    for (int i = 2; i < n; i++)
        if (prime(i))
            printf("%d ", i);
    printf("\n");
}

int main()
{
    int opt;

    do
    {
        printf("\n=== MENIU ===\n");
        printf("1. Genereaza numere prime\n");
        printf("0. Iesire\n");
        printf("Optiunea: ");
        scanf("%d", &opt);

        if (opt == 1)
        {
            int n;
            printf("Introduceti n: ");
            scanf("%d", &n);

            if (n < 0)
                printf("n trebuie sa fie natural!\n");
            else
                generate_numbers(n);
        }

    } while (opt != 0);

    return 0;
}
