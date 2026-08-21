# Contexto completo do projeto

Estou desenvolvendo, em C++, um Algoritmo Genético/Memético para o **Orienteering Problem (OP)** e quero usar o **irace** para configurar automaticamente os hiperparâmetros do meu algoritmo.

Quero que você continue o trabalho a partir do estado atual do projeto, sem reinventar a arquitetura e sem voltar para etapas que já foram concluídas.

## 1. Objetivo principal

Meu objetivo experimental é:

> **Usar o irace para encontrar, para cada valor de `Tmax`, uma configuração de hiperparâmetros do meu GA que maximize o score do Orienteering Problem e superar os resultados apresentados no artigo "A Genetic Algorithm for the Orienteering Problem".**

Não quero simplesmente encontrar uma configuração global que seja boa em média para todos os `Tmax`.

Quero fazer **tuning específico por `Tmax`**, por exemplo:

```text
Tmax = 60
→ melhor configuração para Tmax=60

Tmax = 70
→ melhor configuração para Tmax=70

Tmax = 80
→ melhor configuração para Tmax=80
```

e assim sucessivamente.

## 2. Resultado original do meu GA

O GA original usa:

```cpp
size_t populationSize{ 50 };
size_t generations{ 600 };
double Tmax{ 85.0 };
size_t childrenGoal{ 50 };
size_t breedQnt{ 6 };
size_t popSelQnt{ 10 };
size_t immigration{ 0 };
double mutationRate{ 0.40 };
```

Para os experimentos, eu uso diferentes valores de `Tmax`.

Resultados obtidos sem irace:

```text
Tmax = 5
Score Máximo: 10
Score Mínimo: 10
Score Médio: 10

Tmax = 10
Score Máximo: 15
Score Mínimo: 15
Score Médio: 15

Tmax = 20
Score Máximo: 65
Score Mínimo: 65
Score Médio: 65

Tmax = 30
Score Máximo: 110
Score Mínimo: 110
Score Médio: 110

Tmax = 40
Score Máximo: 155
Score Mínimo: 150
Score Médio: 150.75

Tmax = 50
Score Máximo: 190
Score Mínimo: 170
Score Médio: 186

Tmax = 60
Score Máximo: 220
Score Mínimo: 205
Score Médio: 212.75

Tmax = 70
Score Máximo: 260
Score Mínimo: 230
Score Médio: 250.25

Tmax = 80
Score Máximo: 280
Score Mínimo: 275
Score Médio: 279.50

Tmax = 85
Score Máximo: 285
Score Mínimo: 280
Score Médio: 284.50
```

Para `Tmax=60`, o melhor score observado pelo GA original foi:

```text
220
```

e isso é particularmente importante porque o resultado de referência do artigo para `Tmax=60` é:

```text
225
```

Portanto, `Tmax=60` virou o primeiro caso de estudo para o irace.

## 3. Importante sobre a comparação com o artigo

O objetivo não é comparar velocidade absoluta com o artigo, pois o hardware/época são diferentes.

Quero comparar principalmente:

```text
mesmo problema
mesmo Tmax
maior score
```

A meta é:

```text
score do meu GA + irace > score de referência do artigo
```

Também quero, na validação final, apresentar:

```text
melhor score
pior score
score médio
desvio padrão
tempo médio
número de execuções que atingiram a referência
```

## 4. Estrutura do projeto

O projeto está aproximadamente assim:

```text
genetic-algorithms/
├── CMakeLists.txt
├── README.md
├── bin/
│   └── Mahl
├── build/
├── data/
├── docs/
├── includes/
│   └── population.hpp
├── src/
│   ├── main.cpp
│   └── population.cpp
└── irace/
    ├── instances/
    ├── instances-60/
    ├── parameters.txt
    ├── parameters-60-v1.txt
    ├── scenario-60.txt
    ├── targetRunner.sh
    ├── targetRunner-60.sh
    └── ...
```

## 5. Ambiente

Estou usando:

```text
Ubuntu 24.04
```

O irace foi instalado com sucesso via R/CRAN.

A versão instalada é:

```text
irace 4.4.3.dd8d85f
```

O comando executável `irace` não ficou disponível diretamente no PATH, então estou executando pela interface:

```bash
Rscript -e 'library(irace); irace_cmdline(...)'
```

Isso funciona corretamente.

## 6. Seed e reprodutibilidade

Foi implementado suporte a seed.

Em `RunningOptions` existe:

```cpp
unsigned seed{ 0 };
bool irace{ false };
```

O RNG está centralizado em:

