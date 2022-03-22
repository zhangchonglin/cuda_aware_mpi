module load PrgEnv-gnu
module load cudatoolkit/11.5
module load cpe-cuda

CC -g waitall_test_host.cpp -o waitall_test_host
