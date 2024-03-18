import os
import subprocess
import math
import statistics
import argparse
import json
import yaml


def persist_result(result, program_name, iteration):
    # write results into file for accumulate_data.py
    if not os.path.exists('results'):
        os.mkdir('results')
    target_folder = f'results/{program_name}'
    if not os.path.exists(target_folder):
        os.mkdir(target_folder)

    result_file = f'{target_folder}/iteration_{iteration}.json'
    with open(result_file, 'w') as res:
        json.dump(result, res, indent=2)

def parse_result(result):
    print(result)
    metric_output = result.stderr.strip().split('\n')
    program_output = result.stdout.strip().split('\n')

    # parse output to build dictionary
    metric_names = [entry.split(' ')[-2] for entry in metric_output]  # Assuming the second-to-last line contains metric names
    time_metrics = [float(metric.split()[-1]) for metric in metric_output]

    return {
        'time_metrics': dict(zip(metric_names, time_metrics)),
        'program_output': program_output,
    }


def calculate_confidence_interval(data, confidence=0.95):
    n = len(data)
    if n < 2:
        return 0
    stdev = statistics.stdev(data)
    z = statistics.NormalDist().inv_cdf((1 + confidence) / 2)
    margin_of_error = z * stdev / math.sqrt(n)
    return margin_of_error * 2


def main():
    parser = argparse.ArgumentParser(description='Run benchmarks with load')
    parser.add_argument('config', type=str, help='Yaml config file for to be benchmarked programs')
    parser.add_argument('program_name', type=str, help='name of the program to be benchmarked')
    args = parser.parse_args()
    config = args.config
    program_name = args.program_name

    print('running benchmarks for' + program_name)
    with open(config, 'r') as fc:
        benchmark_config = yaml.safe_load(fc)
    mode = benchmark_config['mode']
    confidence = benchmark_config['confidence']

    match mode:
        case 'lcc3':
            command = f'sbatch ./jobscripts/{program_name}.sh'
        case 'local':
            command = f'/bin/time -f "wall_clock_time: %e\n CPU_time: %U\n system_time: %S\n max_memory_usage: %M\n" ./build/{program_name} {benchmark_config["programs"][program_name]["arguments"]}'

    time_results = []
    for iteration in range(0, benchmark_config['iterations']):
        raw_data = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        time_results.append(parse_result(raw_data))

        # run & time the program
        raw_data = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        result = parse_result(raw_data)


        # calculate mean & variance for each metric
        metric_names = time_results[0]['time_metrics'].keys() 
        time_metrics = [item['time_metrics'].values() for item in time_results]
        

        persist_result(result, program_name, iteration)
        
        # calculate confidence interval
        confidence_intervals = {metric: calculate_confidence_interval(metric) for metric in zip(*time_metrics)}


        # check if all confidence intervals are within desired range
        if all(interval < confidence for interval in confidence_intervals.values()) and iteration > 0:
            print('interval reached')
            break
            
        


if __name__ == "__main__":
    main()
