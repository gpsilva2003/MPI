#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define NUM_PROCS 8
int main(int argc, char *argv[]) {

int meu_ranque, num_procs;
int novo_ranque, envia, reducao;
int ranques1[4]={0,1,2,3}, ranques2[4]={4,5,6,7};
MPI_Group grupo_orig, grupo_novo;
MPI_Comm com_novo;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
/* Verifica se o número de processos está correto */
	if (num_procs!= NUM_PROCS) {
	if (meu_ranque == 0)
		printf("Deve especificar número de processos igual a %d. Terminando.\n", NUM_PROCS);
		MPI_Finalize();
		exit (1);
}
	envia = meu_ranque;
/* Extrai o manipulador do grupo original */
	MPI_Comm_group(MPI_COMM_WORLD, &grupo_orig);
/* Divide os processos em dois grupos distintos baseado
no ranque */
	if (meu_ranque < NUM_PROCS/2) {
		MPI_Group_incl(grupo_orig, NUM_PROCS/2, ranques1, &grupo_novo);
	}
	else {
		MPI_Group_incl(grupo_orig, NUM_PROCS/2, ranques2, &grupo_novo);
	}
/* Cria um novo comunicador e realiza as operações de comunicação coletiva */
	MPI_Comm_create(MPI_COMM_WORLD, grupo_novo, &com_novo);
        MPI_Allreduce(&envia, &reducao, 1, MPI_INT, MPI_SUM, com_novo);
	MPI_Group_rank (grupo_novo, &novo_ranque);
/* Cada processo imprime o ranque antigo, o novo ranque e
o valor da redução */
	printf("ranque= %d Novo ranque= %d redução= %d \n", meu_ranque, novo_ranque, reducao);
/* Libera grupos, comunicadores e termina o MPI */
	MPI_Comm_free(&com_novo);
	MPI_Group_free(&grupo_novo);
	MPI_Finalize();
	return 0;
}
