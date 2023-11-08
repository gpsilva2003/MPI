#include <stdio.h>
#include <math.h>
#include "mpi.h"
#define TAM 4
int main(int argc, char *argv[]) {
int i, meu_ranque, num_procs;
int raiz = 0;
/* Matriz com os dados a serem enviados */
float matriz[TAM][TAM] =
{1.0, 2.0, 3.0, 4.0,
5.0, 6.0, 7.0, 8.0,
9.0, 10.0, 11.0, 12.0,
13.0, 14.0, 15.0, 16.0};
/* Vetor que vai receber os dados */
float vetor_local [TAM];
MPI_Datatype tipo_linha;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
/* Cria o novo tipo de dados derivado tipo_linha */
MPI_Type_contiguous(TAM, MPI_FLOAT, &tipo_linha);
MPI_Type_commit(&tipo_linha);
/* O processo raiz envia a terceira linha da matriz */
if (meu_ranque == raiz)
MPI_Bcast(&matriz[2][0], 1, tipo_linha, raiz,
MPI_COMM_WORLD);
/* E os demais processos a recebem no vetor local */
else
MPI_Bcast(vetor_local, 1, tipo_linha, raiz,
MPI_COMM_WORLD);
/* Os processos imprimem a linha recebida */
if (meu_ranque != 0) {
printf("Processo %d -", meu_ranque);
for (i = 0; i < TAM; i++)
printf("vetor[%d] = %3.1f ", i,vetor_local[i]);
printf("\n");
}
/* Libera os tipos criados e termina a execução */
MPI_Type_free(&tipo_linha);
MPI_Finalize();
return 0;
}
