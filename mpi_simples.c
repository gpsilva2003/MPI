#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]) { /* mpi_simples.c  */
int meu_ranque, num_procs;
int origem, destino, etiq = 0;
char mensagem[200];
MPI_Status estado;
    /* Chamada inicial para o MPI */
    MPI_Init(&argc, &argv);
    /* Determina ranque e número de processos em execução */
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* Todos os processos com ranque diferente de 0 enviam uma mensagem */
    if (meu_ranque != 0) {
        sprintf(mensagem, "Processo %d está vivo!", meu_ranque);
        destino = 0;
        MPI_Send(mensagem, strlen(mensagem)+1, MPI_CHAR, destino, etiq, MPI_COMM_WORLD);
    } 
    /* Processo com ranque 0 recebe num_procs-1 mensagens */
    else {
        for (origem = 1; origem < num_procs; origem++) {
            MPI_Recv(mensagem, 200, MPI_CHAR, origem, etiq, MPI_COMM_WORLD, &estado);
    /* Imprime as mensagens recebidas */
            printf("%s\n",mensagem); 
        }
    } 
    MPI_Finalize();
    return(0);
}