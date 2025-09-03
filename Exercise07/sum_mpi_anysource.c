#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long N = 10000000;
    long long chunk = N / size;
    long long start = rank * chunk + 1;
    long long end = (rank == size - 1) ? N : (rank + 1) * chunk;

    long long local_sum = 0;
    for (long long i = start; i <= end; i++)
        local_sum += i;

    long long total_sum = 0;
    MPI_Status status;

    if (rank == 0) {
        total_sum += local_sum;
        long long temp;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&temp, 1, MPI_LONG_LONG_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            printf("Received sum %lld from rank %d\n", temp, status.MPI_SOURCE);
            total_sum += temp;
        }
        printf("Total Sum = %lld\n", total_sum);
    } else {
        MPI_Send(&local_sum, 1, MPI_LONG_LONG_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

