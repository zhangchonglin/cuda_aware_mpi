module load PrgEnv-gnu
module load cudatoolkit/11.5
module load cpe-cuda
module load craype-accel-nvidia80

CC -g waitall_device.cpp -o waitall_device
