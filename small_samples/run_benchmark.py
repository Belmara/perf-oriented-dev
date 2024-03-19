import os
import subprocess
import math
import statistics
import argparse
import json
import yaml

def calculate_t_value(confidence, degrees_of_freedom):
    # Critical t-values for different confidence levels

    t_values = {
        0.9: [3.078, 1.886, 1.638, 1.533, 1.476, 1.440, 1.415, 1.397, 1.383, 1.372, 1.363,
              1.356, 1.350, 1.345, 1.341, 1.337, 1.333, 1.330, 1.328, 1.325, 1.323, 1.321,
              1.319, 1.318, 1.316, 1.315, 1.314, 1.313, 1.311, 1.310],
        0.95: [6.314, 2.920, 2.353, 2.132, 2.015, 1.943, 1.895, 1.860, 1.833, 1.812, 1.796,
               1.782, 1.771, 1.761, 1.753, 1.746, 1.740, 1.734, 1.729, 1.725, 1.721, 1.717,
               1.714, 1.711, 1.708, 1.706, 1.703, 1.701, 1.699, 1.697],
        0.99: [31.821, 6.965, 4.541, 3.747, 3.365, 3.143, 2.998, 2.896, 2.821, 2.764, 2.718,
               2.681, 2.650, 2.624, 2.602, 2.583, 2.567, 2.552, 2.539, 2.528, 2.518, 2.508,
               2.500, 2.492, 2.485, 2.479, 2.473, 2.467, 2.462, 2.457]
    }
    if confidence in t_values:
        index = min(degrees_of_freedom, len(t_values[confidence])) - 1
        return t_values[confidence][index]
    else:
        return None


def calculate_confidence_interval(data, confidence):
    n = len(data)
    if n < 2:
        return 0
    mean = statistics.mean(data)
    stdev = statistics.stdev(data)
    dof = n - 1  # degrees of freedom
    t = abs(calculate_t_value(confidence, dof))
    if t is None:
        return None
    margin_of_error = t * stdev / math.sqrt(n)
    return margin_of_error * 2


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

    program_arguments = benchmark_config["programs"][program_name]["arguments"]
    base_command = f'/bin/time -f "wall_clock_time: %e\n CPU_time: %U\n system_time: %S\n max_memory_usage: %M\n" ./build/{program_name} {program_arguments}'
    print(base_command)
    if mode == "lcc3":
        command = f'srun --nodes=1 --ntasks-per-node=1 {base_command}'
    elif mode == "local":
        command = base_command
    else:
        print("invalid execution mode")
            
    
    time_results = []
    for iteration in range(0, benchmark_config['iterations']):
        # run & time the program
        raw_data = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        print(raw_data)

        parsed_result = parse_result(raw_data)
        time_results.append(parsed_result)
        
        # calculate mean & variance for each metric
        metric_names = time_results[0]['time_metrics'].keys() 
        time_metrics = [item['time_metrics'].values() for item in time_results]
        
        print(parsed_result)
        persist_result(parsed_result, program_name, iteration)
        
        # calculate confidence interval
        confidence_intervals = {metric: calculate_confidence_interval(metric, confidence) for metric in zip(*time_metrics)}


        # check if all confidence intervals are within desired range
        if all(interval < confidence for interval in confidence_intervals.values()) and iteration > 0:
            break
            
        
if __name__ == "__main__":
    main()
