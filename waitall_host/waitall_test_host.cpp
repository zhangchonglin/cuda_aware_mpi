#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <cuda_runtime.h>

int main(int argc, char *argv[]) {
    int myrank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // sender and receiver
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    int sender = myrank;
    int receiver = (myrank + 1) % comm_size;
    float *val_send_host, *val_recv_host;
    val_send_host = (float*)malloc(sizeof(float));
    val_recv_host = (float*)malloc(sizeof(float));

    // value to send: rank
    *val_send_host = float(myrank);
    *val_send_recv = float(myrank);

    // perform send and receive
    MPI_Request requests[2];
    MPI_Isend(val_send_host, 1, MPI_FLOAT, receiver, 0,
              MPI_COMM_WORLD, requests);
    MPI_Irecv(val_recv_host, 1, MPI_FLOAT, sender, 0,
              MPI_COMM_WORLD, requests+1);
    MPI_Waitall(2, requests, MPI_STATUSES_IGNORE);

    // examine the received value
    printf("I am rank %d and received from rank %d with value %g: \n",
           myrank, sender, *val_recv_host);

    free(val_send_host);
    free(val_recv_host);

    MPI_Finalize();
    return 0;
}

