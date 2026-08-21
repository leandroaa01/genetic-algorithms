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
# 2026-08-19 14:24:36 -03: Reading parameter file '/home/malva/Documentos/half/grafos/genetic-algorithms/irace/parameters-60-v3.txt'.
# 2026-08-19 14:24:36 -03: Initialization
# Elitist race
# Elitist new instances: 1
# Elitist limit: 2
# nbIterations: 4
# minNbSurvival: 4
# nbParameters: 7
# seed: 1843017872
# confidence level: 0.95
# budget: 8000
# mu: 12
# deterministic: FALSE

# 2026-08-19 14:24:36 -03: Iteration 1 of 4
# experimentsUsed: 0
# remainingBudget: 8000
# currentBudget: 2000
# nbConfigurations: 133
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
|x|          1|        133|          3|    -225.0000000|        133|00:01:11|   NA|  NA|    NA|
|x|          2|        133|          4|    -225.0000000|        266|00:01:11|+0.13|0.57|0.8578|
|x|          3|        133|         37|    -225.0000000|        399|00:01:12|+0.05|0.36|0.9469|
|x|          4|        133|         50|    -225.0000000|        532|00:01:11|+0.04|0.28|0.9470|
|x|          5|        133|         50|    -225.0000000|        665|00:01:12|+0.04|0.23|0.9558|
|x|          6|        133|        111|    -225.0000000|        798|00:01:11|+0.04|0.20|0.9517|
|x|          7|        133|        111|    -225.0000000|        931|00:01:11|+0.04|0.18|0.9522|
|x|          8|        133|        111|    -223.7500000|       1064|00:01:11|+0.03|0.15|0.9613|
|x|          9|        133|         17|    -223.8888889|       1197|00:01:11|+0.03|0.14|0.9627|
|x|         10|        133|         17|    -224.0000000|       1330|00:01:11|+0.02|0.12|0.9706|
|x|         11|        133|         17|    -224.0909091|       1463|00:01:11|+0.01|0.10|0.9788|
|=|         12|        133|         17|    -224.1666667|       1596|00:01:11|+0.01|0.10|0.9780|
|x|         13|        133|         17|    -224.2307692|       1729|00:01:11|+0.02|0.09|0.9746|
|x|         14|        133|         17|    -224.2857143|       1862|00:01:11|+0.02|0.09|0.9686|
|-|         15|         37|         17|    -224.3333333|       1995|00:01:11|-0.03|0.04|1.0044|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          17    mean value:     -224.3333333
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
17   17        128        1784       92     1         6   0.9886          15       NA

# 2026-08-19 14:42:28 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
    population generations children breed selection mutation immigration
17         128        1784       92     1         6   0.9886          15
32         136        1803       95     1         5   0.9998          15
99         123        1848       95     1         4   0.9831          13
123        142        1669       99     3         7   0.9888          14
# 2026-08-19 14:42:28 -03: Iteration 2 of 4
# experimentsUsed: 1995
# remainingBudget: 6005
# currentBudget: 2001
# nbConfigurations: 114
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
|x|         16|        114|         17|    -225.0000000|        114|00:01:03|   NA|  NA|    NA|
|x|         14|        114|         17|    -225.0000000|        224|00:01:00|-0.10|0.45|1.1316|
|x|         15|        114|         17|    -225.0000000|        334|00:01:00|+0.06|0.37|0.9581|
|x|          1|        114|         17|    -225.0000000|        444|00:01:00|+0.03|0.28|0.9785|
|x|         13|        114|         17|    -225.0000000|        554|00:01:01|+0.01|0.20|0.9949|
|x|          3|        114|        154|    -225.0000000|        664|00:01:01|+0.01|0.18|0.9826|
|x|         10|        114|        205|    -224.2857143|        774|00:01:00|+0.00|0.14|1.0008|
|x|          2|        114|        205|    -224.3750000|        884|00:01:00|+0.00|0.13|0.9963|
|x|          9|        114|         17|    -224.4444444|        994|00:01:00|-0.01|0.10|1.0047|
|x|         12|        114|         17|    -224.5000000|       1104|00:01:01|-0.01|0.09|1.0004|
|x|          5|        114|         17|    -224.5454545|       1214|00:01:00|+0.00|0.09|0.9911|
|=|          6|        114|         17|    -224.5833333|       1324|00:01:00|-0.00|0.08|0.9967|
|x|          4|        114|         17|    -224.6153846|       1434|00:01:00|-0.00|0.07|0.9949|
|x|          7|        114|         17|    -224.6428571|       1544|00:01:01|-0.00|0.07|0.9955|
|=|         11|        114|         17|    -224.6666667|       1654|00:01:00|-0.00|0.06|0.9942|
|x|          8|        114|         17|    -224.3750000|       1764|00:01:00|-0.00|0.06|0.9949|
|x|         17|        114|         17|    -223.8235294|       1878|00:01:03|+0.00|0.06|0.9922|
|=|         18|        114|         32|    -223.6111111|       1992|00:01:03|+0.00|0.06|0.9895|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          32    mean value:     -223.6111111
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
32   32        136        1803       95     1         5   0.9998          15       NA

