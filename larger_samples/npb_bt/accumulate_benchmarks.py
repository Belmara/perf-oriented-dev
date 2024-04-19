import re
import os
import csv
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
    matches = re.match(filename_pattern, filename)
    if(matches):
        parsed_comps = matches.groups()
    else:
        print(f"Warning: invalid filename {filename}")

    
    measurements = extract_last_measurements(f'outputlogs/{filename}')
    sorted_measurements = list(zip(*sorted(measurements.items())))[1]
    line =  parsed_comps + sorted_measurements

    return line



def main():
    
    output = []
    
    for filename in os.listdir('outputlogs'):
        file = os.path.join('outputlogs', filename)
        if(not os.path.isfile(file)):
            continue
        else:
            res build(filename)
            output.append(res)
            

    with open('accumulated_output', mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(output)


if __name__ == "__main__":
    main()