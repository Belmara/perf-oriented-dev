# Exercise Sheet 2

## Exercise A) External CPU load

Um die Messungen am Lcc3 durchzuführen muss man nur das exec_with_workstation_heavy.sh script laufen lassen. Das wurde so bearbeitet, dass es unser dispatch_benchmarks.py script ausführt, welches alle Messungen jeden Programmes, welche im dazugehörigen YAML file definiert sind auf einer eigenen Node durch.
Außerdem werden dann, im run_benchmark.py file, für jede Iteration ebenfalls eine neue Node verwendet. Falls das Confidenceinterval für alle metriken erreicht wurde, dann werden die Iterationen früher abgebrochen. Die Ergebnisse werden für jedes definierte Programm in ein seperates JSON file geschrieben.

running this code on a virtual machine on windows as host

| Exercise | Parameter | Mean Wall Clock Time | Mean CPU Time | Mean System Time | Mean Max Memory Usage | Variance Wall Clock Time | Variance CPU Time | Variance System Time | Variance Max Memory Usage |
|----------|-----------|----------------------|---------------|------------------|-----------------------|--------------------------|-------------------|----------------------|---------------------------|
| mmul     |           | 0.21| 0.21| 0.0| 1321.2| 4.4444e-05| 4.4444e-05| 0.0| 1959.2889|
| delannoy | 12| 3.353| 2.693| 0.649| 2556.8| 0.0102| 0.139| 0.157| 1467.7333|
| nbody    |   | 0.0| 0.0| 0.0| 1537.6| 0.0| 0.0| 0.0| 5988.2667|
| filegen  | 15 15 1024000 1048576 | 0.795 | 0.78 | 0.008 | 24519.6 | 0.0006056 | 0.0008444 | 4.0000e-05 | 1164.2667 |
| filesearch |  | 0.485| 0.475| 0.005| 1892.0| 5.0000e-05| 5.0000e-05| 5.0000e-05| 0.0|