```cpp
namespace pop {
namespace detail {

inline std::mt19937& tls_gen()
{
  thread_local std::mt19937 g{ std::random_device{}() };
  return g;
}

inline std::uniform_real_distribution<double>& tls_real01()
{
  thread_local std::uniform_real_distribution<double> d(0.0, 1.0);
  return d;
}

}
}
```

No `main.cpp`, a seed é aplicada com:

```cpp
if (options.seed != 0) {
    detail::tls_gen().seed(options.seed);
}
```

O parâmetro `--seed` foi adicionado.

Também foi adicionado o modo:

```bash
--irace
```

## 7. Problema encontrado e corrigido no RNG

Inicialmente, mesmo usando:

```bash
./bin/Mahl --irace --tmax 60 --seed 12345
```

o mesmo comando não produzia o mesmo resultado.

Descobrimos que `generate_individual()` usava:

```cpp
std::async(std::launch::async, ...)
```

para executar em paralelo:

```cpp
genNearestInsertion
genNearestNeighbor
generate
```

Como o RNG era `thread_local`, cada thread recebia um gerador diferente inicializado pelo `random_device`.

Isso quebrava a reprodutibilidade.

A solução adotada foi remover o `std::async` dessa função e executar as três heurísticas sequencialmente usando o mesmo `detail::tls_gen()`.

A função passou a ser essencialmente:

```cpp
void Population::generate_individual(const size_t city_qnt,
                                      const RunningOptions& options)
{
  if (options.allHeuristic) {
    Individual ind1 = genNearestInsertion(city_qnt);
    Individual ind2 = genNearestNeighbor(city_qnt);
    Individual ind3 = generate(city_qnt);

    const double fitness1 = ind1.fitness;
    const double fitness2 = ind2.fitness;
    const double fitness3 = ind3.fitness;

    if (fitness1 >= fitness2 && fitness1 >= fitness3) {
      population.push_back(std::move(ind1));
    } else if (fitness2 >= fitness1 && fitness2 >= fitness3) {
      population.push_back(std::move(ind2));
    } else {
      population.push_back(std::move(ind3));
    }

  } else if (options.useGenNearestInsertion) {
    population.push_back(genNearestInsertion(city_qnt));

  } else if (options.useGenNearestNeighbor) {
    population.push_back(genNearestNeighbor(city_qnt));

  } else {
    population.push_back(generate(city_qnt));
  }
}
```

Depois disso, o teste:

```bash
./bin/Mahl --irace --tmax 60 --seed 12345
```

executado quatro vezes retornou:

```text
-210.000000
-210.000000
-210.000000
-210.000000
```

Isso confirmou reprodutibilidade.

Também foram testadas seeds diferentes:

```text
seed 1 → -220
seed 2 → -210
seed 3 → -210
seed 4 → -215
seed 5 → -210
```

Portanto:

```text
mesma seed → mesmo resultado
seed diferente → pode gerar resultado diferente
```

## 8. Modo `--irace`

No modo normal:

```bash
./bin/Mahl ...
```

o GA executa 20 vezes.

No modo:

```bash
./bin/Mahl --irace ...
```

ele executa apenas uma vez e imprime somente um número:

```text
-score
```

Isso acontece porque o irace minimiza custo por padrão, enquanto meu problema quer maximizar `score`.

Portanto:

```text
score 220 → cost -220
score 225 → cost -225
score 230 → cost -230
```

Esse comportamento está correto.

## 9. `parameters.txt` atual

O espaço de busca refinado usado na segunda rodada foi:

```text
# Name                Switch           Type    Domain
population    "--population "   i   (100,200)
generations   "--generations "  i   (1000,2000)
children      "--children "     i   (60,100)
breed         "--breed "        i   (1,12)
selection     "--selection "    i   (1,12)
mutation      "--mutation "     r   (0.60,1.00)
immigration   "--immigration "  i   (5,20)
```

Esse espaço foi escolhido após uma primeira rodada de tuning.

## 10. Primeira rodada de irace

Foi feita uma primeira rodada para `Tmax=60` com:

```text
maxExperiments = 500
parallel = 4
```

A melhor configuração final da primeira rodada foi:

```text
population  = 144
generations = 1865
children    = 98
breed       = 1
selection   = 6
mutation    = 0.8245
immigration = 12
```

Valor médio aproximado:

```text
score ≈ 221.15
```

Portanto:

```text
GA original ≈ 220
irace 1ª rodada ≈ 221.15
artigo = 225
```

A primeira rodada mostrou uma região de parâmetros promissora, muito diferente do baseline original.

## 11. Segunda rodada de irace

Foi então aumentado o orçamento para:

```text
maxExperiments = 5000
parallel = 4
```

A região de busca foi refinada para:

```text
population    100–200
generations   1000–2000
children      60–100
breed         1–12
selection     1–12
mutation      0.60–1.00
immigration   5–20
```

