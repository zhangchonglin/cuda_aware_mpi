#!/bin/bash
#BSUB -P PHY122
#BSUB -W 0:10
#BSUB -nnodes 1
#BSUB -J waitall_test
#BSUB -o waitall.%J
#BSUB -e waitall.%J

module load cuda/10.2.89

date

jsrun -n 6 -a 1 -c 1 -g 1 --smpiargs "-gpu" \
./waitall_device

date

