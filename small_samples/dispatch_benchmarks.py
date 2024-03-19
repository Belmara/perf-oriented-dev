import subprocess
import statistics
import json
import yaml
import argparse
import os


def generate_job_script(program_name, config, with_load):
    if not os.path.isfile(f'{program_name}.sh'):
        with open(f'./jobscripts/{program_name}.sh', 'w') as job:
            if(with_load):
                job.write(
                f'''#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name benchmarks-am
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

killall loadgen &> /dev/null
./loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
./loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
./loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
./loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
./loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
./loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
#time -p nice -n 100 $1
nice -n 1000 python3 ./run_benchmark.py {config} {program_name} 
killall loadgen &> /dev/null
                '''
            )
            else:
                job.write(
                    f'''#!/bin/bash

                        # Execute job in the partition "lva" unless you have special requirements.1
                        #SBATCH --partition=lva
                        # Name your job to be able to identify it later
                        #SBATCH --job-name test
                        # Redirect output stream to this file
                        #SBATCH --output=output.log
                        # Maximum number of tasks (=processes) to start in total
                        #SBATCH --ntasks=1
                        # Maximum number of tasks (=processes) to start per node
                        #SBATCH --ntasks-per-node=1
                        # Enforce exclusive node allocation, do not share with other jobs
                        #SBATCH --exclusive
                        python3 ./run_benchmark.py {config} {program_name} 
                    '''
                )
    return



def main():
    parser = argparse.ArgumentParser(description='Run benchmarks for programs specified in config')
    parser.add_argument('config', type=str, help='Yaml config file for to be benchmarked programs')
    args = parser.parse_args()
    config = args.config

    with open(config, 'r') as fc:
        benchmark_config = yaml.safe_load(fc)

    if(benchmark_config['confidence'] not in [0.99, 0.95, 0.9]):
        print('Invalid confidence: choose 0.99, 0.95 or 0.9')
        return

    programs = benchmark_config['programs']
    print(programs)
    # program -> should then be the object from yaml config file
    for program in programs:
        print(program)
        executable_location = './build'
        program_name = program
        executable_path = f'{executable_location}/{program_name}'
        arguments = programs[program]['arguments']
        execution_command =  f'{executable_path} {arguments}'
        
        #check if file exists
        if not os.path.isfile(executable_path):
                print(f"Error: File '{executable_path}' not found.")
                return
        
        mode = benchmark_config['mode']
        if  (mode != "local" and mode != "lcc3"):
                print('Invalid execution mode! Choose "lcc3" or "local" ')
        if(mode == "lcc3"):
            generate_job_script(program_name, config, benchmark_config["load"])


        run_command = f'python3 ./run_benchmark.py {config} {program}' if mode == 'local' else f'sbatch ./jobscripts/{program_name}.sh'
        res = subprocess.run(run_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        print(res)

if __name__ == "__main__":
    main()
