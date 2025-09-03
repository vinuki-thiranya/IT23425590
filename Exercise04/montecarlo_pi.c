#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long num_points = 10000000; // 10 million
    long long points_per_process = num_points / size;

    unsigned int seed = (unsigned int)(time(NULL) + rank); // unique seed per process
    long long local_count = 0;

    for (long long i = 0; i < points_per_process; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (x*x + y*y <= 1.0)
            local_count++;
    }

    long long global_count = 0;
    MPI_Reduce(&local_count, &global_count, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi = 4.0 * (double)global_count / (double)num_points;
        printf("Estimated Pi = %f\n", pi);
    }

    MPI_Finalize();
    return 0;
}
