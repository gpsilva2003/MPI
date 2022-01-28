#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int main(int argc, char *argv[]) { /* mpi_probe.c  */
int meu_ranque, num_procs, etiq=0;
int* vet_num;
int total_num, origem, destino=1, numeros[MAX];
MPI_Status estado;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* Envia um número aleatório de dados */
    if (meu_ranque == origem) {
        srand(MPI_Wtime());
        total_num = (rand() / (float)RAND_MAX) * MAX;
        MPI_Send(numeros, total_num, MPI_INT, destino, etiq, MPI_COMM_WORLD);
        printf("Processo %d enviou %d números  para processo %d.\n", origem, total_num, destino);
    } 
    else 
        if (meu_ranque == destino) {
    /* Verifica se chegou mensagem do processo origem */
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
    /* Obtém o tamanho da mensagem através do manipulador "estado" */
            MPI_Get_count(&estado, MPI_INT, &total_num);
    /* Aloca um vetor para guardar os números transmitidos */
            vet_num = (int*) malloc(sizeof(int)*total_num);
	    origem = estado.MPI_SOURCE;
	    etiq = estado.MPI_TAG;
    /* Agora recebe a mensagem com o vetor previamente alocado  */
            MPI_Recv(vet_num, total_num, MPI_INT, origem, etiq, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo %d recebeu dinamicamente %d números de %d.\n", destino, total_num, origem);
            free(vet_num);
        }
    MPI_Finalize();
    return(0);
}
