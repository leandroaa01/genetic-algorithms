# 2026-08-14 15:32:10 -03: Reading parameter file '/home/malva/Documentos/half/grafos/genetic-algorithms/irace/parameters.txt'.
# 2026-08-14 15:32:11 -03: Initialization
# Elitist race
# Elitist new instances: 1
# Elitist limit: 2
# nbIterations: 4
# minNbSurvival: 4
# nbParameters: 7
# seed: 1411529036
# confidence level: 0.95
# budget: 500
# mu: 5
# deterministic: FALSE

# 2026-08-14 15:32:11 -03: Iteration 1 of 4
# experimentsUsed: 0
# remainingBudget: 500
# currentBudget: 125
# nbConfigurations: 20
# Markers:
     x No test is performed.
     c Configurations are discarded only due to capping.
     - The test is performed and some configurations are discarded.
     = The test is performed but no configuration is discarded.
     ! The test is performed and configurations could be discarded but elite configurations are preserved.
     . Alive configurations were already evaluated on this instance and nothing is discarded.
     : All alive configurations are elite, but some need to be evaluated on this instance.

+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
| |   Instance|      Alive|       Best|       Mean best| Exp so far|  W time|  rho|KenW|  Qvar|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
#------------------------------------------------------------------------------
# irace: An implementation in R of (Elitist) Iterated Racing
# Version: 4.4.3.dd8d85f
# Copyright (C) 2010-2025
# Manuel Lopez-Ibanez     <manuel.lopez-ibanez@manchester.ac.uk>
# Jeremie Dubois-Lacoste
# Leslie Perez Caceres    <leslie.perez.caceres@ulb.ac.be>
#
# This is free software, and you are welcome to redistribute it under certain
# conditions.  See the GNU General Public License for details. There is NO
# WARRANTY; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# irace builds upon previous code from the race package:
#     race: Racing methods for the selection of the best
#     Copyright (C) 2003 Mauro Birattari
#------------------------------------------------------------------------------
# installed at: /home/malva/R/x86_64-pc-linux-gnu-library/4.6/irace
# called with: --scenario scenario-60.txt
# 2026-08-18 08:32:00 -03: Reading parameter file '/home/malva/Documentos/half/grafos/genetic-algorithms/irace/parameters.txt'.
# 2026-08-18 08:32:00 -03: Initialization
# Elitist race
# Elitist new instances: 1
# Elitist limit: 2
# nbIterations: 4
# minNbSurvival: 4
# nbParameters: 7
# seed: 477191525
# confidence level: 0.95
# budget: 500
# mu: 5
# deterministic: FALSE

# 2026-08-18 08:32:00 -03: Iteration 1 of 4
# experimentsUsed: 0
# remainingBudget: 500
# currentBudget: 125
# nbConfigurations: 20
# Markers:
     x No test is performed.
     c Configurations are discarded only due to capping.
     - The test is performed and some configurations are discarded.
     = The test is performed but no configuration is discarded.
     ! The test is performed and configurations could be discarded but elite configurations are preserved.
     . Alive configurations were already evaluated on this instance and nothing is discarded.
     : All alive configurations are elite, but some need to be evaluated on this instance.

+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
| |   Instance|      Alive|       Best|       Mean best| Exp so far|  W time|  rho|KenW|  Qvar|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
|x|          1|         20|         17|    -225.0000000|         20|00:00:02|   NA|  NA|    NA|
|x|          2|         20|         10|    -220.0000000|         40|00:00:02|+0.57|0.78|0.5146|
|x|          3|         20|          5|    -220.0000000|         60|00:00:02|+0.51|0.67|0.5158|
|x|          4|         20|          5|    -220.0000000|         80|00:00:02|+0.57|0.68|0.4522|
|-|          5|          6|          5|    -220.0000000|        100|00:00:02|+0.01|0.21|0.8143|
|=|          6|          6|          5|    -220.0000000|        106|00:00:01|+0.05|0.21|0.7752|
|=|          7|          6|          5|    -219.2857143|        112|00:00:01|+0.10|0.23|0.7482|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:           5    mean value:     -219.2857143
Description of the best-so-far configuration:
  .ID. population generations children breed selection mutation immigration .PARENT.
5    5         96        1202       71     2         6    0.707          12       NA

