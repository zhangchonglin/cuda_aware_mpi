module load PrgEnv-gnu
module load cudatoolkit/11.5
module load cpe-cuda
module load craype-accel-nvidia80
module unload craype-network-ofi
module load craype-network-ucx
module unload cray-mpich
module load cray-mpich-ucx/8.1.12

CC -g cuda_aware_mpi.cpp -o cuda_aware_mpi
