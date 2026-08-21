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
# called with: --scenario scenario-60-v3.txt
# 2026-08-20 07:42:04 -03: Reading parameter file '/home/malva/Documentos/half/grafos/genetic-algorithms/irace/parameters-60-v3.txt'.
# 2026-08-20 07:42:04 -03: Initialization
# Elitist race
# Elitist new instances: 1
# Elitist limit: 2
# nbIterations: 4
# minNbSurvival: 4
# nbParameters: 7
# seed: 82676952
# confidence level: 0.95
# budget: 2000
# mu: 12
# deterministic: FALSE

# 2026-08-20 07:42:04 -03: Iteration 1 of 4
# experimentsUsed: 0
# remainingBudget: 2000
# currentBudget: 500
# nbConfigurations: 33
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
|x|          1|         33|         19|    -225.0000000|         33|00:01:31|   NA|  NA|    NA|
|x|          2|         33|         11|    -222.5000000|         66|00:01:33|+0.10|0.55|0.8623|
|x|          3|         33|         11|    -221.6666667|         99|00:01:31|+0.10|0.40|0.8661|
|x|          4|         33|         11|    -221.2500000|        132|00:01:32|+0.02|0.27|0.9325|
|x|          5|         33|         11|    -221.0000000|        165|00:01:32|+0.01|0.21|0.9488|
|x|          6|         33|         11|    -220.8333333|        198|00:01:31|+0.01|0.18|0.9535|
|x|          7|         33|         11|    -220.0000000|        231|00:01:32|+0.05|0.19|0.9224|
|x|          8|         33|         11|    -220.0000000|        264|00:01:32|+0.07|0.18|0.9105|
|x|          9|         33|         21|    -219.4444444|        297|00:01:32|+0.07|0.17|0.9099|
|x|         10|         33|         21|    -219.5000000|        330|00:01:32|+0.08|0.17|0.8983|
|x|         11|         33|         21|    -219.5454545|        363|00:01:32|+0.08|0.17|0.8971|
|-|         12|         14|         21|    -219.1666667|        396|00:01:33|-0.04|0.05|0.9575|
|x|         13|         14|         11|    -219.2307692|        410|00:00:43|-0.03|0.05|0.9515|
|x|         14|         14|         11|    -218.9285714|        424|00:00:42|-0.02|0.05|0.9451|
|=|         15|         14|         11|    -219.0000000|        438|00:00:42|-0.01|0.06|0.9288|
|x|         16|         14|         29|    -218.7500000|        452|00:00:42|+0.01|0.07|0.9181|
|x|         17|         14|         29|    -218.8235294|        466|00:00:42|+0.01|0.07|0.9154|
|=|         18|         14|         29|    -218.8888889|        480|00:00:42|+0.02|0.07|0.9062|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          29    mean value:     -218.8888889
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
29   29        120        1657       93     1         4   0.9908          15       NA

# 2026-08-20 08:04:47 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
29        120        1657       93     1         4   0.9908          15
11        132        1629       96     1         4   0.9864          14
21        141        1827       96     1         2   0.9896          13
16        128        1817      100     1         4   0.9839          16
# 2026-08-20 08:04:47 -03: Iteration 2 of 4
# experimentsUsed: 480
# remainingBudget: 1520
# currentBudget: 506
# nbConfigurations: 27
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
|x|         19|         27|         35|    -225.0000000|         27|00:01:14|   NA|  NA|    NA|
|x|          4|         27|         35|    -225.0000000|         50|00:01:03|+0.04|0.52|0.8507|
|x|         12|         27|         35|    -223.3333333|         73|00:01:03|+0.06|0.38|0.8574|
|x|         11|         27|         35|    -221.2500000|         96|00:01:04|-0.01|0.24|0.9605|
|x|          3|         27|         29|    -220.0000000|        119|00:01:04|-0.09|0.13|1.0411|
|x|         18|         27|         29|    -220.0000000|        142|00:01:04|-0.03|0.14|0.9973|
|x|          9|         27|         29|    -220.0000000|        165|00:01:03|-0.01|0.14|0.9749|
|x|         15|         27|         29|    -220.0000000|        188|00:01:03|+0.03|0.15|0.9463|
|x|          1|         27|         29|    -219.4444444|        211|00:01:03|+0.00|0.12|0.9683|
|x|         14|         27|         29|    -219.5000000|        234|00:01:03|+0.01|0.11|0.9627|
|x|          6|         27|         29|    -219.0909091|        257|00:01:03|+0.00|0.09|0.9707|
|=|          5|         27|         29|    -219.1666667|        280|00:01:04|+0.01|0.09|0.9643|
|x|         16|         27|         29|    -219.2307692|        303|00:01:04|+0.01|0.09|0.9608|
|x|          2|         27|         29|    -218.9285714|        326|00:01:04|+0.01|0.08|0.9635|
|=|         13|         27|         29|    -219.0000000|        349|00:01:04|+0.01|0.08|0.9577|
|x|          7|         27|         29|    -219.0625000|        372|00:01:04|+0.02|0.08|0.9553|
|x|          8|         27|         29|    -218.8235294|        395|00:01:05|+0.01|0.07|0.9608|
|=|         17|         27|         29|    -218.8888889|        418|00:01:04|+0.01|0.06|0.9612|
|x|         10|         27|         29|    -218.9473684|        441|00:01:04|+0.02|0.07|0.9489|
|x|         20|         27|         29|    -219.0000000|        468|00:01:15|+0.03|0.08|0.9406|
|-|         21|         15|         29|    -219.0476190|        495|00:01:15|-0.01|0.03|0.9420|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          29    mean value:     -219.0476190
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
29   29        120        1657       93     1         4   0.9908          15       NA

