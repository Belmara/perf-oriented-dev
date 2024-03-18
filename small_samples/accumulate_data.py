import subprocess
import statistics
import json
import argparse
import os



def parse_measurements():
        
        metric_names = [entry.split(' ')[-2] for entry in metric_output]  # Assuming the second-to-last line contains metric names
        time_metrics = [float(metric.split()[-1]) for metric in metric_output]

        result_data = {
            'time_metrics': dict(zip(metric_names, time_metrics)),
            'program_output': program_output,
        }

        return result_data


def accumulate_measurements_for_program(program):
    benchmark_results = os.listdir(f'./results/{program}')
    return [parse_measurements(extracted_data) for extracted_data in benchmark_results]
         
         
def main():
    results = []

    for program in x:  
        # accumulate measurments from benchmark script
        raw_data = accumulate_repetitions(program)

        # calculate mean & variance for each metric
        metric_names = raw_data[0]['time_metrics'].keys() 
        time_metrics = [item['time_metrics'].values() for item in raw_data]
        mean_metrics = dict(zip(metric_names, [statistics.mean(metric) for metric in zip(*time_metrics)]))
        variance_metrics = dict(zip(metric_names, [statistics.variance(metric) if repetitions > 1 else 0 for metric in zip(*time_metrics)]))
       
        # store for logging
        raw_data.append({'means': mean_metrics})
        raw_data.append({'variance': variance_metrics})
        results.append({program_name: raw_data})

        # Display mean results for current program
        print(f'{program}:')
        print(f"Mean: {mean_metrics}")
        print(f"Variance: {variance_metrics}")
        print('\n')


    # dump into json log file
    with open('raw_data.json', 'w') as f:
        json.dump(results, f, indent=2)
   

if __name__ == "__main__":
    main()
