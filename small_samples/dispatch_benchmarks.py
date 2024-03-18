import subprocess
import statistics
import json
import yaml
import argparse
import os

    
def generate_job_script(program_name, execution_command, with_load):
    if not os.path.isfile(f'{program_name}.sh'):
        with open(f'./jobscripts/{program_name}.sh') as job:
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

                    {execution_command}
                '''
            )
    return


# write program and benchmark output into file

def main():
    # parser = argparse.ArgumentParser(description='Run benchmarks for programs specified in config')
    # parser.add_argument('config', type=str, help='Yaml config file for to be benchmarked programs')
    # args = parser.parse_args()
    # config = args.config
    config = 'benchmark_config.yaml'

    with open('benchmark_config.yaml', 'r') as fc:
        benchmark_config = yaml.safe_load(fc)

    print(benchmark_config)   


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
        elif (mode == "lcc3"):
            generate_job_script(program, execution_command)

        run_command = f'python3 ./run_benchmark.py {config} {program}'
        subprocess.run(run_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)


   

if __name__ == "__main__":
    main()