# 2026-08-19 15:00:52 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
    population generations children breed selection mutation immigration
32         136        1803       95     1         5   0.9998          15
17         128        1784       92     1         6   0.9886          15
99         123        1848       95     1         4   0.9831          13
140        132        1749       95     1         6   0.9998          15
# 2026-08-19 15:00:52 -03: Iteration 3 of 4
# experimentsUsed: 3987
# remainingBudget: 4013
# currentBudget: 2006
# nbConfigurations: 98
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
|x|         19|         98|         17|    -225.0000000|         98|00:00:55|   NA|  NA|    NA|
|x|          4|         98|         17|    -225.0000000|        192|00:00:52|-0.11|0.45|1.0866|
|x|         18|         98|        248|    -225.0000000|        286|00:00:52|-0.05|0.30|1.0303|
|x|          2|         98|        291|    -225.0000000|        380|00:00:52|-0.04|0.22|1.0294|
|x|          5|         98|        305|    -225.0000000|        474|00:00:52|+0.01|0.20|0.9861|
|x|          6|         98|         32|    -224.1666667|        568|00:00:53|-0.02|0.15|1.0110|
|x|         13|         98|         32|    -224.2857143|        662|00:00:52|-0.01|0.14|0.9960|
|x|         15|         98|         32|    -224.3750000|        756|00:00:52|-0.01|0.11|1.0023|
|x|         10|         98|         32|    -224.4444444|        850|00:00:52|-0.01|0.10|1.0035|
|x|         14|         98|         32|    -224.5000000|        944|00:00:52|-0.01|0.09|0.9996|
|x|          9|         98|         32|    -224.5454545|       1038|00:00:52|-0.00|0.09|0.9932|
|=|         17|         98|         32|    -224.5833333|       1132|00:00:53|+0.00|0.09|0.9839|
|x|          1|         98|        307|    -224.2307692|       1226|00:00:52|+0.00|0.08|0.9880|
|x|          8|         98|        307|    -224.2857143|       1320|00:00:53|+0.00|0.07|0.9870|
|=|         12|         98|        307|    -224.3333333|       1414|00:00:52|+0.01|0.07|0.9839|
|x|          7|         98|        307|    -224.3750000|       1508|00:00:52|+0.01|0.07|0.9776|
|x|         16|         98|        307|    -224.1176471|       1602|00:00:52|+0.01|0.07|0.9810|
|=|          3|         98|        307|    -224.1666667|       1696|00:00:52|+0.01|0.07|0.9807|
|x|         11|         98|         17|    -223.6842105|       1790|00:00:53|+0.01|0.06|0.9825|
|x|         20|         98|         17|    -223.7500000|       1888|00:00:55|+0.01|0.06|0.9825|
|=|         21|         98|         17|    -223.8095238|       1986|00:00:54|+0.01|0.06|0.9840|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:          17    mean value:     -223.8095238
Description of the best-so-far configuration:
   .ID. population generations children breed selection mutation immigration .PARENT.
17   17        128        1784       92     1         6   0.9886          15       NA

# 2026-08-19 15:19:29 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
    population generations children breed selection mutation immigration
