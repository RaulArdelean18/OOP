/*
    n = x + (x+1) + (x+2) + ... + (x+k-1) = x * k + k*(k-1)/2
    x = (n - K * (k - 1) / 2) / k
*/

#include <stdio.h>

void write(int n,int x,int k)
{
    for(int i=1;i<=k;i++)
    {
        printf("%d ",x);
        x+=1;
    }
    printf("\n");
}

void all_consecutive_sums(int n)
{
    int found = 0;
    int k = 2;

    while(1)
    {
        long long val = k*(k-1)/2;
        if(val>=n)
            break;
        long long rest = n - val;
        if(rest%k==0)
        {
            long long x = rest/k;
            write(n,(int)x,k);
            found = 1;
        }
        k++;
    }

    if(!found)
        printf("Nu exista un raspuns valid");
}

int main(void)
{
    int opt;

    do
    {
        printf("\n=== MENIU ===\n");
        printf("1. Reprezentari ale lui n ca suma de numere naturale consecutive\n");
        printf("0. Iesire\n");
        printf("Optiunea: ");

        if (scanf("%d", &opt) != 1)
            return 0;

        if (opt == 1)
        {
            int n;
            printf("Introduceti n (natural): ");
            if (scanf("%d", &n) != 1)
                return 0;

            if (n < 0)
            {
                printf("n trebuie sa fie natural (>= 0)!\n");
            }
            else
            {
                all_consecutive_sums(n);
            }
        }
        else if (opt != 0)
        {
            printf("Optiune invalida!\n");
        }

    } while (opt != 0);

    return 0;
}