module load PrgEnv-gnu
module load cudatoolkit/11.5
module load cpe-cuda

CC -g waitall_host.c -o waitall_host
