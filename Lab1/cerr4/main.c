#include <stdio.h>

void decimal_digits(int n,int m,int k)
{
    printf("%d.",n/m);
    n%=m;
    for(int i=0;i<k;i++)
    {
        n*=10;
        printf("%d",n/m);
        n%=m;
    }
    printf("\n");
}

int main(void)
{
    int opt;

    do
    {
        printf("\n=== MENIU ===\n");
        printf("1. Primele k zecimale din numarul n/m\n");
        printf("0. Iesire\n");
        printf("Optiunea: ");

        if (scanf("%d", &opt) != 1)
            return 0;

        if (opt == 1)
        {
            int k, n,m;
            printf("Introduceti n (intreg): ");
            if (scanf("%d", &n) != 1)
                return 0;
            printf("Introduceti m (intreg): ");
            if (scanf("%d", &m) != 1)
                return 0;

            printf("Introduceti k (natural): ");
            if (scanf("%d", &k) != 1)
                return 0;

            printf("n trebuie sa fie natural (>= 0)!\n");
            
            if(m==0)
            {
                printf("nu putem face impartire la 0");
            }
            else if (k < 0)
            {
                printf("k trebuie sa fie natural (>=0)");
            }
            else
            {
                decimal_digits(n,m,k);
            }
        }
        else if (opt != 0)
        {
            printf("Optiune invalida!\n");
        }

    } while (opt != 0);

    return 0;
}