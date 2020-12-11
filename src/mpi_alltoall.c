#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) { /* mpi_alltoall.c  */
int i, meu_ranque, num_procs;
int *vetor_entrada, *vetor_saida;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* Aloca e atribui valor inicial os dados */
    vetor_entrada = (int*) malloc(num_procs * sizeof(int));
    vetor_saida  = (int*) malloc(num_procs * sizeof(int));
    for (i = 0; i < num_procs; i++) 
        vetor_entrada[i] = meu_ranque * num_procs + i;
    /* Imprime a entrada dada para a função MPI_Alltoall */
    printf("Entrada do processo %d: ", meu_ranque);
    for (i = 0; i < num_procs; i++) 
        printf("%d ", vetor_entrada[i]);
    printf("\n");
    /* Reorganiza os dados */
    MPI_Alltoall(vetor_entrada, 1, MPI_INT, vetor_saida, 1, MPI_INT, MPI_COMM_WORLD);
    /* Imprime a saida da função MPI_Alltoall */
    printf("Saida do processo %d: ", meu_ranque);
    for (i = 0; i < num_procs; i++) {
        printf("%d ", vetor_saida[i]);
    }
    printf("\n");
    /* Desaloca os vetores e finaliza o MPI */
    free(vetor_saida);
    free(vetor_entrada);
    MPI_Finalize();
    return(0);
}
