module load PrgEnv-gnu
module load cudatoolkit/11.5
module load cpe-cuda

CC -g waitall_host.cpp -o waitall_host
