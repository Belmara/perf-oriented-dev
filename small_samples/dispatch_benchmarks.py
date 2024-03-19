import subprocess
import statistics
import json
import yaml
import argparse
import os


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

        run_command = f'python3 ./run_benchmark.py {config} {program}'
        subprocess.run(run_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        

if __name__ == "__main__":
    main()
