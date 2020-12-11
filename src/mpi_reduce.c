#include <stdio.h> 
#include <math.h>
#include "mpi.h" 
#define TAM 5

int main(int argc, char *argv[]) { /* mpi_reduce.c  */
int meu_ranque, num_procs, i, raiz = 0;      
float vet_envia [TAM] ; /* Vetor a ser enviado  */ 
float vet_recebe [TAM]; /* Vetor a ser recebido */  

    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque); 
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); 
    /* Preenche o vetor com valores que dependem do ranque */
    for (i = 0; i < TAM; i++)  
        vet_envia[i] = (float) (meu_ranque*TAM+i);
    /* Faz a redução, encontrando o valor máximo do vetor */
    MPI_Reduce(vet_envia, vet_recebe, TAM, MPI_FLOAT, MPI_MAX, raiz, MPI_COMM_WORLD); 
    /* O processo raiz imprime o resultado da operação de redução */
    if (meu_ranque == raiz) { 
        for (i = 0; i < TAM; i++) 
            printf("vet_recebe[%d] = %3.1f ", i,vet_recebe[i]); 
        printf("\n\n");     } 
    MPI_Finalize();
    return(0);
}
