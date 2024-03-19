# Exercise Sheet 2

## Exercise A) External CPU load

Um die Messungen am Lcc3 durchzuführen muss man nur das exec_with_workstation_heavy.sh script laufen lassen. Das wurde so bearbeitet, dass es unser dispatch_benchmarks.py script ausführt, welches alle Messungen jeden Programmes, welche im dazugehörigen YAML file definiert sind auf einer eigenen Node durch.
Falls das Confidenceinterval für alle metriken erreicht wurde, dann werden die Iterationen früher abgebrochen. Die Ergebnisse werden für jedes definierte Programm in ein seperates JSON file geschrieben. Wenn man das script lokal laufen lassen will, dann muss man einfach im YAML file den mode string auf "local" setzen ansonsten "lcc3". Im Yaml File kann man zusätzlich mithilfe von load steuern ob der Loadgenerator laufen soll.

lokal (VM auf windows PC - spezifikation siehe abgabe 1)

| Exercise | Parameter | Mean Wall Clock Time | Mean CPU Time | Mean System Time | Mean Max Memory Usage | Variance Wall Clock Time | Variance CPU Time | Variance System Time | Variance Max Memory Usage |
|---|---|---|---|---|---|---|---|---|---|
| delannoy | 12 | 0.21| 0.21| 0.0| 1321.2| 4.4444e-05| 4.4444e-05| 0.0| 1959.2889|
| filegen | 15 15 1024000 1048576 | 3.353| 2.693| 0.649| 2556.8| 0.0102| 0.139| 0.157| 1467.7333|
| filesearch |   | 0.0| 0.0| 0.0| 1537.6| 0.0| 0.0| 0.0| 5988.2667|
| mmul  |  | 0.795 | 0.78 | 0.008 | 24519.6 | 0.0006056 | 0.0008444 | 4.0000e-05 | 1164.2667 |
| nbody |  | 0.485| 0.475| 0.005| 1892.0| 5.0000e-05| 5.0000e-05| 5.0000e-05| 0.0|

LCC3
|Exercise|Parameter|Mean Wall Clock Time|Mean CPU Time|Mean System Time|Mean Max Memory Usage|Variance Wall Clock Time|Variance CPU Time|Variance System Time|Variance Max Memory Usage|
|---|---|---|---|---|---|---|---|---|---|
|delannoy|12|3.79|0.785|0.0|1379.2|3.0731|0.0096056|0.0|674.8444|
|filegen|15 15 1024000 1048576|26.541|4.127|0.068|2487.2|14.007|0.0558678|0.00004|3615.2889|
|filesearch||0.151|0.0|0.001|1440.0|0.0875656|0.0|0.00001|2709.3333|
|mmul||18.959|3.489|0.005|24584.4|211.2275|6.0161211|0.00005|3806.0444|
|nbody||15.632|2.794|0.0|1850.0|8.5394|0.00076|0.0|6671.1111|
|qap|'./build/problems/chr15a.dat'|25.487|4.538|0.0|1498.8|43.6469|0.1047956|0.0|316.6222|