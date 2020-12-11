#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) { /* mpi_barrier.c  */
int meu_ranque, num_procs;
char resposta;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD,&meu_ranque);
    
    if (meu_ranque == 0 ) {
        printf ("Estou atrasado para a barreira! \n");
        resposta = getchar();
    }
    MPI_Barrier(MPI_COMM_WORLD);
    printf("Passei da barreira. Eu sou o %d de %d processos \n", meu_ranque, num_procs);
  
    MPI_Finalize();
    return(0);
}