# 2026-08-18 08:32:16 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
5          96        1202       71     2         6   0.7070          12
17        181        1261       80    10         5   0.9742           6
12         85        1558       43    10        17   0.8851          18
10         40         133       66    15        12   0.6476           2
# 2026-08-18 08:32:16 -03: Iteration 2 of 4
# experimentsUsed: 112
# remainingBudget: 388
# currentBudget: 129
# nbConfigurations: 19
# Markers:
     x No test is performed.
     c Configurations are discarded only due to capping.
     - The test is performed and some configurations are discarded.
     = The test is performed but no configuration is discarded.
     ! The test is performed and configurations could be discarded but elite configurations are preserved.
     . Alive configurations were already evaluated on this instance and nothing is discarded.
     : All alive configurations are elite, but some need to be evaluated on this instance.

+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
| |   Instance|      Alive|       Best|       Mean best| Exp so far|  W time|  rho|KenW|  Qvar|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
|x|          8|         19|         27|    -225.0000000|         19|00:00:03|   NA|  NA|    NA|
|x|          6|         19|         27|    -222.5000000|         34|00:00:02|+0.27|0.64|0.5223|
|x|          7|         19|         27|    -221.6666667|         49|00:00:02|+0.43|0.62|0.3782|
|x|          2|         19|          5|    -220.0000000|         64|00:00:02|+0.30|0.48|0.5370|
|-|          3|         11|          5|    -220.0000000|         79|00:00:02|-0.05|0.16|0.9248|
|=|          5|         11|          5|    -220.0000000|         86|00:00:01|+0.04|0.20|0.8492|
|=|          1|         11|         27|    -220.0000000|         93|00:00:01|+0.03|0.17|0.8668|
|=|          4|         11|         27|    -220.0000000|        100|00:00:01|+0.03|0.15|0.8744|
|=|          9|         11|         27|    -220.5555556|        111|00:00:02|+0.05|0.16|0.8476|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          27    mean value:     -220.5555556
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
27   27        124        1770       88     4         2   0.8743          13        5

# 2026-08-18 08:32:36 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
27        124        1770       88     4         2   0.8743          13
26        197        1151       96     8         8   0.8941          10
5          96        1202       71     2         6   0.7070          12
17        181        1261       80    10         5   0.9742           6
# 2026-08-18 08:32:36 -03: Iteration 3 of 4
# experimentsUsed: 223
# remainingBudget: 277
# currentBudget: 138
# nbConfigurations: 17
# Markers:
     x No test is performed.
     c Configurations are discarded only due to capping.
     - The test is performed and some configurations are discarded.
     = The test is performed but no configuration is discarded.
     ! The test is performed and configurations could be discarded but elite configurations are preserved.
     . Alive configurations were already evaluated on this instance and nothing is discarded.
     : All alive configurations are elite, but some need to be evaluated on this instance.

+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
| |   Instance|      Alive|       Best|       Mean best| Exp so far|  W time|  rho|KenW|  Qvar|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
|x|         10|         17|         48|    -225.0000000|         17|00:00:05|   NA|  NA|    NA|
|x|          4|         17|         43|    -222.5000000|         30|00:00:03|+0.03|0.52|0.9307|
|x|          3|         17|         41|    -221.6666667|         43|00:00:03|+0.10|0.40|0.8468|
|x|          8|         17|         41|    -222.5000000|         56|00:00:03|+0.17|0.37|0.7908|
|=|          5|         17|         41|    -221.0000000|         69|00:00:03|+0.16|0.33|0.7812|
|-|          1|         12|         41|    -221.6666667|         82|00:00:03|-0.10|0.08|1.0143|
|=|          7|         12|         41|    -222.1428571|         90|00:00:03|-0.03|0.12|0.9421|
|=|          2|         12|         41|    -222.5000000|         98|00:00:03|-0.02|0.10|0.9328|
|=|          6|         12|         41|    -222.2222222|        106|00:00:03|-0.02|0.09|0.9325|
|=|          9|         12|         41|    -222.0000000|        114|00:00:03|+0.00|0.10|0.9086|
|=|         11|         12|         41|    -221.8181818|        126|00:00:04|+0.00|0.09|0.9111|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          41    mean value:     -221.8181818
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
41   41        144        1865       98     1         6   0.8245          12       27

# 2026-08-18 08:33:17 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
41        144        1865       98     1         6   0.8245          12
26        197        1151       96     8         8   0.8941          10
27        124        1770       88     4         2   0.8743          13
40        198        1500       93    13         5   0.9260           6
# 2026-08-18 08:33:17 -03: Iteration 4 of 4
# experimentsUsed: 349
# remainingBudget: 151
# currentBudget: 151
# nbConfigurations: 16
# Markers:
     x No test is performed.
     c Configurations are discarded only due to capping.
     - The test is performed and some configurations are discarded.
     = The test is performed but no configuration is discarded.
     ! The test is performed and configurations could be discarded but elite configurations are preserved.
     . Alive configurations were already evaluated on this instance and nothing is discarded.
     : All alive configurations are elite, but some need to be evaluated on this instance.

