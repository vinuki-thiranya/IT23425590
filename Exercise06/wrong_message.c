#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data = 100;

    if (rank == 0) {
        printf("Sending message to rank 2 from rank 0\n");
        MPI_Send(&data, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        printf("Rank 1 is idle, not receiving anything\n");
    } else if (rank == 2) {
        int recv_data;
        MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 2 received data = %d\n", recv_data);
    }

    MPI_Finalize();
    return 0;
}
