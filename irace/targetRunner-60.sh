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

"$EXECUTABLE" \
    --irace \
    --seed "$SEED" \
    --tmax "$TMAX" \
    "$@"