module load PrgEnv-gnu
module load cudatoolkit/11.5
module load cpe-cuda
module load craype-accel-nvidia80

CC -g cuda_aware_mpi.cpp -o cuda_aware_mpi