17         128        1784       92     1         6   0.9886          15
307        144        1820       96     1         5   0.9996          15
32         136        1803       95     1         5   0.9998          15
297        138        1802       94     1         5   0.9964          16
# 2026-08-19 15:19:29 -03: Iteration 4 of 4
# experimentsUsed: 5973
# remainingBudget: 2027
# currentBudget: 2027
# nbConfigurations: 87
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
|x|         22|         87|        307|    -225.0000000|         87|00:00:48|   NA|  NA|    NA|
|x|         19|         87|        307|    -225.0000000|        170|00:00:46|+0.03|0.52|0.9735|
|x|          2|         87|        307|    -225.0000000|        253|00:00:46|+0.07|0.38|0.9506|
|x|          9|         87|        307|    -225.0000000|        336|00:00:47|+0.03|0.27|0.9787|
|x|          3|         87|        307|    -225.0000000|        419|00:00:46|+0.02|0.22|0.9856|
|x|         21|         87|        307|    -225.0000000|        502|00:00:46|+0.04|0.20|0.9663|
|x|          5|         87|        307|    -225.0000000|        585|00:00:46|+0.03|0.17|0.9698|
|x|         16|         87|        307|    -224.3750000|        668|00:00:46|+0.02|0.14|0.9772|
|x|         15|         87|        307|    -224.4444444|        751|00:00:46|+0.02|0.12|0.9802|
|x|         18|         87|        307|    -224.5000000|        834|00:00:46|+0.02|0.12|0.9755|
|x|         20|         87|        307|    -224.5454545|        917|00:00:46|+0.02|0.11|0.9696|
|-|          6|         50|        307|    -224.5833333|       1000|00:00:46|-0.05|0.04|1.0273|
|x|          1|         50|        307|    -224.6153846|       1046|00:00:26|-0.04|0.04|1.0182|
|x|         11|         50|        307|    -223.9285714|       1092|00:00:26|-0.04|0.03|1.0232|
|=|         13|         50|        307|    -224.0000000|       1138|00:00:26|-0.02|0.05|1.0061|
|x|         10|         50|        307|    -224.0625000|       1184|00:00:26|-0.02|0.05|1.0020|
|x|         17|         50|        307|    -224.1176471|       1230|00:00:26|-0.02|0.04|1.0020|
|=|         14|         50|        307|    -223.8888889|       1276|00:00:26|-0.02|0.04|1.0005|
|x|          8|         50|        307|    -223.9473684|       1322|00:00:26|-0.01|0.04|0.9965|
|x|         12|         50|        307|    -224.0000000|       1368|00:00:26|-0.00|0.05|0.9879|
|=|          4|         50|         32|    -223.8095238|       1414|00:00:26|+0.00|0.05|0.9804|
|x|          7|         50|        401|    -224.0909091|       1460|00:00:26|+0.01|0.05|0.9752|
|x|         23|         50|        401|    -224.1304348|       1510|00:00:28|+0.01|0.05|0.9734|
|=|         24|         50|        307|    -223.9583333|       1560|00:00:28|+0.01|0.05|0.9712|
|x|         25|         50|        307|    -224.0000000|       1610|00:00:28|+0.01|0.05|0.9717|
|x|         26|         50|        307|    -223.8461538|       1660|00:00:28|+0.01|0.05|0.9704|
|=|         27|         50|        307|    -223.7037037|       1710|00:00:28|+0.01|0.05|0.9737|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:         307    mean value:     -223.7037037
Description of the best-so-far configuration:
    .ID. population generations children breed selection mutation immigration .PARENT.
307  307        144        1820       96     1         5   0.9996          15       32

# 2026-08-19 15:35:42 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
    population generations children breed selection mutation immigration
