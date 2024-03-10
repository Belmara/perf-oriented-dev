# Sheet 1

## Metrics locally
| program | parameters | wall clock time | CPU time | system time | max memory usage |
|--|--|--|--|--|--|
| filegen | 15 15 1024000 1048576 | 02.32s | 02.24s | 0.07s | 2100kB |
| filesearch | / (previously generated files) | 00.01s | 0.00s | 0.01s | 1280kB |
| mmul | / | 0.56s | 0.56s | 0.00 | 24320kB |
| nbody | / | 0.35s | 0.34s | 0.00s | 1536kB |
| qap | problems/chr15a.dat | 01.24s | 01.24s | 0.00s | 1260kB |
| delannoy | 14 | 0.23s | 0.23s | 0.00s | 1024kB |


## Metrics on LCC3
| program | parameters | wall clock time | CPU time | system time | max memory usage |
|--|--|--|--|--|--|
| filegen | 15 15 1024000 1048576 | 06.27s | 03.08s | 0.22s | 2516kB |
| filesearch | / (previously generated files) | 0.01s| 0.00s | 0.01s | 1556kB |
| mmul | / | 1.99s | 1.98s | 0.00 | 24656kB |
| nbody | / | 2.55s | 2.54s | 0.00s | 1804kB |

| qap | problems/chr15a.dat | 01.24s | 01.24s | 0.00s | 1260kB |

| delannoy | 12 | 0.63 | 0.62 | 0.00s | 1300 |



## mean and variance for 10 repetitions locally (script output)
delannoy:
Mean: {'wall_clock_time:': 0.16333333333333333, 'CPU_time:': 0.16333333333333333, 'system_time:': 0.0, 'max_memory_usage:': 1024.0}
Variance: {'wall_clock_time:': 0.000433333333333333, 'CPU_time:': 0.000433333333333333, 'system_time:': 0.0, 'max_memory_usage:': 0.0}


filegen:
Mean: {'wall_clock_time:': 2.3933333333333335, 'CPU_time:': 2.34, 'system_time:': 0.04666666666666667, 'max_memory_usage:': 2101.3333333333335}
Variance: {'wall_clock_time:': 0.005633333333333324, 'CPU_time:': 0.0061000000000000195, 'system_time:': 0.00013333333333333329, 'max_memory_usage:': 77541.33333333333}


filesearch:
Mean: {'wall_clock_time:': 0.0, 'CPU_time:': 0.0, 'system_time:': 0.0, 'max_memory_usage:': 1280.0}
Variance: {'wall_clock_time:': 0.0, 'CPU_time:': 0.0, 'system_time:': 0.0, 'max_memory_usage:': 0.0}


mmul:
Mean: {'wall_clock_time:': 0.5666666666666667, 'CPU_time:': 0.5566666666666666, 'system_time:': 0.0, 'max_memory_usage:': 24486.666666666668}
Variance: {'wall_clock_time:': 0.005033333333333334, 'CPU_time:': 0.005033333333333334, 'system_time:': 0.0, 'max_memory_usage:': 72069.33333333333}


nbody:
Mean: {'wall_clock_time:': 0.37333333333333335, 'CPU_time:': 0.37, 'system_time:': 0.0, 'max_memory_usage:': 1536.0}
Variance: {'wall_clock_time:': 0.000833333333333333, 'CPU_time:': 0.0006999999999999996, 'system_time:': 0.0, 'max_memory_usage:': 0.0}


qap:
Mean: {'signal': 11.0, 'wall_clock_time:': 0.12333333333333334, 'CPU_time:': 0.0, 'system_time:': 0.0, 'max_memory_usage:': 1194.6666666666667}
Variance: {'signal': 0.0, 'wall_clock_time:': 0.0009333333333333333, 'CPU_time:': 0.0, 'system_time:': 0.0, 'max_memory_usage:': 21845.333333333332}



## mean and variance for 10 repetitions LCC3 (script output)

delannoy:
Mean: {'wall_clock_time:': 0.166, 'CPU_time:': 0.165, 'system_time:': 0.0, 'max_memory_usage:': 1075.2}
Variance: {'wall_clock_time:': 0.0007822222222222222, 'CPU_time:': 0.0008277777777777778, 'system_time:': 0.0, 'max_memory_usage:': 11650.844444444445}


filegen:
Mean: {'wall_clock_time:': 2.404, 'CPU_time:': 2.323, 'system_time:': 0.07100000000000001, 'max_memory_usage:': 2181.6}
Variance: {'wall_clock_time:': 0.016271111111111132, 'CPU_time:': 0.013867777777777786, 'system_time:': 0.0014322222222222223, 'max_memory_usage:': 9753.6}


filesearch:
Mean: {'wall_clock_time:': 0.0, 'CPU_time:': 0.0, 'system_time:': 0.0, 'max_memory_usage:': 1280.0}
Variance: {'wall_clock_time:': 0.0, 'CPU_time:': 0.0, 'system_time:': 0.0, 'max_memory_usage:': 0.0}


mmul:
Mean: {'wall_clock_time:': 0.57, 'CPU_time:': 0.5619999999999999, 'system_time:': 0.0, 'max_memory_usage:': 24494.8}
Variance: {'wall_clock_time:': 0.0015333333333333323, 'CPU_time:': 0.0015066666666666657, 'system_time:': 0.0, 'max_memory_usage:': 19882.844444444443}


nbody:
Mean: {'wall_clock_time:': 0.34500000000000003, 'CPU_time:': 0.34400000000000003, 'system_time:': 0.0, 'max_memory_usage:': 1484.8}
Variance: {'wall_clock_time:': 0.004294444444444444, 'CPU_time:': 0.004448888888888888, 'system_time:': 0.0, 'max_memory_usage:': 11650.844444444445}


qap:
Mean: {'signal': 11.0, 'wall_clock_time:': 0.137, 'CPU_time:': 0.0, 'system_time:': 0.0, 'max_memory_usage:': 1177.6}
Variance: {'signal': 0.0, 'wall_clock_time:': 0.000178888888888889, 'CPU_time:': 0.0, 'system_time:': 0.0, 'max_memory_usage:': 17476.266666666666}

## mean and variance for 10 repetitions on lcc3




## Architecture:
![lstopo](image.png)
![btop](image-1.png)