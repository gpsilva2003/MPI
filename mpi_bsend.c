#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define TAM 4

int main(int argc, char *argv[]) { /* mpi_bsend.c  */
int i, j, meu_ranque, num_procs;
int pot2, meu_valor, reducao[TAM];
int destino, recebido[TAM], etiq=1, cont=TAM;
MPI_Status estado;
void *buffer;
int tam_buffer;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* Aborta se o número de processos não for potência de 2 */
    pot2 = num_procs;
    while (((pot2 % 2) == 0) && pot2 > 1)
        pot2 /= 2;
    if (pot2 != 1) {
        if (meu_ranque == 0)
           printf("Por favor execute com número de processos potencia de 2 \n");
        MPI_Finalize();
        exit(0);
        }
    /* Faz a alocação do espaço para o buffer de envio */
    MPI_Pack_size(TAM, MPI_INT, MPI_COMM_WORLD, &tam_buffer);
    tam_buffer = tam_buffer +  MPI_BSEND_OVERHEAD;
    buffer =(void*) malloc(tam_buffer);
    MPI_Buffer_attach(buffer, tam_buffer);
    if (meu_ranque == 0)
        printf("Alocados %d bytes \n", tam_buffer);
    /* Cada processo tem um valor diferente para a redução */
    meu_valor = meu_ranque*num_procs;
    for (j = 0; j < TAM; j++)
         reducao[j]  = meu_valor;
    /* Realiza a troca de mensagens no padrão do algoritmo de "recursive doubling" */
    for (i = 1; i <= (num_procs/2); i += i) {
        if ((meu_ranque/i)%2 == 0) 
            destino = meu_ranque + i;
        else
            destino = meu_ranque - i;
    /* Faz as operações de envio e recepção, nesta ordem */
    MPI_Bsend(&reducao, cont, MPI_INT, destino, etiq, MPI_COMM_WORLD);
    MPI_Recv(&recebido, cont, MPI_INT, destino, etiq, MPI_COMM_WORLD, &estado);
   /* Realiza operação de redução com os dados recebidos */
    for (j = 0; j < TAM; j++)
        if (recebido[j] > reducao[j])
            reducao[j] = recebido[j];
    }
    printf("Meus valores = %d %d %d %d \t", meu_valor, meu_valor, meu_valor, meu_valor);
    printf("Redução = ");
    for (j = 0; j < TAM; j++)
        printf(" %d", reducao[j]);
    printf("\n");
    /* Note o uso do & na passagem de parâmetros */
    MPI_Buffer_detach(&buffer, &tam_buffer);  
    free (buffer);
    MPI_Finalize();
    return(0);
}