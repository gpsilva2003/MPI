#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[]) { /* mpi_funcoes.c  */
int meu_ranque, num_procs; 
int versao, subversao,  aux, ret;
double tempo_inicial, tempo_final; 
char maquina[MPI_MAX_PROCESSOR_NAME];
    /* Inicia o MPI. Em caso de erro aborta o programa */
    ret = MPI_Init(&argc, &argv);
    if (ret != MPI_SUCCESS) {
        printf("Erro ao iniciar o programa MPI. Abortando.\n");
        MPI_Abort(MPI_COMM_WORLD, ret);
    }
    tempo_inicial = MPI_Wtime();
    /* Imprime a versão e subversão da biblioteca MPI */
    MPI_Get_version(&versao,&subversao);
    printf("Versão do MPI  = %d Subversão = %d \n", versao, subversao);
    /* Obtém o ranque e número de processos em execução */
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    /* Recebe o nome do computador onde o processo é executado */
    MPI_Get_processor_name(maquina, &aux);
    printf("Número de tarefas = %d Meu ranque = %d Executando em  %s\n", num_procs, meu_ranque, maquina);
    tempo_final = MPI_Wtime();
    printf("Foram gastos %3.6f segundos com precisão de %3.3e segundos\n",tempo_final-tempo_inicial, MPI_Wtick());
    /* Finaliza o MPI */
    MPI_Finalize();
    return(0);
}
