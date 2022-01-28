#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#define NELEM 1024

int main(int argc, char *argv[]) {  /* mpi_allgather.c  */
int i, meu_ranque, num_procs;
float *medias_parc = NULL;
float *sub_nums_aleat = NULL;
float soma_local=0, soma_medias=0;
float media, media_local ;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
   /* Sementes diferentes para cada processo  */
   srand(meu_ranque+meu_ranque*meu_ranque);
   /* Cria um vetor de números aleatórios em cada processo */
   sub_nums_aleat  = (float *)malloc(sizeof(float) * NELEM);
   for (i = 0; i < NELEM; i++) 
        sub_nums_aleat[i] = (rand() / (float)RAND_MAX);
   /* Soma os números localmente */
   for (i = 0; i < NELEM; i++) 
        soma_local += sub_nums_aleat[i];
   media_local = soma_local / NELEM;
   /* Imprime a soma e média dos números aleatórios em cada processo */
   printf("Soma local para o processo %d - %f, media local = %f\n", meu_ranque, soma_local, soma_local / NELEM);
   /* Coleta todas as médias parciais de todos os processos */
  medias_parc = (float*)malloc(sizeof(float) * num_procs);
  MPI_Allgather(&media_local, 1, MPI_FLOAT, medias_parc, 1, MPI_FLOAT, MPI_COMM_WORLD);
  /* Calcula a média total de todos os números. */
  for (i = 0; i < num_procs; i++) 
        soma_medias += medias_parc[i];
  media = soma_medias / num_procs;
  printf("Média de todos os elementos calculada no processo %d é  %f\n", meu_ranque, media);
  /* Libera espaço alocado  */
  free(medias_parc);
  free(sub_nums_aleat);
  MPI_Finalize();
  return(0);
}