+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
| |   Instance|      Alive|       Best|       Mean best| Exp so far|  W time|  rho|KenW|  Qvar|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
|x|         12|         16|         27|    -225.0000000|         16|00:00:06|   NA|  NA|    NA|
|x|         11|         16|         60|    -222.5000000|         28|00:00:04|+0.00|0.50|1.0192|
|x|          6|         16|         59|    -220.0000000|         40|00:00:04|+0.06|0.37|0.8879|
|x|          4|         16|         59|    -221.2500000|         52|00:00:04|+0.02|0.27|0.9204|
|=|          1|         16|         59|    -221.0000000|         64|00:00:04|+0.10|0.28|0.8518|
|=|          7|         16|         59|    -220.8333333|         76|00:00:04|+0.12|0.27|0.8285|
|-|          9|         11|         41|    -220.7142857|         88|00:00:04|-0.01|0.13|0.9226|
|=|          5|         11|         27|    -221.2500000|         95|00:00:02|+0.00|0.13|0.8978|
|=|          3|         11|         41|    -220.5555556|        102|00:00:02|+0.00|0.11|0.8995|
|=|          2|         11|         41|    -221.0000000|        109|00:00:02|+0.00|0.10|0.8996|
|=|         10|         11|         41|    -220.9090909|        116|00:00:02|+0.01|0.10|0.8990|
|=|          8|         11|         41|    -221.2500000|        123|00:00:02|+0.01|0.10|0.8949|
|=|         13|         11|         41|    -221.1538462|        134|00:00:04|+0.01|0.08|0.9028|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          41    mean value:     -221.1538462
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
41   41        144        1865       98     1         6   0.8245          12       27

# 2026-08-18 08:34:10 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
41        144        1865       98     1         6   0.8245          12
27        124        1770       88     4         2   0.8743          13
53        137        1982       75     3         2   0.6829          15
40        198        1500       93    13         5   0.9260           6
# 2026-08-18 08:34:10 -03: Iteration 5 of 5
# experimentsUsed: 483
# remainingBudget: 17
# currentBudget: 17
# nbConfigurations: 5
# Markers:
     x No test is performed.
     c Configurations are discarded only due to capping.
     - The test is performed and some configurations are discarded.
     = The test is performed but no configuration is discarded.
     ! The test is performed and configurations could be discarded but elite configurations are preserved.
     . Alive configurations were already evaluated on this instance and nothing is discarded.
     : All alive configurations are elite, but some need to be evaluated on this instance.

+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
| |   Instance|      Alive|       Best|       Mean best| Exp so far|  W time|  rho|KenW|  Qvar|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
|x|         10|          5|         53|    -225.0000000|          1|00:00:01|   NA|  NA|    NA|
|x|          8|          5|         53|    -225.0000000|          2|00:00:01|+0.38|0.69|0.5000|
|x|          4|          5|         41|    -221.6666667|          3|00:00:01|+0.24|0.50|0.6184|
|x|          1|          5|         41|    -222.5000000|          4|00:00:01|+0.32|0.49|0.5408|
|=|          2|          5|         41|    -223.0000000|          5|00:00:01|+0.14|0.31|0.6961|
|=|         11|          5|         41|    -222.5000000|          6|00:00:01|+0.12|0.27|0.7019|
|=|         13|          5|         41|    -222.1428571|          7|00:00:01|+0.09|0.22|0.7345|
|=|         12|          5|         41|    -221.2500000|          8|00:00:01|+0.10|0.21|0.7259|
|=|          7|          5|         41|    -221.6666667|          9|00:00:01|+0.15|0.24|0.6879|
|-|          9|          4|         41|    -221.5000000|         10|00:00:01|-0.04|0.07|0.7014|
|.|          3|          4|         41|    -221.8181818|         10|00:00:00|-0.01|0.09|0.6879|
|.|          5|          4|         41|    -221.2500000|         10|00:00:00|-0.03|0.06|0.7075|
|.|          6|          4|         41|    -221.1538462|         10|00:00:00|-0.01|0.07|0.6968|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          41    mean value:     -221.1538462
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
41   41        144        1865       98     1         6   0.8245          12       27

