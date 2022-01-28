#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) { /* mpi_barrier.c  */
int meu_ranque, num_procs;
MPI_Comm comm=MPI_COMM_WORLD;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(comm,&num_procs);
    MPI_Comm_rank(comm,&meu_ranque);
    
    if (meu_ranque == 0 ) {
        printf ("Estou atrasado para a barreira! \n");
        getchar();
    	MPI_Barrier(comm);
    }
    else
    	MPI_Barrier(comm);
    printf("Passei da barreira. Eu sou o %d de %d processos \n", meu_ranque, num_procs);
  
    MPI_Finalize();
    return(0);
}
