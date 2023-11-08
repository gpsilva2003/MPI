#include "mpi.h"
#include <stdio.h>
#define TAM 4
int main(int argc, char *argv[]) {
int num_procs, meu_ranque;
int i, raiz=0;
int cont, tam_bloco, salto; /* Parâmetros da função
  MPI_Type_vector */
/* Matriz com os dados a serem enviados */
float matriz[TAM][TAM] =
{1.0, 2.0, 3.0, 4.0,
5.0, 6.0, 7.0, 8.0,
9.0, 10.0, 11.0, 12.0,
13.0, 14.0, 15.0, 16.0};
/* Vetor local para receber os dados */
float vetor_local[TAM];
MPI_Datatype tipo_coluna;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
/* Prepara os argumentos para a rotina */
cont = TAM;
tam_bloco = 1;
salto = TAM;
/* Cria o novo tipo de dados derivado tipo_coluna */
MPI_Type_vector(cont, tam_bloco, salto, MPI_FLOAT, &tipo_coluna);
MPI_Type_commit(&tipo_coluna);
/* O processo raiz envia a coluna para os demais
processos */
if (meu_ranque == 0)
MPI_Bcast(&matriz[0][1], 1, tipo_coluna, raiz,
MPI_COMM_WORLD);
else
/* Os outros processos recebem os dados no vetor local */
MPI_Bcast(vetor_local, 4, MPI_FLOAT, raiz, MPI_COMM_WORLD);
/* Os processos imprimem a coluna recebida */
if (meu_ranque != 0) {
printf("Processo %d -", meu_ranque);
for (i =0; i < TAM; i++)
printf("vetor[%d] = %3.1f ", i, vetor_local[i]);
printf("\n");
}
/* Libera os tipos criados e termina a execução */
MPI_Type_free(&tipo_coluna);
MPI_Finalize();
return 0;
}
