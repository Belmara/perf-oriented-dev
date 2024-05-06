import re
import os
import csv
import argparse
from collections import defaultdict


def extract_last_measurements(filename):
    expected_keys = ["wall_clock_time", "CPU_time", "system_time"]
    measurements = {}

    with open(filename, "r") as file:
        lines = file.readlines()

    for line in reversed(lines):
        if ":" in line:
            key, value = line.split(":", 1)
            key = key.strip()
            if key in expected_keys:
                measurements[key] = value.strip()
        if len(measurements) == 3:
            break  # Stop after finding the last 3 measurements

    if set(measurements.keys()) != set(expected_keys):
        print("Warning: Some expected measurements are missing.")

    return measurements


def build_csv_line(filename):
    filename_pattern =  r'output-(\w+)-(\w+)-(\d+).log'
    filename_pattern2 =  r'output-(\w+)-(\d+).log'
    matches = re.match(filename_pattern, filename)
    matches2 = re.match(filename_pattern2, filename)
    parsed_comps = []
    if(matches):
        parsed_comps = matches.groups()
    elif(matches2):
        parsed_comps = matches2.groups()
    else:
        print(f"Warning: invalid filename {filename}")

    
    measurements = extract_last_measurements(f'outputlogs/{filename}')

    sorted_measurements = list(list(zip(*sorted(measurements.items())))[1])
    line = list(parsed_comps) + sorted_measurements

    print(line)
    return line




def main():
    parser = argparse.ArgumentParser(description='Run benchmarks with load')
    parser.add_argument('program_name', type=str, help='program name - gets appended to output csv file name')
    args = parser.parse_args()
    name = args.program_name


    output = []
    accumulated_output = defaultdict(list)

    for filename in os.listdir('outputlogs'):
        file = os.path.join('outputlogs', filename)
        if not os.path.isfile(file):
            continue
        else:
            line = build_csv_line(filename)
            output.append(line)
            key = line[0] +'-'+ line[1]
            measurements = [float(val) for val in line[3:]]  # Convert only the last 3 values to floats
            accumulated_output[key].append(measurements)  # use first and second colum (=program name) as key, skip iteration number



    # dump raw data
    with open(f'raw_output-{name}.csv', mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["program", "tile-size", "iteration", "execution_number", "cpu-time", "system-time", "wall-time"])
        
        writer.writerows(output)

    # accumulate per program
    with open(f'accumulated_output-{name}.csv', mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["key", "cpu-time", "system-time", "wall-time"])
        for key, lines in accumulated_output.items():
            aggregated_line = [key] + [sum(measurements) / len(measurements) for measurements in zip(*lines)]
            writer.writerow(aggregated_line)








if __name__ == "__main__":
    main()