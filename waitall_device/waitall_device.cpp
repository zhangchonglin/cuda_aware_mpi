#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <cuda_runtime.h>

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);
    int myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    float *val_host, *val_device;
    val_host = (float*)malloc(sizeof(float));
    cudaMalloc((void **)&val_device, sizeof(float));

    *val_host = -1.0;
    if (myrank != 0) {
      printf("%s %d %s %f\n", "I am rank", myrank, "and my initial value is:", *val_host);
    }

    if (myrank == 0) {
        *val_host = 42.0;
        cudaMemcpy(val_device, val_host, sizeof(float), cudaMemcpyHostToDevice);
        printf("%s %d %s %f\n", "I am rank", myrank, "and will broadcast value:", *val_host);
    }

    MPI_Bcast(val_device, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (myrank != 0) {
      cudaMemcpy(val_host, val_device, sizeof(float), cudaMemcpyDeviceToHost);
      printf("%s %d %s %f\n", "I am rank", myrank, "and received broadcasted value:", *val_host);
    }

    cudaFree(val_device);
    free(val_host);


    // send and receive example
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    // sender and receiver
    int sender = (myrank - 1) % comm_size;
    if ( sender <0) sender += comm_size;
    int receiver = (myrank + 1) % comm_size;

    // create memory
    float *val_send_device, *val_send_host;
    float *val_recv_device, *val_recv_host;
    val_send_host = (float*)malloc(sizeof(float));
    val_recv_host = (float*)malloc(sizeof(float));
    cudaMalloc((void **)&val_send_device, sizeof(float));
    cudaMalloc((void **)&val_recv_device, sizeof(float));

    // value to send: rank
    *val_send_host = float(myrank);
    *val_recv_host = 0.0;
    cudaMemcpy(val_send_device, val_send_host, sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(val_recv_device, val_recv_host, sizeof(float), cudaMemcpyHostToDevice);

    // perform send and receive
    MPI_Request requests[2];
    MPI_Isend(val_send_device, 1, MPI_FLOAT, receiver, 0,
              MPI_COMM_WORLD, requests);
    MPI_Irecv(val_recv_device, 1, MPI_FLOAT, sender, 0,
              MPI_COMM_WORLD, requests+1);
    MPI_Waitall(2, requests, MPI_STATUSES_IGNORE);

    // examine the received value
    cudaMemcpy(val_recv_host, val_recv_device, sizeof(float), cudaMemcpyDeviceToHost);
    printf("I am rank %d and received from rank %d with value %g: \n",
           myrank, sender, *val_recv_host);

    cudaFree(val_send_device);
    cudaFree(val_recv_device);
    free(val_send_host);
    free(val_recv_host);

    MPI_Finalize();
    return 0;
}