A segunda rodada terminou com aproximadamente:

```text
experimentsUsed = 4990
```

e cerca de:

```text
2304 segundos de wall-clock
```

aproximadamente 38 minutos.

## 12. Melhor configuração da segunda rodada

A configuração vencedora foi a **ID 624**:

```text
population  = 122
generations = 1715
children    = 97
breed       = 1
selection   = 7
mutation    = 0.9941
immigration = 16
```

O comando foi:

```bash
--population 122 \
--generations 1715 \
--children 97 \
--breed 1 \
--selection 7 \
--mutation 0.9941 \
--immigration 16
```

A estimativa final do racing foi aproximadamente:

```text
score ≈ 224.23
```

portanto:

```text
GA original       ≈ 220
irace rodada 1    ≈ 221.15
irace rodada 2    ≈ 224.23
artigo            = 225
```

A configuração ainda não superou a referência de 225 de forma demonstrada.

## 13. Outras configurações elites da segunda rodada

Também apareceram como configurações fortes:

### ID 644

```text
population  = 141
generations = 1822
children    = 92
breed       = 3
selection   = 2
mutation    = 0.9903
immigration = 13
```

### ID 550

```text
population  = 132
generations = 1559
children    = 100
breed       = 1
selection   = 6
mutation    = 0.9852
immigration = 15
```

### ID 382

```text
population  = 145
generations = 1865
children    = 95
breed       = 3
selection   = 2
mutation    = 0.9786
immigration = 13
```

Há uma região consistente aproximadamente em:

```text
population   ≈ 120–145
generations  ≈ 1550–1850
children     ≈ 90–100
breed        ≈ 1–3
selection    ≈ 2–7
mutation     ≈ 0.98–1.00
immigration  ≈ 13–16
```

Isso sugere uma região promissora do espaço de parâmetros.

## 14. Estado atual

Estamos exatamente neste ponto:

```text
✅ Ubuntu 24
✅ R instalado
✅ irace instalado
✅ irace 4.4.3
✅ GA compilando
✅ --seed implementado
✅ reprodutibilidade confirmada
✅ --irace implementado
✅ modo irace executa somente 1 execução
✅ score convertido para custo negativo
✅ targetRunner funcionando
✅ cenário específico para Tmax=60
✅ checkScenario passou
✅ primeira rodada de 500 experimentos concluída
✅ segunda rodada de 5000 experimentos concluída
✅ configuração 624 encontrada
⬜ validar a configuração 624 com múltiplas seeds
⬜ verificar se média/robustez realmente supera 225
⬜ possivelmente fazer terceira rodada de tuning
⬜ depois repetir o processo para outros Tmax
```

## 15. Próximo passo que quero fazer

Não quero declarar sucesso ainda.

Quero validar a configuração 624 com **30 seeds independentes** em:

```text
Tmax = 60
```

Usando:

```text
population  = 122
generations = 1715
children    = 97
breed       = 1
selection   = 7
mutation    = 0.9941
immigration = 16
```

O objetivo da validação é obter:

```text
melhor score
pior score
média
desvio padrão
quantidade de execuções >= 225
quantidade de execuções > 225
```

Depois decidir:

### Caso 1

Se a média superar 225:

Considerar que a configuração é forte e prosseguir para outros `Tmax`.

### Caso 2

Se a melhor execução superar 225, mas a média ficar abaixo:

Considerar a configuração promissora, mas não robusta, e fazer nova rodada de tuning/refinamento.

### Caso 3

Se nem a melhor execução chegar a 225:

Refinar o espaço de busca novamente.

## 16. Muito importante

Não altere silenciosamente a arquitetura do GA.

Não introduza novos parâmetros sem justificar.

Não trate `Tmax` como hiperparâmetro no primeiro objetivo.

O objetivo é:

```text
para cada Tmax:
    encontrar parâmetros
    maximizar score
    comparar com a referência do artigo
```

Primeiro estamos trabalhando exclusivamente com:

```text
Tmax = 60
```

Depois quero repetir o mesmo processo para:

```text
5
10
15
20
25
30
35
40
46
50
55
60
65
70
73
75
80
85
```

quando tivermos certeza de que o processo experimental está correto.

## 17. Como quero que você responda

Quero respostas práticas e passo a passo, com comandos de terminal completos quando necessário.

Não pule etapas.

Sempre diferencie:

```text
baseline
resultado do irace
validação independente
referência do artigo
```

Não considere uma configuração "melhor" apenas porque teve uma única execução com score alto.

Quero priorizar resultados reprodutíveis e experimentalmente defensáveis.

Neste momento, continue a partir da **validação da configuração 624 para Tmax=60 com 30 seeds**.