# 2026-08-18 08:34:23 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
41        144        1865       98     1         6   0.8245          12
27        124        1770       88     4         2   0.8743          13
53        137        1982       75     3         2   0.6829          15
40        198        1500       93    13         5   0.9260           6
# 2026-08-18 08:34:23 -03: Stopped because there is not enough budget left to race more than the minimum (4).
# You may either increase the budget or set 'minNbSurvival' to a lower value.
# Iteration: 6
# nbIterations: 6
# experimentsUsed: 493
# timeUsed: 0
# remainingBudget: 7
# currentBudget: 7
# number of elites: 4
# nbConfigurations: 4
# Total CPU user time: 459.111, CPU sys time: 6.57, Wall-clock time: 143
# 2026-08-18 08:34:23 -03: Starting post-selection:
# Configurations selected: 41, 27, 53, 40, 26, 49, 52.
# Pending instances: 0, 0, 0, 0, 0, 0, 0.
# 2026-08-18 08:34:23 -03: seed: 477191525
# Configurations: 7
# Available experiments: 7
# minSurvival: 1
# Markers:
     x No test is performed.
     c Configurations are discarded only due to capping.
     - The test is performed and some configurations are discarded.
     = The test is performed but no configuration is discarded.
     ! The test is performed and configurations could be discarded but elite configurations are preserved.
     . Alive configurations were already evaluated on this instance and nothing is discarded.
     : All alive configurations are elite, but some need to be evaluated on this instance.

+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
| |   Instance|      Alive|       Best|       Mean best| Exp so far|  W time|  rho|KenW|  Qvar|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
|.|          8|          7|         27|    -225.0000000|          0|00:00:00|   NA|  NA|    NA|
|.|         11|          7|         27|    -220.0000000|          0|00:00:00|-0.66|0.17|1.4150|
|.|          6|          7|         27|    -220.0000000|          0|00:00:00|-0.14|0.24|0.9746|
|.|          4|          7|         27|    -220.0000000|          0|00:00:00|-0.08|0.19|0.9211|
|.|          5|          7|         27|    -221.0000000|          0|00:00:00|-0.02|0.19|0.8608|
|.|          3|          7|         27|    -220.0000000|          0|00:00:00|+0.07|0.23|0.7902|
|.|         10|          7|         27|    -219.2857143|          0|00:00:00|+0.10|0.23|0.7755|
|.|         12|          7|         27|    -220.0000000|          0|00:00:00|+0.07|0.18|0.7976|
|.|          2|          7|         27|    -219.4444444|          0|00:00:00|+0.03|0.14|0.8324|
|.|          7|          7|         27|    -219.5000000|          0|00:00:00|+0.03|0.13|0.8273|
|.|         13|          7|         27|    -220.0000000|          0|00:00:00|+0.02|0.11|0.8340|
|.|          1|          7|         27|    -220.0000000|          0|00:00:00|+0.05|0.12|0.8184|
|.|          9|          7|         27|    -220.3846154|          0|00:00:00|+0.06|0.14|0.8020|
|-|         14|          5|         41|    -221.0714286|          7|00:00:03|-0.02|0.05|0.8114|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          41    mean value:     -221.0714286
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
41   41        144        1865       98     1         6   0.8245          12       27

# 2026-08-18 08:34:26 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
41        144        1865       98     1         6   0.8245          12
27        124        1770       88     4         2   0.8743          13
53        137        1982       75     3         2   0.6829          15
26        197        1151       96     8         8   0.8941          10
# Total CPU user time: 469.778, CPU sys time: 6.668, Wall-clock time: 146.075
# Best configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
41        144        1865       98     1         6   0.8245          12
27        124        1770       88     4         2   0.8743          13
53        137        1982       75     3         2   0.6829          15
26        197        1151       96     8         8   0.8941          10
# Best configurations as commandlines (first number is the configuration ID; listed from best to worst according to the sum of ranks):
41 --population 144 --generations 1865 --children 98 --breed 1 --selection 6 --mutation 0.8245 --immigration 12
27 --population 124 --generations 1770 --children 88 --breed 4 --selection 2 --mutation 0.8743 --immigration 13
53 --population 137 --generations 1982 --children 75 --breed 3 --selection 2 --mutation 0.6829 --immigration 15
26 --population 197 --generations 1151 --children 96 --breed 8 --selection 8 --mutation 0.8941 --immigration 10


# Testing of elite configurations: 1 
# Testing iteration configurations: FALSE 
# 2026-08-18 08:34:26 -03: No test instances, skip testing