307        144        1820       96     1         5   0.9996          15
387        144        1823       96     1         5   0.9996          15
401        143        1803       96     1         5   0.9979          15
351        127        1779       92     1         6   0.9883          15
# 2026-08-19 15:35:42 -03: Iteration 5 of 5
# experimentsUsed: 7683
# remainingBudget: 317
# currentBudget: 317
# nbConfigurations: 14
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
|x|         28|         14|        401|    -225.0000000|         14|00:00:08|   NA|  NA|    NA|
|x|         27|         14|        351|    -225.0000000|         24|00:00:06|-0.23|0.38|1.1995|
|x|          1|         14|        351|    -225.0000000|         34|00:00:06|-0.28|0.15|1.2214|
|x|          7|         14|        351|    -225.0000000|         44|00:00:06|-0.10|0.17|1.0466|
|x|         12|         14|        401|    -224.0000000|         54|00:00:06|-0.12|0.10|1.0337|
|x|         25|         14|        401|    -223.3333333|         64|00:00:06|-0.06|0.12|0.9639|
|x|         23|         14|        401|    -223.5714286|         74|00:00:06|-0.06|0.09|0.9729|
|x|         20|         14|        401|    -223.7500000|         84|00:00:06|+0.01|0.14|0.9060|
|x|          4|         14|        401|    -223.8888889|         94|00:00:06|+0.05|0.15|0.8784|
|x|         18|         14|        401|    -224.0000000|        104|00:00:06|+0.05|0.14|0.8807|
|x|         24|         14|        351|    -224.0909091|        114|00:00:06|+0.05|0.13|0.8781|
|=|         14|         14|        401|    -223.7500000|        124|00:00:06|+0.04|0.12|0.8782|
|x|         10|         14|        307|    -223.4615385|        134|00:00:06|+0.03|0.10|0.8988|
|x|         11|         14|        401|    -223.5714286|        144|00:00:06|+0.02|0.09|0.9051|
|=|         22|         14|        401|    -223.6666667|        154|00:00:06|+0.03|0.09|0.9021|
|x|          6|         14|        401|    -223.7500000|        164|00:00:06|+0.04|0.10|0.8911|
|x|          3|         14|        351|    -223.8235294|        174|00:00:06|+0.05|0.11|0.8838|
|=|          5|         14|        401|    -223.6111111|        184|00:00:06|+0.04|0.09|0.8903|
|x|         17|         14|        401|    -223.6842105|        194|00:00:06|+0.05|0.10|0.8851|
|x|          9|         14|        307|    -223.5000000|        204|00:00:06|+0.05|0.09|0.8817|
|-|         13|         10|        307|    -223.5714286|        214|00:00:06|+0.01|0.06|0.8892|
|x|          8|         10|        307|    -223.6363636|        220|00:00:04|+0.02|0.07|0.8806|
|x|         21|         10|        307|    -223.6956522|        226|00:00:04|+0.03|0.07|0.8763|
|=|         19|         10|        307|    -223.7500000|        232|00:00:04|+0.03|0.07|0.8759|
|x|          2|         10|        307|    -223.8000000|        238|00:00:04|+0.03|0.07|0.8706|
|x|         15|         10|        307|    -223.8461538|        244|00:00:04|+0.04|0.07|0.8669|
|=|         26|         10|        307|    -223.7037037|        250|00:00:04|+0.02|0.06|0.8758|
|x|         16|         10|        307|    -223.5714286|        256|00:00:04|+0.02|0.06|0.8770|
|x|         29|         10|        307|    -223.4482759|        266|00:00:06|+0.01|0.05|0.8858|
|=|         30|         10|        307|    -223.3333333|        276|00:00:06|+0.00|0.04|0.8959|
|x|         31|         10|        351|    -223.5483871|        286|00:00:06|-0.00|0.03|0.9008|
|x|         32|         10|        351|    -223.5937500|        296|00:00:06|-0.00|0.03|0.9010|
|=|         33|         10|        351|    -223.6363636|        306|00:00:06|+0.00|0.03|0.8981|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:         351    mean value:     -223.6363636
Description of the best-so-far configuration:
    .ID. population generations children breed selection mutation immigration .PARENT.
351  351        127        1779       92     1         6   0.9883          15       17

# 2026-08-19 15:39:11 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
    population generations children breed selection mutation immigration
