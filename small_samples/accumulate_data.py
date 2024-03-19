import subprocess
import statistics
import json
import argparse
import os
import yaml



def parse_measurements():
        metric_names = [entry.split(' ')[-2] for entry in metric_output]  # Assuming the second-to-last line contains metric names
        time_metrics = [float(metric.split()[-1]) for metric in metric_output]

        result_data = {
            'time_metrics': dict(zip(metric_names, time_metrics)),
            'metric_names': metric_names,
        }

        return result_data


def table_row(program_name, mean, variance):
    return f"|{program_name} | {mean['wall_clock_time']} | {variance['wall_clock_time']} | {mean['CPU_time']} | {variance['CPU_time']} | {mean['system_time']} | {variance['system_time']} | {mean['max_memory_usage']} | {variance['max_memory_usage']}|\n"

def get_table(data):
    header = '''| Task           | Wall Clock Time |              | CPU Time |              | System Time |              | Max Memory Usage |              |
|----------------|-----------------|--------------|----------|--------------|-------------|--------------|------------------|--------------|
|                | **Mean**        | **Variance** | **Mean** | **Variance** | **Mean**    | **Variance** | **Mean**         | **Variance** |'''

    rows = [table_row(program['name'], program['means'], program['variance']) for program in data]
    print(rows)



def accumulate_measurements_for_program(program):
    benchmark_results = os.listdir(f'./results/{program}')
    return [parse_measurements(extracted_data) for extracted_data in benchmark_results]
         
def accumulate_repetitions(program):
    directory = f'./results/{program}'
    results = []
    for metric_file in os.listdir(directory):
        f = os.path.join(directory, metric_file)
        # checking if it is a file
        if os.path.isfile(f):
            with open(f, 'r') as measurements:
                results.append(json.load(measurements))
    return(results)
         
def main():
    parser = argparse.ArgumentParser(description='Run benchmarks for programs specified in config')
    parser.add_argument('config', type=str, help='Yaml config file for to be benchmarked programs')
    args = parser.parse_args()
    config = args.config

    with open(config, 'r') as fc:
        benchmark_config = yaml.safe_load(fc)


    programs = benchmark_config['programs']
    results = []
    

    for program in programs:  
        # accumulate measurments from benchmark script
        raw_data = accumulate_repetitions(program)

        # calculate mean & variance for each metric
        metric_names = raw_data[0]['time_metrics'].keys() 
        time_metrics = [item['time_metrics'].values() for item in raw_data]
        mean_metrics = dict(zip(metric_names, [statistics.mean(metric) for metric in zip(*time_metrics)]))
        variance_metrics = dict(zip(metric_names, [statistics.variance(metric) for metric in zip(*time_metrics)]))
       
        # store for logging
        raw_data.append({'means': mean_metrics})
        raw_data.append({'variance': variance_metrics})

        results.append( {'name': program,
                        'iterations:': raw_data,
                        'means': mean_metrics,
                        'variance': variance_metrics})

        # Display mean results for current program
        # print(f'{program}:')
        # print(f"Mean: {mean_metrics}")
        # print(f"Variance: {variance_metrics}")
        # print('\n')

    get_table(results)
    # dump into json log file
    with open('raw_data.json', 'w') as f:
        json.dump(results, f, indent=2)
   

if __name__ == "__main__":
    main()
