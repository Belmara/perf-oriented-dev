### Usage:

1) navigate to parent folder of build folder, from there:
2) run generate_jobscripts <num_of_repetitions>
> CAREFUL!  
> cuz i am lazy, program arguments get hardcoded in generate_jobscript  
> that means: if arguments are not always the same, add if cases to 'generate_job_script' function
3) run sbatch_jobscripts
4) move output log files to folder 'outputlogs'
5) run accumulate_benchmarks <program_name> (programe name will be appended to name of csv files)