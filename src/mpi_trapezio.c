#include <stdio.h>
#include <math.h>
#include "mpi.h"

double f(double x) {
        double return_val;
        return_val = exp(x); /* Função exponencial */
        return return_val;
}

int main(int argc, char *argv[]) { /* mpi_trapezio.c  */
int meu_ranque, num_procs;  /* respectivamente q e p */
double a = 0.0,  b = 1.0;   /* Limites da integral */
double tempo_inicial, tempo_final; /* Tempo de execução */
long int n = 500000000;     /* Número de trapezoides */
double x, h;                /* x e h, a base do trapezoide */
double integral=0.0, total; /* Integral de cada processo e total */
int origem, destino = 0;    /* Origem e destino das mensagens */
int etiq = 3;               /* Uma etiqueta qualquer */

    /* Inicia o MPI e determina o ranque e o número de processos ativos  */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* h é o mesmo para todos os processos */
    h = (b - a)/n;   
    /* O processo 0 calcula o valor de f(x)/2 em a e b */
    tempo_inicial = MPI_Wtime(); 
    if (meu_ranque == 0) {
        integral = (f(a) + f(b))/2.0;
    }
    /* Cada processo calcula a integral aprox. sobre n/num_procs trapézios */ 
    for (x = a+h*(meu_ranque+1); x < b ; x += num_procs*h) {
         integral += f(x);
    }
    integral = integral*h;
    /* O processo 0 soma as integrais parciais recebidas */
    if (meu_ranque == 0) { 
        total = integral; 
        for (origem = 1; origem < num_procs; origem++) { 
             MPI_Recv(&integral, 1, MPI_DOUBLE, origem, etiq, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             total += integral; 
        }
    } 
     /* Os demais processos enviam as integrais parciais para o processo 0 */
    else {
        tempo_final = MPI_Wtime();
        MPI_Send(&integral, 1, MPI_DOUBLE, destino, etiq, MPI_COMM_WORLD);
    }
    /* Imprime o resultado */
    if (meu_ranque == 0) {
        tempo_final = MPI_Wtime();
        printf("Foram gastos %3.5f segundos\n",tempo_final-tempo_inicial);
        printf("Com n = %ld trapezoides, a estimativa\n", n);
        printf("da integral de %lf até %lf = %lf \n", a, b, total);
    }
    MPI_Finalize();
    return(0);
} 
