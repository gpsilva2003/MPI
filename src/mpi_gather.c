#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define TAM_VET 10

int main(int argc, char *argv[]) { /* mpi_gather.c  */
int meu_ranque, num_procs, raiz = 0;
int *vet_recebe,  vet_envia[TAM_VET];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	/* O processo raiz aloca o espaço de memória para o vetor de recepção */
	if (meu_ranque == raiz)
        vet_recebe = (int *) malloc(num_procs*TAM_VET*sizeof(int)); 
    /* Cada processo atribui valor inicial ao vetor de envio */
	for (int i = 0; i < TAM_VET; i++) 
         vet_envia[i] = meu_ranque;
    /* O vetor é recebido pelo processo raiz com as partes recebidas de todos processos, incluindo o processo raiz */
	MPI_Gather (vet_envia, TAM_VET, MPI_INT, vet_recebe, TAM_VET, MPI_INT, raiz, MPI_COMM_WORLD);
	/* O processo raiz imprime o vetor recebido */ 
	if (meu_ranque == raiz) {
	    printf("Processo =  %d, recebeu", meu_ranque);
	    for (int i = 0; i < (TAM_VET*num_procs); i ++) {
             printf(" %d", vet_recebe[i]);
	    }
	    printf("\n");
	}
	/* Termina a execução */
	MPI_Finalize();
	return(0);
}
