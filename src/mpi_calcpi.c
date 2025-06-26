#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int meu_ranque, num_procs;
    long long i, n = 10000000000; // número total de intervalos
    double h, x, local_sum = 0.0, pi = 0.0;
    double inicio, fim;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    inicio = MPI_Wtime();

    h = 1.0 / (double)n;

    for (i = 0; i < n; i += num_procs) {
        x = h * (i + 0.5);
        local_sum += 4.0 / (1.0 + x * x);
    }

    local_sum *= h;
    MPI_Reduce(&local_sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (meu_ranque == 0) {
        fim = MPI_Wtime();
        printf("Aproximação de pi: %.15f Tempo de execução: %f \n", pi, fim-inicio);
    }

    MPI_Finalize();
    return 0;
}
