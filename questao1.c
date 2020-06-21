#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int validaPrimo(int num);
void primos_iterativo(int n, int loops);
void primos_paralelo(int n, int loops);
int validaPrimoParalelo(int num);

void main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    int loops = atoi(argv[2]);

    primos_iterativo(n, loops);
    primos_paralelo(n, loops);
}

int validaPrimo(int num)
{
    int aux = 0;

    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
        {
            aux++;
        }
    }

    if (aux <= 2 && num != 0 && num != 1)
        return 1;

    return 0;
}

int validaPrimoParalelo(int num)
{

    int result = 0;

#pragma omp parallel
    {

        int aux = 0;
        int procs = omp_get_num_procs();

        omp_set_num_threads(procs);

        #pragma omp for
        for (int i = 1; i <= num; i++)
        {
            if (num % i == 0)
            {
                aux++;
            }
        }

        #pragma omp atomic
        result += aux;
    }

    if (result <= 2 && num != 0 && num != 1)
        return 1;

    return 0;
}

void primos_paralelo(int n, int loops)
{

    printf("\nparalelo\n");

    int qtdPrimos = 0;
    int primo = 0;
    double t1, t2;

    printf("QTD de threads: %i \n", omp_get_num_procs());

    t1 = omp_get_wtime();
    for (int j = 0; j < loops; j++)
    {
        for (int i = 0; i < n; i++)
        {

            primo = validaPrimoParalelo(i);

            if (primo == 1)
            {
                qtdPrimos++;
            }
        }

        printf("iteracao: %i Quantidade de primos de 0 ->%i = %i \n", j + 1, n, qtdPrimos);
        n = n * 2;
        qtdPrimos = 0;
    }
    t2 = omp_get_wtime();

    printf("\ntempo paralelo: %f", t2 - t1);
    printf("\n");
}

void primos_iterativo(int n, int loops)
{

    printf("\niterativo\n");

    int qtdPrimos = 0;
    int primo = 0;
    double t1, t2;

    t1 = omp_get_wtime();

    for (int j = 0; j < loops; j++)
    {
        for (int i = 0; i < n; i++)
        {

            primo = validaPrimo(i);

            if (primo == 1)
            {
                qtdPrimos++;
            }
        }

        printf("iteracao: %i Quantidade de primos de 0 ->%i = %i \n", j + 1, n, qtdPrimos);
        n = n * 2;
        qtdPrimos = 0;
    }
    t2 = omp_get_wtime();

    printf("\ntempo iterativo: %f", t2 - t1);
    printf("\n");
}