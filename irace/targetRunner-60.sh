#!/bin/bash

CONFIG_ID="$1"
INSTANCE_ID="$2"
SEED="$3"
INSTANCE="$4"

shift 4

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
EXECUTABLE="$PROJECT_ROOT/bin/Mahl"

if [[ ! -x "$EXECUTABLE" ]]; then
    echo "Erro: executável não encontrado: $EXECUTABLE" >&2
    exit 1
fi

TMAX=60
N_INTERNAL=5   # quantas seeds internas testar por avaliação

WORST=""

for i in $(seq 0 $((N_INTERNAL - 1))); do
    # deriva uma seed diferente e determinística a partir da seed que o irace deu
    RUN_SEED=$(( (SEED * 97 + i * 131) % 2147483647 ))

    cost=$("$EXECUTABLE" --irace --seed "$RUN_SEED" --tmax "$TMAX" "$@")

    if [[ -z "$WORST" ]]; then
        WORST="$cost"
    else
        # cost é negativo (custo = -score). O PIOR caso é o valor MENOS negativo
        # (score mais baixo), ou seja, o MAIOR valor de cost entre as N execuções.
        WORST=$(awk -v a="$cost" -v b="$WORST" 'BEGIN{print (a>b)?a:b}')
    fi
done

echo "$WORST"