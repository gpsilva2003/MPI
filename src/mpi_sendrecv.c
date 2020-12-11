#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) { /* mpi_sendrecv.c  */
int meu_ranque, num_procs;
int dados, dados_locais;
int destino, etiq=0;
MPI_Status estado;
const int raiz=0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* Se o número de processos não for igual a 2 então aborta */
    if (num_procs != 2) { 
        if (meu_ranque == raiz)
            printf("Por favor execute com apenas 2 processos  \n");
        MPI_Finalize();
        exit(0);
    }
    /* Valor a ser enviado */
    dados = meu_ranque*2 + 1; 
    printf("Processo %d: tem dado %d \n", meu_ranque, dados);
    /* Determina o destino */
    destino = (meu_ranque == raiz)? 1 : 0; 
    MPI_Sendrecv(&dados, 1, MPI_INT, destino, etiq, &dados_locais, 1, MPI_INT, destino, etiq, MPI_COMM_WORLD, &estado);
    printf("Processo %d:  recebeu o  dado: %d\n", meu_ranque, dados_locais);
    MPI_Finalize();
    return(0);
}