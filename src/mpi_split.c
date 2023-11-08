#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[]) {
int meu_ranque, num_procs;
int cor;
int ranque_linha, num_procs_linha;
MPI_Comm com_linha;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
/* Determina a cor considerando linhas com 4 processos
cada */
cor = meu_ranque / 4;
/* Divide o comunicador baseado na cor e usa o ranque
original para ordenação */
MPI_Comm_split(MPI_COMM_WORLD, cor, meu_ranque, &com_linha);
MPI_Comm_rank(com_linha, &ranque_linha);
MPI_Comm_size(com_linha, &num_procs_linha);
/* Cada processo imprime o ranque antigo, o novo ranque e
o número de processos */
printf("RANQUE/TAMANHO GLOBAL: %d/%d \t RANQUE/TAMANHO LINHA %d/%d\n", meu_ranque, num_procs, ranque_linha, num_procs_linha);
/* Libera comunicadores e termina o MPI */
MPI_Comm_free(&com_linha);
MPI_Finalize();
return 0;
}
