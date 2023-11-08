#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define NELEM 25
int main(int argc, char *argv[]) {
int num_procs, meu_ranque, origem=0;
int raiz = 0, etiq = 1, i;
typedef struct {
float x, y, z;
float velocidade;
int n, tipo;
} Particula;
Particula p[NELEM], particulas[NELEM];
MPI_Datatype tipo_particula, tipos_antigos[2];
int tam_blocos[2];
MPI_Status estado;
/* O tipo MPI_Aint é usado para manter a consistência com a
sintaxe da rotina MPI_Type_get_extent */
MPI_Aint deslocamentos[2], lim_inf, extensao;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
/* Prepara a descrição dos 4 campos MPI_FLOAT, ou seja, x
, y, z e velocidade */
	deslocamentos[0] = 0;
	tipos_antigos[0] = MPI_FLOAT;
	tam_blocos[0] = 4;
/* Prepara a descrição dos 2 campos MPI_INT, ou seja, n e
tipo. */
/* É necessário primeiro descobrir o offset determinando
o tamanho de um MPI_FLOAT */
	MPI_Type_get_extent(MPI_FLOAT, &lim_inf, &extensao);
	deslocamentos[1] = 4 * extensao;
	tipos_antigos[1] = MPI_INT;
	tam_blocos[1] = 2;
/* Define agora o tipo estruturado e o publica */
	MPI_Type_create_struct(2, tam_blocos, deslocamentos, tipos_antigos, &tipo_particula);
	MPI_Type_commit(&tipo_particula);
/* Inicia o vetor de particulas e o envia para cada
processo */
	if (meu_ranque == 0)
	for (i=0; i<NELEM; i++) {
		particulas[i].x = i * 1.0;
		particulas[i].y = i * -1.0;
		particulas[i].z = i * 1.0;
		particulas[i].velocidade = 0.25;
		particulas[i].n = i;
		particulas[i].tipo = i % 2;
	}
	if (meu_ranque == 0)
		MPI_Bcast(particulas, NELEM, tipo_particula, raiz, MPI_COMM_WORLD);
	else
		MPI_Bcast(p, NELEM, tipo_particula, raiz, MPI_COMM_WORLD);
	if (meu_ranque != 0) {
/* Imprime uma amostra do que foi recebido */
		printf("ranque= %d %3.2f %3.2f %3.2f %3.2f %d %d\n", meu_ranque, p[3].x,p[3].y,p[3].z,p[3].velocidade,p[3].n,p[3].tipo);
 }
/* Libera os tipos criados e termina a execução */
	MPI_Type_free(&tipo_particula);
	MPI_Finalize();
	return 0;
}
