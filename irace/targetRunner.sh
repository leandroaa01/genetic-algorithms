#!/bin/bash

CONFIG_ID=$1
INSTANCE_ID=$2
SEED=$3
INSTANCE_FILE=$4
shift 4
PARAMETERS="$@"

BINARY="../bin/Mahl"

# Definimos o Tmax (pode ser fixo ou extraído dinamicamente se necessário)
TMAX_VAL="60"

# Executa o binário utilizando a estrutura exata de flags exigida pelo seu programa
OUTPUT=$($BINARY --irace --seed "$SEED" $PARAMETERS < "$INSTANCE_FILE")
# Captura a última linha da saída (onde está o score)
SCORE=$(echo "$OUTPUT" | tail -n 1)

# Validação e inversão do score para o irace maximizar
if [[ -z "$SCORE" || ! "$SCORE" =~ ^-?[0-9]+([.,][0-9]+)?$ ]]; then
    SCORE=0
else
    SCORE_CLEAN=$(echo "$SCORE" | tr ',' '.')
    # Multiplica por -1 para que o irace (que minimiza) busque o maior score positivo
    SCORE=$(echo "-1 * $SCORE_CLEAN" | bc)
fi

# Retorna o score processado para o irace
echo "$SCORE"