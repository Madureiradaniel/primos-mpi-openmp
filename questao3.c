#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

// verificar quantidade de numeros primos entre 0 e N
int validaPrimo(int num);

void main(int argc, char *argv[])
{

    int size, rank, numero;
    int valor = 0;
    int novo_valor = 0;
    int total = 0;
    MPI_Status st;
    int n;
    int aux = 0;
    int aux2 = 0;

    MPI_Init(&argc, &argv);

    numero = atoi(argv[1]);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {

        for (int i = 0; i < size; i++)
        {
            n = aux * 2;
            MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            //printf("Enviando numero para verificar se é primo %i\n", i);
            fflush(stdout);
            aux++;
        }

        for (int i = 0; i < size; i++)
        {
            MPI_Recv(&novo_valor, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
            if (novo_valor != 0)
            {
                total = total + 1;
            }
            printf("total de primos entre 0 e %i = %i\n", aux2, total);
            fflush(stdout);
            aux2++;
        }
    }
    else
    {
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
        //printf("Recebendo do para verificar se e primo: %i\n", n);
        fflush(stdout);

        novo_valor = validaPrimo(n);

        MPI_Send(&novo_valor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        fflush(stdout);
    }

    MPI_Finalize();
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

        if(aux >2){
            break;
        }
    }

    if (aux <= 2 && num != 0 && num != 1)
        return 1;

    return 0;
}