# 2026-08-20 08:27:46 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
29        120        1657       93     1         4   0.9908          15
16        128        1817      100     1         4   0.9839          16
11        132        1629       96     1         4   0.9864          14
55        128        1664       93     1         2   0.9946          15
# 2026-08-20 08:27:46 -03: Iteration 3 of 4
# experimentsUsed: 975
# remainingBudget: 1025
# currentBudget: 512
# nbConfigurations: 24
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
|x|         22|         24|         16|    -225.0000000|         24|00:01:07|   NA|  NA|    NA|
|x|         11|         24|         58|    -220.0000000|         44|00:00:56|-0.31|0.34|1.2531|
|x|         17|         24|         16|    -220.0000000|         64|00:00:55|-0.07|0.29|1.0122|
|x|          9|         24|         16|    -220.0000000|         84|00:00:55|-0.02|0.24|0.9664|
|x|         15|         24|         16|    -220.0000000|        104|00:00:55|+0.11|0.29|0.8477|
|x|          4|         24|         29|    -219.1666667|        124|00:00:54|+0.13|0.27|0.8342|
|x|         13|         24|         29|    -219.2857143|        144|00:00:54|+0.16|0.28|0.8005|
|x|         16|         24|         29|    -219.3750000|        164|00:00:54|+0.13|0.24|0.8248|
|x|         10|         24|         29|    -219.4444444|        184|00:00:55|+0.14|0.23|0.8208|
|x|          6|         24|         16|    -220.0000000|        204|00:00:54|+0.13|0.22|0.8264|
|x|          3|         24|         16|    -220.4545455|        224|00:00:54|+0.11|0.19|0.8437|
|-|          1|         14|         16|    -220.0000000|        244|00:00:56|-0.02|0.06|0.9364|
|x|         14|         14|         16|    -219.6153846|        254|00:00:30|-0.03|0.05|0.9437|
|x|          8|         14|         16|    -219.2857143|        264|00:00:30|-0.03|0.04|0.9499|
|=|         21|         14|         16|    -219.3333333|        274|00:00:30|-0.03|0.04|0.9483|
|x|         19|         14|         16|    -219.3750000|        284|00:00:30|-0.02|0.05|0.9395|
|x|          7|         14|         29|    -218.8235294|        294|00:00:30|-0.02|0.04|0.9446|
|=|         18|         14|         29|    -218.8888889|        304|00:00:30|-0.01|0.05|0.9337|
|x|          2|         14|         29|    -218.6842105|        314|00:00:30|-0.01|0.05|0.9339|
|x|          5|         14|         29|    -218.7500000|        324|00:00:30|+0.01|0.05|0.9220|
|=|         12|         14|         29|    -218.8095238|        334|00:00:30|+0.01|0.05|0.9211|
|x|         20|         14|         29|    -218.8636364|        344|00:00:30|+0.01|0.06|0.9174|
|x|         23|         14|         29|    -218.9130435|        358|00:00:41|-0.00|0.04|0.9283|
|=|         24|         14|         29|    -218.9583333|        372|00:00:41|-0.00|0.04|0.9315|
|x|         25|         14|         29|    -219.0000000|        386|00:00:41|-0.01|0.03|0.9343|
|x|         26|         14|         29|    -219.0384615|        400|00:00:41|+0.00|0.04|0.9289|
|=|         27|         14|         29|    -218.8888889|        414|00:00:41|+0.00|0.04|0.9269|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          29    mean value:     -218.8888889
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
29   29        120        1657       93     1         4   0.9908          15       NA

