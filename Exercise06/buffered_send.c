#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    int x[10], y[10];
    int bufsize;

    // Create a buffer for Bsend
    MPI_Pack_size(10, MPI_INT, MPI_COMM_WORLD, &bufsize);
    bufsize += MPI_BSEND_OVERHEAD;
    void *buffer = malloc(bufsize);
    MPI_Buffer_attach(buffer, bufsize);

    if (rank == 0) {
        for (int i = 0; i < 10; i++) x[i] = i * 10;
        printf("Process 0 sending buffered message to process 1\n");
        MPI_Bsend(x, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent message\n");
    } else if (rank == 1) {
        MPI_Recv(y, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process 1 received: ");
        for (int i = 0; i < 10; i++)
            printf("%d ", y[i]);
        printf("\n");
    }

    MPI_Buffer_detach(&buffer, &bufsize);
    free(buffer);

    MPI_Finalize();
    return 0;
}
