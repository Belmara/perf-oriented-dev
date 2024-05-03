import os
import argparse


def generate_job_script(program_name, argument, iterations):
    if not os.path.exists('jobscripts'):
        os.mkdir('jobscripts')
    if "delannoy" in program_name:
        argument = 13

    for i in range(1, iterations + 1):
        with open(f'./jobscripts/{program_name}-{i}.sh', 'w') as job:
                job.write(
                    f'''#!/bin/bash
# Execute job in the partition "lva" unless you have special requirements.1
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name {program_name}-{i}
# Redirect output stream to this file
#SBATCH --output=output-{program_name}-{i}.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive
/bin/time -f "wall_clock_time: %e\\nCPU_time: %U\\nsystem_time: %S\\n" ./build/{program_name} {argument} 
'''
                    )
    return




def main():
    parser = argparse.ArgumentParser(description='Run benchmarks with load')
    parser.add_argument('repetitions', type=int, help='executions / program')
    args = parser.parse_args()
    repetitions = args.repetitions

    for filename in os.listdir('build'):
        file = os.path.join('build', filename)
        if(not os.path.isfile(file) or 'cmake' in filename or 'ninja' in filename or 'CMake' in filename):
            continue
        else:
            generate_job_script(filename, '', repetitions)


if __name__ == "__main__":
    main()
