#include <stdio.h>
#include <stdlib.h>
#include "mpi.h" 

void mxv(int n, double* A, double* b, double* c);

int main(int argc, char *argv[]) { /* mpi_mxv.c  */
double *A,*Aloc, *b,*cloc, *c;
/* matriz m x n por um vetor de dimensão n */
int i, j, m, n;                     
int meu_ranque, num_procs, raiz=0;
double inicio, fim;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
   
   if (meu_ranque == 0) {
      printf("Por favor entre com n: \n");
      scanf("%d",&n);
      printf("\n");
    }
   
    m = num_procs;

    MPI_Bcast(&n, 1, MPI_INT, raiz, MPI_COMM_WORLD);

    if (meu_ranque == 0) {
        printf("Valor de m: %d e  n: %d \n", m,n);
        A=(double*) malloc(m*n*sizeof(double));
        c=(double*) malloc(m*sizeof(double));
    }
    Aloc=(double *) malloc(n*sizeof(double));
    b=(double*) malloc(n*sizeof(double));
    cloc=(double*) malloc(sizeof(double));

     if (meu_ranque == 0) {
         printf("Atribuindo valor inicial à matriz A e ao vetor b\n");
         for (j = 0; j < n; j++)
              b[j] = 2.0;
         for (i = 0; i < m; i++)
              for (j = 0; j < n; j++)
                  A[i*n + j] = (double) i;
     }
     inicio = MPI_Wtime();
     /* Difunde o vetor b para todos os processos */
     MPI_Bcast(&b[0], n, MPI_DOUBLE, raiz, MPI_COMM_WORLD);

     /* Distribui as linhas da matriz A entre todos os processos */
     MPI_Scatter(A, n, MPI_DOUBLE, Aloc, n, MPI_DOUBLE, raiz, MPI_COMM_WORLD);
     
     (void) mxv(n, Aloc, b, cloc);

     MPI_Gather(cloc, 1, MPI_DOUBLE, c, 1, MPI_DOUBLE, raiz, MPI_COMM_WORLD);
     fim = MPI_Wtime();

     if (meu_ranque == 0) {
        printf("Tempo total = %e\n", fim-inicio);
        for (i = 0; i < m; i++)
          	printf("c[%d] = %3.1f ", i, c[i]);
        printf("\n");
     	free(c);
     	free(A);
     }
     free(Aloc);
     free(b);
     free(cloc);
     
     MPI_Finalize();
     return(0);
}
void mxv(int n, double* A, double* b, double* c) {
int j;
      c[0] = 0.0;
      for (j = 0; j < n; j++)
           c[0] += A[j]*b[j];
}
