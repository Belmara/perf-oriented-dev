def main():
    # parser = argparse.ArgumentParser(description='Run benchmarks for programs specified in config')
    # parser.add_argument('config', type=str, help='Yaml config file for to be benchmarked programs')
    # args = parser.parse_args()
    # config = args.config
    config = 'benchmark_config.yaml'

    with open('benchmark_config.yaml', 'r') as fc:
        benchmark_config = yaml.safe_load(fc)

    # program -> should then be the object from yaml config file

  
    res = subprocess.run('sbatch testjob.sh', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    print(res)
    return 'out'

