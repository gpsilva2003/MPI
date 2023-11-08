#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define TAM 10
int main(int argc, char** argv) {
int meu_ranque, num_procs;
int i, tam_buf;
/* Tamanho do buffer de empacotamento */
float a[TAM];
float b[TAM];
char *buffer;
int posicao = 0;
int destino = 1;
int raiz = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
/* Todos os processos calculam o tamanho do buffer para
envio e recepção */
	MPI_Pack_size(TAM, MPI_FLOAT, MPI_COMM_WORLD, &tam_buf);
	buffer = (char *) malloc(tam_buf * sizeof(char));
/* Só processo raiz envia */
	if (meu_ranque == raiz) {
		for (i = 0; i < TAM; i++)
		a[i] = (float) (i);
/* Empacota os dados e envia a mensagem de difusão */
		MPI_Pack(a, TAM, MPI_FLOAT, buffer, tam_buf, &posicao, MPI_COMM_WORLD);
		MPI_Bcast(buffer, tam_buf, MPI_PACKED, raiz,MPI_COMM_WORLD);
		printf("Valor de posição depois do envio = %d \n", posicao);
	}
	else {
/* Recebe a mensagem de difusão e desempacota os dados
*/
		MPI_Bcast(buffer, tam_buf, MPI_PACKED, raiz,MPI_COMM_WORLD);
		MPI_Unpack(buffer, tam_buf, &posicao, b, TAM,MPI_FLOAT, MPI_COMM_WORLD);
}
/* Só um processo imprime o vetor recebido */
	if (meu_ranque == destino) {
		printf("Valor de posição depois da recepção = %d \n",posicao);
		for (i = 0; i < TAM; i++)
			printf("b[%d] = %3.1f ", i, b[i]);
		fflush(stdout);
	}
/* Termima a execução */
	free (buffer);
	MPI_Finalize();
	return 0;
}
