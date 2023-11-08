#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define NUM_PROCS 10
int main(int argc, char *argv[]) {
int meu_ranque, num_procs;
int novo_ranque;
int ranques1[6]={0,2,3,4,5,8}, ranques2[5]={9,4,0,2,8};
MPI_Group grupo_orig, grupo1, grupo2, grupo_novo;
MPI_Comm com_novo;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
/* Verifica se o número de processos está correto */
if (num_procs!= NUM_PROCS) {
if (meu_ranque == 0)
printf("Deve especificar o número de processos igual a %d. Terminando.\n", NUM_PROCS);
MPI_Finalize();
exit (1);
}
/* Extrai o manipulador do grupo original */
MPI_Comm_group(MPI_COMM_WORLD, &grupo_orig);
/* Divide os processos em dois grupos distintos baseado
no ranque */
MPI_Group_incl(grupo_orig, 6, ranques1, &grupo1);
MPI_Group_incl(grupo_orig, 5, ranques2, &grupo2);
MPI_Group_union(grupo1, grupo2, &grupo_novo);
/* Cria um novo comunicador verifica o seu ranque */
MPI_Comm_create(MPI_COMM_WORLD, grupo_novo, &com_novo);
MPI_Group_rank (grupo_novo, &novo_ranque);
/* Cada processo imprime o ranque antigo e o novo ranque
*/
if (novo_ranque != MPI_UNDEFINED) {
printf("ranque= %d Novo ranque= %d \n", meu_ranque,
novo_ranque);
/* Libera comunicador criado */
MPI_Comm_free(&com_novo);
}
/* Libera grupos criados e termina o MPI */
MPI_Group_free(&grupo_novo);
MPI_Group_free(&grupo1);
MPI_Group_free(&grupo2);
MPI_Finalize();
return 0;
}
