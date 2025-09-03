#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long N = 10000000;
    long long local_sum = 0;
    long long chunk = N / size;
    long long start = rank * chunk + 1;
    long long end = (rank + 1) * chunk;

    double t1 = MPI_Wtime();

    for (long long i = start; i <= end; i++)
        local_sum += i;

    long long total_sum;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double t2 = MPI_Wtime();

    if (rank == 0) {
        printf("Sum = %lld\n", total_sum);
        printf("Time taken = %f seconds\n", t2 - t1);
    }

    MPI_Finalize();
    return 0;
}

