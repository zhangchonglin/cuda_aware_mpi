#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <cuda_runtime.h>
#include "waitall_host.hpp"

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    int ierr = wait_host();

    MPI_Finalize();
    return 0;
}

