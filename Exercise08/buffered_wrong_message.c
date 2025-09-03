#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data = 100;

    // Step 1: Create and attach a buffer for Bsend
    int bufsize;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &bufsize);
    bufsize += MPI_BSEND_OVERHEAD;
    void *buffer = malloc(bufsize);
    MPI_Buffer_attach(buffer, bufsize);

    if (rank == 0) {
        printf("Rank 0 sending buffered message to rank 2\n");
        MPI_Bsend(&data, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        printf("Rank 0 finished Bsend\n");
    } else if (rank == 1) {
        printf("Rank 1 is idle, not receiving anything\n");
    } else if (rank == 2) {
        int recv_data;
        MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 2 received data = %d\n", recv_data);
    }

    // Step 2: Detach and free buffer
    MPI_Buffer_detach(&buffer, &bufsize);
    free(buffer);

    MPI_Finalize();
    return 0;
}