# 2026-08-20 08:47:33 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
29        120        1657       93     1         4   0.9908          15
73        128        1634       95     1         5   0.9856          14
11        132        1629       96     1         4   0.9864          14
16        128        1817      100     1         4   0.9839          16
# 2026-08-20 08:47:33 -03: Iteration 4 of 4
# experimentsUsed: 1389
# remainingBudget: 611
# currentBudget: 611
# nbConfigurations: 23
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
|x|         28|         23|         79|    -225.0000000|         23|00:01:01|   NA|  NA|    NA|
|x|         14|         23|         29|    -220.0000000|         42|00:00:51|-0.25|0.37|1.2204|
|x|         20|         23|         29|    -220.0000000|         61|00:00:51|-0.15|0.23|1.0667|
|x|         21|         23|         29|    -220.0000000|         80|00:00:51|-0.05|0.21|1.0139|
|x|          6|         23|         73|    -220.0000000|         99|00:00:51|-0.02|0.18|0.9985|
|x|          3|         23|         16|    -220.0000000|        118|00:00:51|-0.01|0.16|0.9688|
|x|         11|         23|         73|    -219.2857143|        137|00:00:51|-0.02|0.12|0.9781|
|x|         10|         23|         29|    -219.3750000|        156|00:00:51|-0.02|0.10|0.9785|
|x|          4|         23|         29|    -219.4444444|        175|00:00:51|-0.02|0.09|0.9753|
|x|         13|         23|         29|    -219.5000000|        194|00:00:51|-0.01|0.09|0.9631|
|x|          5|         23|         29|    -219.5454545|        213|00:00:51|+0.01|0.10|0.9448|
|=|          7|         23|         29|    -219.5833333|        232|00:00:51|+0.01|0.09|0.9520|
|x|         16|         23|         29|    -219.6153846|        251|00:00:51|+0.01|0.09|0.9526|
|x|         18|         23|         29|    -219.6428571|        270|00:00:51|+0.02|0.09|0.9460|
|=|         24|         23|         29|    -219.6666667|        289|00:00:51|+0.01|0.08|0.9493|
|x|         19|         23|         29|    -219.6875000|        308|00:00:51|+0.01|0.07|0.9491|
|x|         15|         23|         29|    -219.7058824|        327|00:00:51|+0.01|0.07|0.9501|
|=|          8|         23|         29|    -219.4444444|        346|00:00:51|+0.01|0.06|0.9541|
|x|         22|         23|         29|    -219.2105263|        365|00:00:51|+0.01|0.06|0.9516|
|x|         27|         23|         29|    -219.0000000|        384|00:00:51|+0.01|0.06|0.9477|
|=|         23|         23|         29|    -219.0476190|        403|00:00:51|+0.01|0.05|0.9534|
|x|         26|         23|         29|    -219.0909091|        422|00:00:51|+0.01|0.05|0.9499|
|x|         12|         23|         29|    -219.1304348|        441|00:00:52|+0.02|0.06|0.9441|
|=|          1|         23|         29|    -218.9583333|        460|00:00:51|+0.01|0.06|0.9450|
|x|          9|         23|         29|    -219.0000000|        479|00:00:51|+0.02|0.06|0.9429|
|x|          2|         23|         29|    -218.8461538|        498|00:00:51|+0.01|0.05|0.9469|
|=|         17|         23|         29|    -218.8888889|        517|00:00:51|+0.02|0.05|0.9421|
|x|         25|         23|         29|    -218.9285714|        536|00:00:51|+0.02|0.05|0.9439|
|x|         29|         23|         29|    -218.7931034|        559|00:01:01|+0.01|0.05|0.9484|
|=|         30|         23|         29|    -218.8333333|        582|00:01:01|+0.01|0.04|0.9488|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          29    mean value:     -218.8333333
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
29   29        120        1657       93     1         4   0.9908          15       NA

