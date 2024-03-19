import os
import json


def table_row(program_name, mean, variance):
    return f"|{program_name} | {mean['wall_clock_time:']} | {variance['wall_clock_time:']} | {mean['CPU_time:']} | {variance['CPU_time:']} | {mean['system_time:']} | {variance['system_time:']} | {mean['max_memory_usage:']} | {variance['max_memory_usage:']}|\n"


def generate_table(data):
    header = '''| Task           | Wall Clock Time |              | CPU Time |              | System Time |              | Max Memory Usage |              |
|----------------|-----------------|--------------|----------|--------------|-------------|--------------|------------------|--------------|
|                | **Mean**        | **Variance** | **Mean** | **Variance** | **Mean**    | **Variance** | **Mean**         | **Variance** |\n'''

    rows = [table_row(program['name'], program['means'], program['variance']) for program in data]
    with open('pretty_tables.txt', 'w') as f:
        f.write(header + ('').join(rows))



def main():
    for filename in os.listdir('./results_local'):
        f = os.path.join('./results_local', filename)
        print(f)
        # checking if it is a file
        if os.path.isfile(f):
            generate_table(json.loads(f))
        


if __name__ == "__main__":
    main()
