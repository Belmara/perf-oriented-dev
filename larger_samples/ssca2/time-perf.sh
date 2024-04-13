#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name perf-timed-ssca
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive


events=$(perf list hwcache | grep -v -e "^$" -e "^List of pre-defined events" -e "^$" -e "^cpu_atom" -e "^cpu_core" | awk '{print $1}' | paste -sd "," -)
time perf stat -e $events ./build/ssca2 17