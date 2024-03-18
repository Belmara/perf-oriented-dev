import subprocess
import statistics
import json
import yaml
import argparse
import os

    
def generate_job_script(program_name, execution_command):
    if not os.path.isfile(f'./jobscripts/{program_name}.sh'):
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


def run_on_lcc3():
    for job in os.listdir('./jobscripts'):
        subprocess.run(f'sbatch {job}', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
            
def run_locally(execution_command):
    command = f'/bin/time -f "wall_clock_time: %e\n CPU_time: %U\n system_time: %S\n max_memory_usage: %M\n" {execution_command}'
    return subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)

def persist_result(result, program_name, iteration):
    # write results into file for accumulate_data.py
    metric_output = result.stderr.strip().split('\n')
    program_output = result.stdout.strip().split('\n')

    if not os.path.exists('results'):
        os.mkdir('results')

    result_file = f'results/result_{program_name}_{iteration}.json'
    with open(result_file, 'w') as res:
        json.dump({'metrics': metric_output, 'program_output': program_output}, res, indent=2 )
   

def main():
    parser = argparse.ArgumentParser(description='Run benchmarks for programs specified in config')
    parser.add_argument('config', type=str, help='Yaml config file for to be benchmarked programs')
    args = parser.parse_args()
    config = args.config

    with open(config, 'r') as fc:
        benchmark_config = yaml.safe_load(fc)

    print(benchmark_config)   

    
    # print(f'Examining {repetitions} interation(s) per program\n')
    # tba: add option for execution with convergence interval -> maybe with break?

    programs = benchmark_config['programs']
    # program -> should then be the object from yaml config file
    for program in programs:
        iteration = 1
        executable_location = './build'
        program_name = program['name']
        executable_path = f'{executable_location}/{program_name}'
        arguments = program['arguments']
        execution_command =  f'{executable_path} {arguments}'
        #check if file exists
        if not os.path.isfile(executable_path):
                print(f"Error: File '{executable_path}' not found.")
                return
        match benchmark_config['mode']:
            case "local":
                result = run_locally(execution_command)
            case "lcc3":
                generate_job_script(program, execution_command)
                result = run_on_lcc3()
            case _:
                print('Invalid execution mode! Choose "lcc3" or "local" ')

        persist_result(result, program_name, iteration)
   

if __name__ == "__main__":
    main()
