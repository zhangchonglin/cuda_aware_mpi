#!/bin/bash
#SBATCH -A m499_g
#SBATCH -C gpu
#SBATCH -q regular
#SBATCH -t 0:30:00
#SBATCH -n 4
#SBATCH --ntasks-per-node=4
#SBATCH -c 32
#SBATCH --gpus-per-task=1
#SBATCH --gpu-bind=single:2
#SBATCH --job-name=cuda_aware_mpi

module load PrgEnv-gnu
module load cudatoolkit/11.5
module load cpe-cuda
module load craype-accel-nvidia80
export SLURM_CPU_BIND="cores"
export MPICH_GPU_SUPPORT_ENABLED=1

srun --ntasks=4 --ntasks-per-node=4 -G 4 --gpu-bind=single:2 cuda_aware_mpi
