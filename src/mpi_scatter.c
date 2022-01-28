#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define TAM_VET 10

int main(int argc, char *argv[]) { /* mpi_scatter.c  */
int i, meu_ranque, num_procs, raiz = 0;
int *vet_envia, vet_recebe[TAM_VET];
MPI_Comm com=MPI_COMM_WORLD;
	
	MPI_Init(&argc, &argv);
    	MPI_Comm_rank(com, &meu_ranque);
    	MPI_Comm_size(com, &num_procs);
    	/* O processo raiz aloca o espaço de memória e inicia o vetor */
    	if (meu_ranque == raiz) {
        	vet_envia = (int*) malloc (num_procs*TAM_VET*sizeof(int));
        	for (i = 0; i < (TAM_VET*num_procs); i++) 
             		vet_envia[i] = i;
    	}
    	/* O vetor é distribuído em partes iguais entre os processos, incluindo o processo raiz */
    	MPI_Scatter(vet_envia, TAM_VET, MPI_INT, vet_recebe, TAM_VET, MPI_INT, raiz, com);
	/* Cada processo imprime a parte que recebeu */ 
	printf("Processo =  %d, recebeu", meu_ranque);
	for (i = 0; i < TAM_VET; i ++) 
		printf(" %d", vet_recebe[i]);
	printf("\n");
	/* Termina a execução */
	MPI_Finalize();
	return(0);
}
