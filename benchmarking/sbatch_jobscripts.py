import subprocess
import os

def main():
    for filename in os.listdir('jobscripts'):
        file = os.path.join('jobscripts', filename)
        if(not os.path.isfile(file)):
            continue
        else:
            command = f'sbatch {file}'
            output = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
            print(output)


    
if __name__ == "__main__":
    main()
