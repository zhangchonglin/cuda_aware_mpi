module load gcc/7.5.0
module load cuda/10.2.89

mpiCC -g waitall_device.cpp -L/$CUDA_DIR/lib64 -lcudart -o waitall_device
