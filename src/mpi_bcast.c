#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) { /* mpi_bcast.c  */
int valor, meu_ranque, raiz = 0;
MPI_Comm comm=MPI_COMM_WORLD;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &meu_ranque);
    /* Cada processo tem um valor inicial diferente */
    valor = meu_ranque;
    printf("O processo com ranque %d tem inicialmente o valor: %d\n",meu_ranque, valor);
    /* O valor a ser enviado é lido pelo processo raiz */
    if (meu_ranque == raiz) {
        printf("Entre um valor: \n");
        scanf("%d", &valor);    
    }
    /* A rotina de difusão é chamada por todos processos, apenas o processo raiz envia, os demais recebem */
    MPI_Bcast(&valor, 1, MPI_INT, raiz, comm);
    /* O valor agora é o mesmo em todos os processos */
    printf("O processo com ranque %d recebeu o valor: %d\n",meu_ranque, valor);
    /* Termina a execução */
    MPI_Finalize();
    return 0;
}