# 2026-08-20 09:13:44 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
29        120        1657       93     1         4   0.9908          15
73        128        1634       95     1         5   0.9856          14
16        128        1817      100     1         4   0.9839          16
92        129        1593       95     1         4   0.9871          15
# 2026-08-20 09:13:44 -03: Stopped because there is not enough budget left to race more than the minimum (4).
# You may either increase the budget or set 'minNbSurvival' to a lower value.
# Iteration: 5
# nbIterations: 5
# experimentsUsed: 1971
# timeUsed: 0
# remainingBudget: 29
# currentBudget: 29
# number of elites: 4
# nbConfigurations: 4
# Total CPU user time: 20491.6, CPU sys time: 46.935, Wall-clock time: 5500.527
# 2026-08-20 09:13:44 -03: Starting post-selection:
# Configurations selected: 29, 73, 16, 92, 11, 77, 78, 79, 80.
# Pending instances: 0, 0, 0, 0, 0, 0, 0, 0, 0.
# 2026-08-20 09:13:45 -03: seed: 82676952
# Configurations: 9
# Available experiments: 29
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
|.|         12|          9|         11|    -220.0000000|          0|00:00:00|   NA|  NA|    NA|
|.|          3|          9|         11|    -220.0000000|          0|00:00:00|+0.39|0.69|0.5375|
|.|         28|          9|         11|    -218.3333333|          0|00:00:00|-0.03|0.31|0.9025|
|.|         21|          9|         11|    -217.5000000|          0|00:00:00|+0.02|0.26|0.8692|
|.|         27|          9|         11|    -219.0000000|          0|00:00:00|+0.05|0.24|0.8530|
|.|         25|          9|         11|    -218.3333333|          0|00:00:00|-0.03|0.14|0.9262|
|.|          9|          9|         11|    -217.8571429|          0|00:00:00|+0.05|0.19|0.8404|
|.|         30|          9|         11|    -217.5000000|          0|00:00:00|+0.09|0.21|0.7998|
|.|         14|          9|         11|    -217.2222222|          0|00:00:00|+0.11|0.21|0.7833|
|.|         15|          9|         11|    -217.5000000|          0|00:00:00|+0.09|0.18|0.8083|
|.|         11|          9|         11|    -217.2727273|          0|00:00:00|+0.05|0.14|0.8443|
|.|          4|          9|         11|    -217.5000000|          0|00:00:00|+0.04|0.12|0.8534|
|.|         17|          9|         11|    -217.6923077|          0|00:00:00|+0.04|0.12|0.8518|
|.|          5|          9|         11|    -217.8571429|          0|00:00:00|+0.06|0.13|0.8380|
|.|         16|          9|         11|    -217.6666667|          0|00:00:00|+0.09|0.15|0.8140|
|.|         22|          9|         11|    -217.8125000|          0|00:00:00|+0.09|0.14|0.8131|
|.|          8|          9|         11|    -217.9411765|          0|00:00:00|+0.05|0.10|0.8426|
|.|          7|          9|         11|    -217.7777778|          0|00:00:00|+0.05|0.10|0.8402|
|.|         13|          9|         11|    -217.8947368|          0|00:00:00|+0.06|0.11|0.8363|
|.|         10|          9|         11|    -218.0000000|          0|00:00:00|+0.07|0.12|0.8261|
|.|         19|          9|         11|    -218.0952381|          0|00:00:00|+0.07|0.12|0.8211|
|.|         23|          9|         11|    -217.9545455|          0|00:00:00|+0.06|0.10|0.8337|
|.|          1|          9|         11|    -218.0434783|          0|00:00:00|+0.05|0.09|0.8451|
|.|         24|          9|         11|    -218.1250000|          0|00:00:00|+0.04|0.08|0.8540|
|.|          2|          9|         11|    -218.4000000|          0|00:00:00|+0.03|0.06|0.8648|
|.|         29|          9|         11|    -218.2692308|          0|00:00:00|+0.01|0.05|0.8739|
|.|         20|          9|         11|    -218.3333333|          0|00:00:00|+0.03|0.06|0.8629|
|.|         26|          9|         11|    -218.2142857|          0|00:00:00|+0.03|0.07|0.8588|
|.|         18|          9|         11|    -218.2758621|          0|00:00:00|+0.04|0.07|0.8551|
|.|          6|          9|         11|    -218.3333333|          0|00:00:00|+0.03|0.06|0.8588|
|x|         31|          9|         29|    -218.8709677|          9|00:00:29|+0.03|0.07|0.8563|
|x|         32|          9|         29|    -218.7500000|         18|00:00:29|+0.03|0.06|0.8603|
|=|         33|          9|         29|    -218.9393939|         27|00:00:29|+0.02|0.05|0.8644|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          29    mean value:     -218.9393939
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
29   29        120        1657       93     1         4   0.9908          15       NA

# 2026-08-20 09:15:12 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
29        120        1657       93     1         4   0.9908          15
16        128        1817      100     1         4   0.9839          16
73        128        1634       95     1         5   0.9856          14
11        132        1629       96     1         4   0.9864          14
# Total CPU user time: 20764.63, CPU sys time: 47.563, Wall-clock time: 5588.456
# Best configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
   population generations children breed selection mutation immigration
29        120        1657       93     1         4   0.9908          15
16        128        1817      100     1         4   0.9839          16
73        128        1634       95     1         5   0.9856          14
11        132        1629       96     1         4   0.9864          14
# Best configurations as commandlines (first number is the configuration ID; listed from best to worst according to the sum of ranks):
29 --population 120 --generations 1657 --children 93 --breed 1 --selection 4 --mutation 0.9908 --immigration 15
16 --population 128 --generations 1817 --children 100 --breed 1 --selection 4 --mutation 0.9839 --immigration 16
73 --population 128 --generations 1634 --children 95 --breed 1 --selection 5 --mutation 0.9856 --immigration 14
11 --population 132 --generations 1629 --children 96 --breed 1 --selection 4 --mutation 0.9864 --immigration 14


# Testing of elite configurations: 1 
# Testing iteration configurations: FALSE 
# 2026-08-20 09:15:12 -03: No test instances, skip testing
