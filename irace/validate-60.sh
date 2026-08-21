#!/bin/bash
EXECUTABLE="../bin/Mahl"

for seed in $(seq 1 30); do
  result=$("$EXECUTABLE" --irace --tmax 60 --seed "$seed" \
    --population 127 --generations 1779 --children 92 \
    --breed 1 --selection 6 --mutation 0.9883 --immigration 15)
  echo "seed=$seed $result"
done