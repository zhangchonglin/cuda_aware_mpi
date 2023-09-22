module load cuda11.8/toolkit/11.8.0
module load cmake/3.21.3
module load mpich/ge/gcc/64/3.3.2

mpicxx -g -c waitall_host.cpp
mpicxx -g waitall_host.o main.cpp -o waitall_host
