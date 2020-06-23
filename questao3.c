#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "omp.h"

int totalPrimo(int num, int id, int p);

void main(int argc, char *argv[])
{
    int primos = 0, primos_total = 0;
    int num = atoi(argv[1]);
    int qtd_loops = atoi(argv[2]);
    int size, rank;
    MPI_Status st;
    int count = 0;
    double t1, t2;

    t1 = omp_get_wtime();

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    while (count < qtd_loops)
    {
        MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

        primos_total = totalPrimo(num, rank, size);

        MPI_Reduce(&primos_total, &primos, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0)
        {
            printf("ITERACAO: %i QTD PRIMOS DE 0 A %i = %i\n", count, num, primos);
        }

        num = num * 2;
        count++;
    }

    if (rank == 0)
    {
        t2 = omp_get_wtime();

        printf("\ntempo mpi: %f", t2 - t1);
        printf("\n");
    }

    MPI_Finalize();
}

int totalPrimo(int num, int id, int p)
{
    int aux = 0;
    int qtdPrimos = 0;

    for (int j = 2 + id; j < num; j = j + p)
    {
        for (int i = 1; i <= j; i++)
        {
            if (j % i == 0)
            {
                aux++;
            }
        }
        if (aux <= 2 && j != 0 && j != 1)
            qtdPrimos++;
        aux = 0;
    }

    return qtdPrimos;
}