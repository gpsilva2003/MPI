#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>
#define BLOCO 500000  // Bloco de trabalho, deve ser par

int primo (long int n) { 
        for (long int i = 3; i < (sqrtl(n) + 1); i += 2)
                if(n%i == 0) return 0;
        return 1;
}

int main(int argc, char *argv[]) {  /* mpi_primos2.c  */
        double t_inicial, t_final;
        int cont = 0, total = 0;
        long int inicio, n;
        int meu_ranque, num_procs, salto;

        if (argc < 2) {
                printf("Valor inválido! Entre com um valor do maior inteiro\n");
                return 0;
        } else
                n = strtol(argv[1], (char **) NULL, 10);

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
        MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
        t_inicial = MPI_Wtime();
        inicio = 3 + BLOCO*meu_ranque;
        salto = BLOCO*num_procs;

        for (long int i = inicio; i <= n; i += salto)
            for (long int j = i; (j < i+BLOCO) &&  (j < n); j+=2)
                if(primo(j) == 1) cont++;

        if(num_procs > 1)
                MPI_Reduce(&cont, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        else
                total = cont;

        t_final = MPI_Wtime();
        if (meu_ranque == 0) {
                total += 1;    /* Acrescenta o dois, que também é primo */
                printf("Quant. de primos entre 1 e n: %d Meu total: %d \n", total, cont);
                printf("Tempo de execucao: %1.3f \n", t_final - t_inicial);
        }

        MPI_Finalize();
        return(0);
}
