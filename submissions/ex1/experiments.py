import subprocess
import statistics
import json
import argparse
import os

def run_program(command, repetitions):
    results = []
    for _ in range(repetitions):
       # Execute the command and capture its output
        result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)

        metric_output = result.stderr.strip().split('\n')
        print(metric_output)
        program_output = result.stdout.strip().split('\n')

        # Extract relevant metrics from the output
        metric_names = [entry.split(' ')[-2] for entry in metric_output]  # Assuming the second-to-last line contains metric names
        time_metrics = [float(metric.split()[-1]) for metric in metric_output]

        result_data = {
            'time_metrics': dict(zip(metric_names, time_metrics)),
            'program_output': program_output,
        }
        results.append(result_data)

    return results
    
    
def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description='Run program with time measurement and collect metrics.')
    parser.add_argument('repetitions', type=int, help='Number of repetitions')
    args = parser.parse_args()

    # could be changeed to list of triple to configure different repetitions for each program
    programs = {'delannoy': '12',
                'filegen': '15 15 1024000 1048576',
                'filesearch': '',
                'mmul': '',
                'nbody': '',
                'qap': 'problems/chr15a.dat',
    }
    

    repetitions = args.repetitions


    results = []
    for program in programs:
        program_name = '../../small_samples/build/' + program
        # use underscores instead of spaces to make extracting measurement name easier
        command = f'/bin/time -f "wall_clock_time: %e\n CPU_time: %U\n system_time: %S\n max_memory_usage: %M\n" {program_name} {programs[program]}'
        #check if file exists
        if not os.path.isfile(program_name):
                print(f"Error: File '{program_name}' not found.")
                return
        
        # run & time the program
        raw_data = run_program(command, repetitions)

        # calculate mean & variance for each metric
        metric_names = raw_data[0]['time_metrics'].keys()
        time_metrics = [item['time_metrics'].values() for item in raw_data]
        mean_metrics = dict(zip(metric_names, [statistics.mean(metric) for metric in zip(*time_metrics)]))
        variance_metrics = dict(zip(metric_names, [statistics.variance(metric) for metric in zip(*time_metrics)]))
        
        # store for log file
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
