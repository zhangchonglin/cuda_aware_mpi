#!/bin/bash
#SBATCH -A m499_g
#SBATCH -C gpu
#SBATCH -q regular
#SBATCH -t 0:30:00
#SBATCH -n 4
#SBATCH --ntasks-per-node=4
#SBATCH -c 32
#SBATCH --gpus-per-task=1
#SBATCH --gpu-bind=single:1
#SBATCH --job-name=waitall_test

module load PrgEnv-gnu
module load cudatoolkit/11.5
module load cpe-cuda
export SLURM_CPU_BIND="cores"

srun waitall_test_host
