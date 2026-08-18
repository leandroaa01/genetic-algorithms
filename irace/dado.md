scenario-60.txt:
parameterFile = "parameters.txt"
trainInstancesDir = "./instances-60"
targetRunner = "./targetRunner-60.sh"
maxExperiments = 500
parallel = 4

parameters.txt:
# Name                Switch           Type    Domain
population    "--population "   i   (20,200)
generations   "--generations "  i   (100,2000)
children      "--children "     i   (10,100)
breed         "--breed "        i   (1,20)
selection     "--selection "    i   (1,20)
mutation      "--mutation "     r   (0.05,1.00)
immigration   "--immigration "  i   (0,20)


bonus, o targetRunner-60.sh:
```bash
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
```
