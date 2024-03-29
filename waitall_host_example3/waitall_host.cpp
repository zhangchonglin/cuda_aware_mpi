#include "waitall_host.hpp"

int wait_host() {

    int myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    // sender and receiver
    int sender = (myrank - 1) % comm_size;
    if ( sender <0) sender += comm_size;
    int receiver = (myrank + 1) % comm_size;

    // create memory
    float *val_send_host, *val_recv_host;
    val_send_host = (float*)malloc(sizeof(float));
    val_recv_host = (float*)malloc(sizeof(float));

    // value to send: rank
    *val_send_host = float(myrank);
    *val_recv_host = 0.0;
    printf("I am rank %d and send to rank %d with value %g: \n",
           myrank, receiver, *val_send_host);

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

    return 0;
}