351        127        1779       92     1         6   0.9883          15
307        144        1820       96     1         5   0.9996          15
387        144        1823       96     1         5   0.9996          15
401        143        1803       96     1         5   0.9979          15
# 2026-08-19 15:39:11 -03: Stopped because there is not enough budget left to race more than the minimum (4).
# You may either increase the budget or set 'minNbSurvival' to a lower value.
# Iteration: 6
# nbIterations: 6
# experimentsUsed: 7989
# timeUsed: 0
# remainingBudget: 11
# currentBudget: 11
# number of elites: 4
# nbConfigurations: 4
# Total CPU user time: 17389.3, CPU sys time: 103.78, Wall-clock time: 4475.015
# 2026-08-19 15:39:11 -03: Starting post-selection:
# Configurations selected: 351, 307, 387.
# Pending instances: 0, 0, 0.
# 2026-08-19 15:39:11 -03: seed: 1843017872
# Configurations: 3
# Available experiments: 11
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
|.|         16|          3|        351|    -225.0000000|          0|00:00:00|   NA|  NA|    NA|
|.|         27|          3|        351|    -225.0000000|          0|00:00:00|+1.00|1.00|0.0000|
|.|         31|          3|        351|    -225.0000000|          0|00:00:00|+1.00|1.00|0.0000|
|.|         22|          3|        351|    -225.0000000|          0|00:00:00|+0.67|0.75|0.1667|
|.|         13|          3|        351|    -225.0000000|          0|00:00:00|+0.50|0.60|0.2000|
|.|         10|          3|        351|    -224.1666667|          0|00:00:00|+0.00|0.17|0.4444|
|.|          5|          3|        351|    -223.5714286|          0|00:00:00|-0.13|0.03|0.5397|
|.|          9|          3|        351|    -223.1250000|          0|00:00:00|-0.14|0.00|0.5714|
|.|          8|          3|        351|    -223.3333333|          0|00:00:00|-0.12|0.00|0.5000|
|.|         20|          3|        351|    -223.5000000|          0|00:00:00|-0.11|0.00|0.4444|
|.|         23|          3|        351|    -223.6363636|          0|00:00:00|-0.10|0.00|0.4000|
|.|         33|          3|        351|    -223.7500000|          0|00:00:00|-0.09|0.00|0.3636|
|.|         26|          3|        351|    -223.8461538|          0|00:00:00|-0.07|0.01|0.3846|
|.|         14|          3|        351|    -223.5714286|          0|00:00:00|-0.07|0.01|0.3553|
|.|         17|          3|        351|    -223.6666667|          0|00:00:00|-0.06|0.01|0.3302|
|.|          7|          3|        351|    -223.7500000|          0|00:00:00|-0.06|0.01|0.3083|
|.|         28|          3|        351|    -223.8235294|          0|00:00:00|-0.03|0.03|0.3235|
|.|          6|          3|        351|    -223.8888889|          0|00:00:00|-0.03|0.03|0.3050|
|.|          3|          3|        351|    -223.9473684|          0|00:00:00|-0.03|0.03|0.2885|
|.|          1|          3|        351|    -224.0000000|          0|00:00:00|-0.03|0.03|0.2737|
|.|         11|          3|        351|    -224.0476190|          0|00:00:00|+0.00|0.05|0.2857|
|.|         32|          3|        351|    -224.0909091|          0|00:00:00|+0.03|0.07|0.2944|
|.|         30|          3|        351|    -223.9130435|          0|00:00:00|+0.03|0.07|0.2819|
|.|          4|          3|        351|    -223.9583333|          0|00:00:00|+0.06|0.09|0.2886|
|.|         29|          3|        351|    -224.0000000|          0|00:00:00|+0.08|0.12|0.2933|
|.|         12|          3|        351|    -223.8461538|          0|00:00:00|+0.04|0.07|0.3210|
|.|         21|          3|        351|    -223.8888889|          0|00:00:00|+0.04|0.07|0.3096|
|.|          2|          3|        351|    -223.9285714|          0|00:00:00|+0.03|0.07|0.2989|
|.|         24|          3|        351|    -223.9655172|          0|00:00:00|+0.03|0.07|0.2890|
|.|         19|          3|        351|    -223.8333333|          0|00:00:00|+0.00|0.04|0.3096|
|.|         15|          3|        351|    -223.7096774|          0|00:00:00|-0.01|0.02|0.3269|
|.|         18|          3|        351|    -223.7500000|          0|00:00:00|-0.01|0.02|0.3165|
|.|         25|          3|        351|    -223.6363636|          0|00:00:00|-0.02|0.01|0.3308|
|x|         34|          3|        351|    -223.5294118|          3|00:00:02|-0.03|0.00|0.3428|
|x|         35|          3|        351|    -223.5714286|          6|00:00:02|-0.02|0.01|0.3507|
|=|         36|          3|        351|    -223.3333333|          9|00:00:02|-0.03|0.00|0.3614|
+-+-----------+-----------+-----------+----------------+-----------+--------+-----+----+------+
Best-so-far configuration:         351    mean value:     -223.3333333
Description of the best-so-far configuration:
    .ID. population generations children breed selection mutation immigration .PARENT.
351  351        127        1779       92     1         6   0.9883          15       17

# 2026-08-19 15:39:18 -03: Elite configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
    population generations children breed selection mutation immigration
351        127        1779       92     1         6   0.9883          15
307        144        1820       96     1         5   0.9996          15
387        144        1823       96     1         5   0.9996          15
# Total CPU user time: 17409.24, CPU sys time: 103.894, Wall-clock time: 4481.923
# Best configurations (first number is the configuration ID; listed from best to worst according to the sum of ranks):
    population generations children breed selection mutation immigration
351        127        1779       92     1         6   0.9883          15
307        144        1820       96     1         5   0.9996          15
387        144        1823       96     1         5   0.9996          15
# Best configurations as commandlines (first number is the configuration ID; listed from best to worst according to the sum of ranks):
351 --population 127 --generations 1779 --children 92 --breed 1 --selection 6 --mutation 0.9883 --immigration 15
307 --population 144 --generations 1820 --children 96 --breed 1 --selection 5 --mutation 0.9996 --immigration 15
387 --population 144 --generations 1823 --children 96 --breed 1 --selection 5 --mutation 0.9996 --immigration 15


# Testing of elite configurations: 1 
# Testing iteration configurations: FALSE 
# 2026-08-19 15:39:18 -03: No test instances, skip testing
