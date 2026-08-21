# population.hpp:
```c++
/**
 * @file population.hpp
 * @author  Leandro Andrade(leandro.andrade.401@ufrn.edu.br)
 * @author  Heitor Campos(heitor.campos.711@ufrn.edu.br)
 * @brief  classe que representa um Algoritmo Memético
 * Ela é responsável por gerenciar a população de indivíduos, realizar operações genéticas como cruzamento e mutação,
 * e aplicar heurísticas para melhorar as soluções encontradas.
 * @details  A classe Population é projetada para trabalhar com indivíduos representados pela estrutura Individual, 
 * que contém informações sobre o caminho percorrido, a pontuação, a distância total e o número
 * de vértices visitados. A classe oferece métodos para gerar indivíduos, calcular a aptidão da população,
 * realizar seleção de sobreviventes e cruzamento, e aplicar mutações. Além disso, a classe permite configurar
 * parâmetros como tamanho da população, taxa de mutação, quantidade de filhos desejada e penalidades para soluções que excedam o tempo máximo permitido.
 * @version 0.1
 * @date 2026-06-28
 * @copyright Copyright (c) 2026
 *
 */

#pragma once
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <random>
#include <vector>

/**
 * @brief  Namespace que encapsula todas as classes e funções relacionadas ao Algoritmo Memético
 */
namespace pop {
  
namespace detail {
/**
 * @brief  Função para obter um gerador de números aleatórios específico para cada thread
 * @return std::mt19937&  Retorna uma referência para o gerador de números aleatórios
 */
inline std::mt19937& tls_gen()
{
  thread_local std::mt19937 g{ std::random_device{}() };
  return g;
}

/**
 * @brief  Função para obter uma distribuição uniforme de números reais entre 0 e 1
 * @return std::uniform_real_distribution<double>&  Retorna uma referência para a distribuição uniforme
 */
inline std::uniform_real_distribution<double>& tls_real01()
{
  thread_local std::uniform_real_distribution<double> d(0.0, 1.0);
  return d;
}

}

/**
 * @brief  Estrutura que representa as opções de execução do Algoritmo Memético
 */
struct RunningOptions
{

  size_t populationSize{ 50 }; //> Representa o tamanho da população
  size_t generations{ 600 }; //> Representa o número de gerações
  double Tmax{ 85.0 }; //> Representa o tempo máximo permitido
  size_t childrenGoal{ 50 }; //> Representa a quantidade de filhos desejada
  size_t breedQnt{ 6 }; //> Representa a quantidade de indivíduos selecionados para cruzamento
  size_t popSelQnt{ 10 }; //> Representa a quantidade de indivíduos selecionados para a população
  size_t immigration{ 0 }; //> Representa a quantidade de indivíduos importados
  double mutationRate{ 0.40 }; //> Representa a taxa de mutação
  unsigned seed{ 0 }; //> Semente para reprodutibilidade (0 -> random)
  bool printScore{ false }; //> Representa se deve imprimir a pontuação da melhor solução encontrada
  bool allHeuristic{ true }; //> Representa se deve utilizar todas as heurísticas para a geração da população inicial
  bool useGenNearestInsertion{ false }; //> Representa se deve utilizar a heurística de inserção mais próxima para a geração da população inicial
  bool useGenNearestNeighbor{ false }; //> Representa se deve utilizar a heurística de vizinho mais próximo para a geração da população inicial
  bool useMahl{ false }; //> Representa se deve utilizar a heurística MAHL para a geração da população inicial
  bool activeMA{ false }; //> Representa se deve utilizar o Algoritmo Memético
  bool test{false }; //> Representa se deve executar em modo de teste
  bool irace{ false };

  /**
   * @brief  Função para imprimir as opções de execução do Algoritmo Memético
   */
  void print() const
  {
    std::cout << "Running Options:\n";
    std::cout << "Population Size: " << populationSize << "\n";
    std::cout << "Generations: " << generations << "\n";
    std::cout << "Tmax: " << Tmax << "\n";
    std::cout << "Seed: " << seed << "\n";
    std::cout << "Children Goal: " << childrenGoal << "\n";
    std::cout << "Breed Quantity: " << breedQnt << "\n";
    std::cout << "Population Selection Quantity: " << popSelQnt << "\n";
    std::cout << "Mutation Rate: " << mutationRate << "\n";
    std::cout << "All Heuristic: " << (allHeuristic ? "Yes" : "No") << "\n";
    std::cout << "Use Gen Nearest Insertion: " << (useGenNearestInsertion ? "Yes" : "No") << "\n";
    std::cout << "Use Gen Nearest Neighbor: " << (useGenNearestNeighbor ? "Yes" : "No") << "\n";
    std::cout << "Use Mahl: " << (useMahl ? "Yes" : "No") << "\n";
    std::cout << "Active Memetic Algorithm: " << (activeMA ? "Yes" : "No") << "\n";
    std::cout << "Immigration: " << immigration << "\n";
    std::cout << "Test: " << (test ? "Yes" : "No") << "\n";
    std::cout << "Seed: " << seed << "\n";
  }
};


/**
 * @brief  Estrutura que representa um indivíduo na população do Algoritmo Memético
 */
struct Individual
{
  std::vector<size_t> path; //> Representa o caminho percorrido pelo indivíduo, onde cada elemento é um índice de vértice
  double fitness{ 0.0 }; //> Representa a aptidão do indivíduo
  double score{ 0.0 }; //> Representa a pontuação do indivíduo
  double dist{ 0.0 }; //> Representa a distância percorrida pelo indivíduo
  size_t visited{ 0 }; //> Representa a quantidade de vértices visitados pelo indivíduo

  /**
   * @brief  Função para calcular a pontuação do indivíduo com base no caminho percorrido, lucros e penalidades
   * @return double  Retorna a pontuação calculada para o indivíduo
   */
  double calc_score(const std::vector<std::vector<double>>*, const std::vector<double>*, size_t, double, double);
};

/**
 * @brief  Classe que representa a população do Algoritmo Memético
 * Ela é responsável por gerenciar os indivíduos, realizar operações genéticas e aplicar heurísticas para melhorar as soluções encontradas.
 */
class Population
{
private:
  std::vector<Individual> population; //> Representa a população de indivíduos, onde cada elemento é um indivíduo
  const std::vector<std::vector<double>>* paths = nullptr; //> Representa a matriz de distâncias entre os vértices, onde cada elemento é uma linha da matriz
  const std::vector<double>* profits = nullptr; //> Representa os lucros associados a cada vértice, onde cada elemento é o lucro de um vértice
  size_t startNode = 0; //> Representa o índice do vértice inicial para o cálculo da pontuação
  size_t endNode = 0; //> Representa o índice do vértice final para o cálculo da pontuação
  double Tmax = 0; //> Representa o tempo máximo permitido para o cálculo da pontuação

  double allFitness = 0.0; //> Representa a soma das aptidões de todos os indivíduos na população
  double mutationRate = 0.05; //> Representa a taxa de mutação aplicada aos indivíduos durante a evolução
  size_t breedSelectionQnt = 3; //> Representa a quantidade de indivíduos selecionados para cruzamento
  size_t populationSelectionQnt = 3; //> Representa a quantidade de indivíduos selecionados para a próxima geração
  size_t childrenGoal = 5; //> Representa o número de descendentes desejado para a próxima geração
  size_t topk = 3; //< Fiz isso para testar uma população inicial mais aleatória, coloque igual a 1 se quiser que seja determinística
  double penaltyDelta{ 10.0 }; //> Representa a penalidade aplicada a soluções que excedam o tempo máximo permitido
  size_t immigration{ 0 }; //> Representa a quantidade de indivíduos importados para a população, permitindo a introdução de diversidade genética

  //> Representa a distribuição uniforme de números reais entre 0 e 1, utilizada para gerar números aleatórios durante a evolução da população
  std::uniform_real_distribution<double> realDistrib = std::uniform_real_distribution<double>(0.0, 1.0);

public:
 //> Construtor padrão da classe Population, inicializando a população, caminhos e lucros como vazios
  Population() : population(), paths(), profits(){};
  Population(const Population&) = default;

  
  Individual generate(const size_t); 


  Individual genNearestInsertion(const size_t);

 
  Individual genNearestNeighbor(const size_t);

 
  void generate_individual(const size_t, const RunningOptions&);
  void processAllFitness();
  void preprocess();
  void compact(Individual&);
  std::vector<Individual> elitism(const std::vector<Individual>&, const std::vector<Individual>&);
  std::vector<Individual> steadyState(const std::vector<Individual>&, const std::vector<Individual>&);
  std::vector<Individual> muLambda(const std::vector<Individual>&, const std::vector<Individual>&);

  void shift(Individual&);
  void swap(Individual&);
  void invert(Individual&);

  void shift(Individual&, size_t, size_t);
  void swap(Individual&, size_t, size_t);
  void invert(Individual&, size_t, size_t);

  /**
   * @brief  Função para contar a quantidade de vértices utilizados em um indivíduo
   * @param ind  Representa o indivíduo a ser analisado
   * @return size_t  Retorna a quantidade de vértices utilizados no indivíduo
   */
  static size_t usedVertices(const Individual& ind)
  {
    return std::find(ind.path.begin(), ind.path.end(), SIZE_MAX) - ind.path.begin();
  }

  void geneticMut(Individual&);
  void memeticMut(Individual&);
  void add_a_point(Individual&);
  void omit_a_point(Individual&);
  void replace_a_point(Individual&);
  void replaceBest(const Individual&);
  
  /**
   * @brief  Função para realizar a mutação de um indivíduo com base em uma função de mutação fornecida
   * @tparam mutation  Tipo da função de mutação a ser aplicada
   * @param m  Representa a função de mutação a ser aplicada
   * @param child  Representa o indivíduo a ser mutado
   */
  template<typename mutation>
  void mutate(mutation /*m*/, Individual& /*child*/);

  const Individual& tournament(size_t qnt);
  const Individual& random_choice(size_t qnt);
  const Individual& roulette(size_t qnt);

  Individual x1(const Individual&, const Individual&);

  /**
   * @brief  Função para evoluir a população utilizando seleção de sobreviventes, seleção de cruzamento, algoritmo de cruzamento e mutação
   * @tparam survivingSelection  Tipo da função de seleção de sobreviventes a ser aplicada
   * @tparam breedSelection  Tipo da função de seleção de cruzamento a ser aplicada
   * @tparam breedAlgorithm  Tipo do algoritmo de cruzamento a ser aplicado
   * @tparam mutation  Tipo da função de mutação a ser aplicada
   * @param s  Representa a função de seleção de sobreviventes a ser aplicada
   * @param bs1  Representa a função de seleção de cruzamento a ser aplicada
   * @param bs2  Representa a função de seleção de cruzamento a ser aplicada
   * @param ba  Representa o algoritmo de cruzamento a ser aplicado
   * @param m  Representa a função de mutação a ser aplicada
   */
  template<typename survivingSelection, typename breedSelection, typename breedAlgorithm, typename mutation>
  void evolve(survivingSelection /*s*/,
              breedSelection /*bs1*/,
              breedSelection /*bs2*/,
              breedAlgorithm /*ba*/,
              mutation /*m*/);

  /**
   * @brief  Função para definir a população da classe Population
   * @param p  Representa a nova população a ser definida
   */
  void setPopulation(const std::vector<Individual>& p) { population = p; }

  /**
   * @brief  Função para definir a matriz de distâncias entre os vértices
   * @param p  Representa a nova matriz de distâncias a ser definida
   */
  void setPath(const std::vector<std::vector<double>>& p) { paths = &p; }

  /**
   * @brief  Função para definir os lucros associados a cada vértice
   * @param p  Representa o novo vetor de lucros a ser definido
   */
  void setProfits(const std::vector<double>& p) { profits = &p; }

  /**
   * @brief  Função para definir a quantidade de indivíduos a serem selecionados para reprodução
   * @param s  Representa a nova quantidade de indivíduos a ser definida
   */

  void setBreedQnt(const size_t s) { breedSelectionQnt = s; }
  /**
   * @brief  Função para definir a quantidade de indivíduos a serem selecionados para a próxima geração
   * @param p  Representa a nova quantidade de indivíduos a ser definida
   */
  void setPopSelQnt(const size_t p) { populationSelectionQnt = p; }

  /**
   * @brief  Função para definir a taxa de mutação aplicada aos indivíduos durante a evolução
   * @param r  Representa a nova taxa de mutação a ser definida
   */
  void setRate(const double r) { mutationRate = r; }

  /**
   * @brief  Função para definir a quantidade de filhos desejada para a próxima geração
   * @param c  Representa a nova quantidade de filhos a ser definida
   */
  void setChildrenGoal(const size_t c) { childrenGoal = c; }

  /**
   * @brief  Função para definir o tempo máximo permitido para o cálculo da pontuação
   * @param t  Representa o novo tempo máximo a ser definido
   */
  void setTmax(const double t)
  {
    Tmax = t;
    if (Tmax <= 15) {
      setPenaltyDelta(10.0);
    } else if (Tmax <= 50) {
      setPenaltyDelta(40.0);
    } else {
      setPenaltyDelta(100.0);
    }
  }

  /**
   * @brief  Função para definir o vértice final para o cálculo da pontuação
   * @param n  Representa o novo vértice final a ser definido
   */
  void setEndNode(const size_t n) { endNode = n; }

  /**
   * @brief  Função para definir o vértice inicial para o cálculo da pontuação
   * @param n  Representa o novo vértice inicial a ser definido
   */
  void setStartNode(const size_t n) { startNode = n; }

  /**
   * @brief  Função para definir a penalidade aplicada a soluções que excedam o tempo máximo permitido
   * @param pd  Representa a nova penalidade a ser definida
   */
  void setPenaltyDelta(const double pd) { penaltyDelta = pd; }

  /**
   * @brief  Função para definir a quantidade de indivíduos importados para a população, permitindo a introdução de diversidade genética
   * @param i  Representa a nova quantidade de indivíduos importados a ser definida
   */
  void setImmigration(const size_t i) { immigration = i; }

  /**
   * @brief  Função para realizar a imigração de novos indivíduos na população
   * @param city_qnt  Representa a quantidade de vértices disponíveis para a imigração
   */
  void imigrate(size_t);

  /**
   * @brief  Função para intensificar o melhor indivíduo da população, aplicando mutações e melhorias
   * @param max_iter  Representa o número máximo de iterações para tentar melhorar o indivíduo
   */
  const Individual& getBest() const;

  /**
   * @brief  Função para intensificar o melhor indivíduo da população, aplicando mutações e melhorias
   * @param max_iter  Representa o número máximo de iterações para tentar melhorar o indivíduo
   */
  void intensifyBest(int = 100);
};


template<typename survivingSelection, typename breedSelection, typename breedAlgorithm, typename mutation>
void Population::evolve(survivingSelection s, breedSelection bs1, breedSelection bs2, breedAlgorithm ba, mutation m)
{
  std::vector<Individual> childs(childrenGoal);

  // #pragma omp parallel for
  for (long long i = 0; i < static_cast<long long>(childrenGoal); ++i) {
    const Individual& father = (this->*bs1)(breedSelectionQnt);
    const Individual& mother = (this->*bs2)(breedSelectionQnt);

    Individual child = (this->*ba)(father, mother);

    mutate(m, child);
    child.calc_score(paths, profits, endNode, Tmax, penaltyDelta);
    childs[i] = std::move(child);
  }

  population = std::move((this->*s)(population, childs));
}

template<typename mutation>
void Population::mutate(mutation m, Individual& child)
{
  if (detail::tls_real01()(detail::tls_gen()) < mutationRate) {
    (this->*m)(child);
  }
}
};

```
# main.cpp:

```c++

/**
 * @file main.cpp
 * @author  Leandro Andrade(leandro.andrade.401@ufrn.edu.br)
 * @author  Heitor Campos(heitor.campos.711@ufrn.edu.br) 
 * @brief  Classe para execução do Algoritmo Memético
 * @version 0.1
 * @date 2026-07-05
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "population.hpp"
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace pop; 

using vec3 = std::vector<std::tuple<double, double, double>>; //> alias para vetor de tuplas representando coordenadas e lucros
using vec2 = std::vector<std::vector<double>>; //> alias para vetor de vetores representando distâncias entre pontos
template<typename T>
using vec = std::vector<T>; //> alias para vetor genérico
using raw_str = const char*; //> alias para string constante

/**
 * @brief  Função para calcular a matriz de distâncias e os lucros a partir das coordenadas dos pontos
 * usa a distância euclidiana para calcular a distância entre os pontos
 *  dist[i][j] = sqrt((x_i - x_j)^2 + (y_i - y_j)^2)
 * @param raw  Representa as coordenadas dos pontos e os lucros associados a cada ponto
 * @param dist  Representa a matriz de distâncias entre os pontos
 * @param profits  Representa os lucros associados a cada ponto
 */
void CalculeDistance(const vec3& raw, vec2& dist, vec<double>& profits)
{
  const size_t N = raw.size();
  dist.resize(N, std::vector<double>(N, 0.0));
  profits.resize(N);

  for (size_t i = 0; i < N; ++i) {
    profits[i] = std::get<2>(raw[i]);
    for (size_t j = 0; j < N; ++j) {

      double dx = std::get<0>(raw[i]) - std::get<0>(raw[j]);
      double dy = std::get<1>(raw[i]) - std::get<1>(raw[j]);
      dist[i][j] = std::sqrt(dx * dx + dy * dy);
    }
  }
}

/**
 * @brief  Função para imprimir as coordenadas e lucros dos pontos
 * @param raw  Representa as coordenadas dos pontos e os lucros associados a cada ponto
 */
void PrintRaw(const vec3& raw)
{
  for (const auto& point : raw) {
    std::cout << "X: " << std::get<0>(point) << ", Y: " << std::get<1>(point) << ", C: " << std::get<2>(point) << "\n";
  }
}

/**
 * @brief  Função para imprimir a matriz de distâncias entre os pontos
 * @param dist  Representa a matriz de distâncias entre os pontos
 */
void PrintDistance(const vec2& dist)
{
  for (const auto& row : dist) {
    for (const auto& d : row) {
      std::cout << d << " ";
    }
    std::cout << "\n";
  }
}

/**
 * @brief  Função para imprimir informações sobre a melhor solução encontrada
 * @param gaPop  Representa a população do algoritmo genético
 * @param Tmax  Representa o tempo máximo permitido
 */
void PrintInfo(const Population& gaPop, double Tmax)
{
  const Individual& best = gaPop.getBest();
  std::cout << '\n';
  std::cout << "score: " << best.score << "\n";
  std::cout << "distancia: " << std::fixed << std::setprecision(2) << best.dist << " (Tmax = " << Tmax << ")\n";
  std::cout << "caminho: ";
  // for (size_t node : best.path) std::cout << node << " ";
  for (size_t i{ 0 }; i < best.path.size(); ++i)
    if (best.path[i] != SIZE_MAX) std::cout << best.path[i] + 1 << ' ';
  std::cout << 32 << '\n';
}

/**
 * @brief  Função para executar o algoritmo genético e imprimir os resultados
 * @param popSize  Representa o tamanho da população
 * @param N  Representa o número de pontos
 * @param options  Representa as opções de execução do algoritmo
 * @param basePop  Representa a população do algoritmo genético
 * @param result  Representa a string de resultados
 * @param times  Representa os tempos de execução das diferentes execuções
 */
void Run(const size_t popSize,
         const size_t N,
         const RunningOptions& options,
         const Population& basePop,
         std::string&& result = "",
         vec<std::pair<int, Population>>&& times = {},
         const size_t executions = 20)
{
    times.assign(executions, std::pair<int, Population>{ 0, Population{} });
    for (size_t i{ 0 }; i < executions; ++i) 
    {
        Population gaPop = basePop;

     result += "Execução " + std::to_string(i + 1) + ": ";
    auto start{ std::chrono::steady_clock::now() };
    for (size_t j = 0; j < popSize; ++j) {
      gaPop.generate_individual(N, options);
    }

        gaPop.processAllFitness();

        const size_t generations = options.generations;
        for (size_t g = 0; g < generations; ++g) {
        gaPop.evolve(&Population::steadyState,
                    &Population::tournament,
                    &Population::random_choice,
                    &Population::x1,
                    &Population::memeticMut);

        if (g % 15 == 0) 
            gaPop.imigrate(N);
        

        gaPop.processAllFitness();

        if (options.printScore) 
            if (g % 25 == 0) 
            {
            const Individual& best = gaPop.getBest();
            std::cout << "geracao " << g << " | melhor score = " << best.score << " | dist = " << best.dist << "\n";
            }
        

        if (g % 50 == 0) 
            gaPop.intensifyBest(20);
        
        }
        auto end{ std::chrono::steady_clock::now() };
        auto diff{ end - start };
        // auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
        result += "Tempo de execução: " +
                std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() % 1000) + "ms\n";

        auto current = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
        times[i].first = current;
        times[i].second = gaPop;
    }
    
}

/**
 * @brief  Função para melhorar a solução encontrada pelo algoritmo genético
 * @param gaPop  Representa a população do algoritmo genético
 * @param Tmax  Representa o tempo máximo permitido
 */
void improve(Population& gaPop, double Tmax = 85.0)
{
    //std::cout << "Starting Memetic Algorithm...\n";

    auto start = std::chrono::steady_clock::now();

    Individual best = gaPop.getBest();

    const size_t used = Population::usedVertices(best);

    bool improved = true;

    while(improved)
    {
        improved = false;

        Individual bestNeighbor = best;


        for(size_t i = 1; i < used - 1; ++i)
        {
            for(size_t j = i + 1; j < used; ++j)
            {
                Individual candidate = best;

                gaPop.swap(candidate, i, j);

                if(candidate.dist < bestNeighbor.dist and candidate.dist <= Tmax)
                {
                    bestNeighbor = std::move(candidate);
                }
            }
        }

        if(bestNeighbor.dist < best.dist and bestNeighbor.dist <= Tmax)
        {
            std::cout << "swap dist: "
                      << best.dist
                      << " <-> "
                      << bestNeighbor.dist
                      << '\n';

            best = std::move(bestNeighbor);
            improved = true;
        }

        bestNeighbor = best;

        for(size_t i = 1; i < used - 1; ++i)
        {
            for(size_t j = i + 1; j < used; ++j)
            {
                Individual candidate = best;

                gaPop.shift(candidate, i, j);

                if(candidate.dist < bestNeighbor.dist and candidate.dist <= Tmax)
                {
                    bestNeighbor = std::move(candidate);
                }
            }
        }

        if(bestNeighbor.dist < best.dist and bestNeighbor.dist <= Tmax)
        {
            std::cout << "shift dist: "
                      << best.dist
                      << " <-> "
                      << bestNeighbor.dist
                      << '\n';

            best = std::move(bestNeighbor);
            improved = true;
        }
    
    }

    auto end = std::chrono::steady_clock::now();

   auto elapsed = end - start;

std::cout
    << "MA time = "
    << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << " ns ("
    << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << " us, "
    << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << " ms)\n";
    gaPop.replaceBest(best);

}

/**
 * @brief  Mensagem de ajuda para o usuário
 */
inline raw_str HELP_MESSAGE = R"(Usage: Mahl [<options>] 

Rendering simulation options:
  -h, --help                           Show this help message and exit
  -p <value>, --population <value>     Set the population size (default: 50)
  -g <value>, --generations <value>    Set the number of generations (default: 600)
  -tx <value>, --tmax <value>          Set the Tmax value (default: 85.0)
  -c <value>, --children <value>       Set the children goal (default: 50)
  -b <value>, --breed <value>          Set the breed quantity (default: 6)
  -s <value>, --selection <value>      Set the population selection quantity (default: 10)
  -m <value>, --mutation <value>       Set the mutation rate (default: 0.40)
  -i <value>, --immigration <value>    Set the immigration quantity (default: 0)
  --seed <value>                       Set the random seed (default: 0)
  --irace                              Run a single execution for irace
  -ps, --print-score                   Print the best score every 25% generations
  -allHeuristic                        Use all heuristic methods for initial population generation (default: true)
  -gni, --useGenNearestInsertion       Use the nearest insertion heuristic for initial population generation
  -gnn, --useGenNearestNeighbor        Use the nearest neighbor heuristic for initial population generation
  -gm, --useMahl                       Use the MAHL algorithm for evolution 
  -ama, --activeMA                     Activate the Memetic Algorithm for local search
  -t, -test                            Run the program in test mode, executing multiple runs with different Tmax values

   Obs: The program will run 20 executions with the specified parameters and print the best solution found, along with the average execution time.
   When activating a heuristic, the last result will always be considered.
   )";


/**
  * @brief  Função para executar testes com diferentes valores de Tmax
  *  O programa executará 20 execuções para cada valor de Tmax e imprimirá a melhor solução encontrada, juntamente com o tempo médio de execução.
  *  O interval de Tmaxs é definido como { 5, 10, 20, 30, 40, 50, 60, 70, 80, 85 }.
  *  O programa também permite ativar ou desativar o Algoritmo Memético (MA) para busca local, dependendo das opções fornecidas.
  *  O programa também permite ativar ou desativar diferentes heurísticas para a geração da população inicial, dependendo das opções fornecidas.
  * @param options  Representa as opções de execução do algoritmo
  * @param raw  Representa as coordenadas dos pontos e os lucros associados a cada ponto
  * @param dist  Representa a matriz de distâncias entre os pontos
  * @param profits  Representa os lucros associados a cada ponto
  */
void test(RunningOptions& options, const vec3& raw, const vec2& dist, const vec<double>& profits)
{
  vec<int> Tmaxs = { 5, 10, 20, 30, 40, 50, 60, 70, 80, 85 };
  Population gaPop;
  gaPop.setPath(dist);
  gaPop.setProfits(profits);
  gaPop.setStartNode(0);
  gaPop.setEndNode(31);
  gaPop.setTmax(Tmaxs[0]);

  gaPop.setChildrenGoal(options.childrenGoal);
  gaPop.setBreedQnt(options.breedQnt);
  gaPop.setPopSelQnt(options.popSelQnt);
  gaPop.setRate(options.mutationRate);
  gaPop.setImmigration(options.immigration);
  const size_t N = raw.size();
  const size_t popSize = options.populationSize;


  for(int Tmax : Tmaxs)
{
    gaPop.setTmax(Tmax);

    std::string result;
    vec<std::pair<int,Population>> times;

    Run(popSize, N, options, gaPop, std::move(result), std::move(times));
    int media = 0;

    Population best = times.front().second;
    Population worse = times.front().second;
    double averageScore{0};

    for(const auto& exec : times)
    {
        media += exec.first;

        auto ind = exec.second.getBest();
        
        if(ind.fitness > best.getBest().fitness)
            best = exec.second;
        if(ind.fitness < worse.getBest().fitness)
            worse = exec.second;

        averageScore += ind.score;
    }

    media /= times.size();
    averageScore /= times.size();

    std::cout << "\n=====================================\n";
    std::cout << "Tmax = " << Tmax << '\n';
    std::cout << "Tempo médio = " << media << " ms\n";
    std::cout << "Melhor solução GA:\n";
    PrintInfo(best, Tmax);
    std::cout << '\n';
    std::cout << "Pior solução GA:\n";
    PrintInfo(worse, Tmax);

    std::cout << "Score médio = " << std::fixed << std::setprecision(2) << averageScore << "\n";

    if(options.activeMA)
    {
        improve(best, Tmax);
        improve(worse, Tmax);

        std::cout << "A MELHOR solução pós MA:";
        PrintInfo(best, Tmax);

        std::cout << "A PIOR solução pós MA:";
        PrintInfo(worse, Tmax);
    }
  }
}

/**
 * @brief  Função principal do programa
 *  O programa executará o Algoritmo Genético (GA) e, opcionalmente, o Algoritmo Memético (MA) para busca local.
 *  O programa permite configurar diversos parâmetros de execução, como tamanho da população, número de gerações, taxa de mutação, entre outros.
 *  O programa também permite ativar ou desativar diferentes heurísticas para a geração da população inicial, dependendo das opções fornecidas.
 * @param argc  Representa o número de argumentos passados para o programa
 * @param argv  Representa os argumentos passados para o programa
 * @return int  Retorna 0 em caso de sucesso
 */
int main(int argc, char* argv[])
{
  vec3 raw = { { 10.5, 14.4, 0 },  { 18, 15.9, 10 },   { 18.3, 13.3, 10 }, { 16.5, 9.3, 10 },  { 15.4, 11, 10 },
               { 14.9, 13.2, 5 },  { 16.3, 13.3, 5 },  { 16.4, 17.8, 5 },  { 15, 17.9, 5 },    { 16.1, 19.6, 10 },
               { 15.7, 20.6, 10 }, { 13.2, 20.1, 10 }, { 14.3, 15.3, 5 },  { 14, 5.1, 10 },    { 11.4, 6.7, 15 },
               { 8.3, 5, 15 },     { 7.9, 9.8, 10 },   { 11.4, 12, 5 },    { 11.2, 17.6, 5 },  { 10.1, 18.7, 5 },
               { 11.7, 20.3, 10 }, { 10.2, 22.1, 10 }, { 9.7, 23.8, 10 },  { 10.1, 26.4, 15 }, { 7.4, 24, 15 },
               { 8.2, 19.9, 15 },  { 8.7, 17.7, 10 },  { 8.9, 13.6, 10 },  { 5.6, 11.1, 10 },  { 4.9, 18.9, 10 },
               { 7.3, 18.8, 10 },  { 11.2, 14.1, 0 } };


  RunningOptions options;

  for (int i{ 0 }; i < argc; ++i) {
    if (std::strcmp(argv[i], "-h") == 0 or std::strcmp(argv[i], "--help") == 0) {
      std::cout << HELP_MESSAGE;
      return 0;
    }
    // Add more option parsing logic here
    else if (std::strcmp(argv[i], "-p") == 0 or std::strcmp(argv[i], "--population") == 0) {
      if (i + 1 < argc) { 
        options.populationSize = std::stoul(argv[++i]);
      }
    } else if (std::strcmp(argv[i], "-g") == 0 or std::strcmp(argv[i], "--generations") == 0) {
      if (i + 1 < argc) {
        options.generations = std::stoul(argv[++i]);
      }
    } else if (std::strcmp(argv[i], "-tx") == 0 or std::strcmp(argv[i], "--tmax") == 0) {
      if (i + 1 < argc) {
        options.Tmax = std::stod(argv[++i]);
      }
    } else if (std::strcmp(argv[i], "-c") == 0 or std::strcmp(argv[i], "--children") == 0) {
      if (i + 1 < argc) {
        options.childrenGoal = std::stoul(argv[++i]);
      }
    } else if (std::strcmp(argv[i], "-b") == 0 or std::strcmp(argv[i], "--breed") == 0) {
      if (i + 1 < argc) {
        options.breedQnt = std::stoul(argv[++i]);
      }
    } else if (std::strcmp(argv[i], "-s") == 0 or std::strcmp(argv[i], "--selection") == 0) {
      if (i + 1 < argc) {
        options.popSelQnt = std::stoul(argv[++i]);
      }
    } else if (std::strcmp(argv[i], "-m") == 0 or std::strcmp(argv[i], "--mutation") == 0) {
      if (i + 1 < argc) {
        options.mutationRate = std::stod(argv[++i]);
      }
    } else if (std::strcmp(argv[i], "-ps") == 0 or std::strcmp(argv[i], "--print-score") == 0) {
      options.printScore = true;
    } else if (std::strcmp(argv[i], "--seed") == 0) {
      if (i + 1 < argc) {
        options.seed = static_cast<unsigned>(std::stoul(argv[++i]));
      }
    } else if (std::strcmp(argv[i], "--irace") == 0) {
      options.irace = true;
    } else if (std::strcmp(argv[i], "-i") == 0 or std::strcmp(argv[i], "--immigration") == 0) {
      options.immigration = std::stoul(argv[++i]);
    } else if (std::strcmp(argv[i], "-allHeuristic") == 0) {
      options.allHeuristic = true;
      options.useGenNearestInsertion = false;
      options.useGenNearestNeighbor = false;
      options.useMahl = false;

    } else if (std::strcmp(argv[i], "-gni") == 0 or std::strcmp(argv[i], "--useGenNearestInsertion") == 0) {
      options.useGenNearestInsertion = true;
      options.allHeuristic = false;
      options.useGenNearestNeighbor = false;
      options.useMahl = false;
    } else if (std::strcmp(argv[i], "-gnn") == 0 or std::strcmp(argv[i], "--useGenNearestNeighbor") == 0) {
      options.useGenNearestNeighbor = true;
      options.allHeuristic = false;
      options.useGenNearestInsertion = false;
      options.useMahl = false;
    } else if (std::strcmp(argv[i], "-gm") == 0 or std::strcmp(argv[i], "--useMahl") == 0) {
      options.useMahl = true;
      options.useGenNearestInsertion = false;
      options.useGenNearestNeighbor = false;
      options.allHeuristic = false;
    } else if (std::strcmp(argv[i], "-ama") == 0 or std::strcmp(argv[i], "--activeMA") == 0) {
      options.activeMA = true;
    }
    else if (std::strcmp(argv[i], "-t") == 0 or std::strcmp(argv[i], "-test") == 0) {
      options.test = true;
    }
  }

  if (options.irace && options.test) {
    std::cerr << "Erro: --irace e --test não podem ser usados simultaneamente.\n";
    return 1;
  }

  if(options.test)
  {
    vec2 dist(raw.size(), vec<double>(raw.size(), 0.0));
    vec<double> profits(raw.size());
    CalculeDistance(raw, dist, profits);
    test(options, raw, dist, profits);
    return 0;
  }

  std::string result{};
  vec<std::pair<int, Population>> times{};
  double Tmax{ options.Tmax };
  const size_t N = raw.size();

  vec2 dist(N, vec<double>(N, 0.0));
  vec<double> profits(N);

  CalculeDistance(raw, dist, profits);

  Population gaPop;
  gaPop.setPath(dist);
  gaPop.setProfits(profits);
  gaPop.setStartNode(0);
  gaPop.setEndNode(31);
  gaPop.setTmax(static_cast<double>(Tmax));

  gaPop.setChildrenGoal(options.childrenGoal);
  gaPop.setBreedQnt(options.breedQnt);
  gaPop.setPopSelQnt(options.popSelQnt);
  gaPop.setRate(options.mutationRate);
  gaPop.setImmigration(options.immigration);
  const size_t popSize = options.populationSize;

  // Em execuções normais, seed=0 mantém o comportamento aleatório original.
  // No modo irace, a seed fornecida pelo irace será aplicada aqui.
  if (options.seed != 0) {
    detail::tls_gen().seed(options.seed);
  }

  const size_t executions = options.irace ? 1 : 20;

  Run(
      popSize,
      N,
      options,
      gaPop,
      std::move(result),
      std::move(times),
      executions
  );

  // O irace precisa receber somente uma métrica numérica.
  // Como o irace minimiza por padrão e nosso objetivo é maximizar score,
  // retornamos o score com sinal invertido.
  if (options.irace) {
    const double cost = -times[0].second.getBest().score;
    std::cout << std::fixed << std::setprecision(6) << cost << '\n';
    return 0;
  }

  std::cout << "Resultados das 20 execuções:\n";
  options.print();  
  std::cout << result << "\n";


  Population bestPop{times[0].second};
  Population worsePop{times[0].second};
  auto mediaTime{ times[0].first };
  double sumScores{times[0].second.getBest().score};
  
  for (size_t i{ 1 }; i < times.size(); ++i) {
    mediaTime += times[i].first;
    double currentScore = times[i].second.getBest().score;
    sumScores += currentScore;
    
    if (currentScore > bestPop.getBest().score) {
          bestPop = times[i].second;
      }
      
      if (currentScore < worsePop.getBest().score) {
          worsePop = times[i].second;
      }
  }
  mediaTime /= times.size();
  double mediaScores = sumScores / times.size();

  std::cout << "Menor Valor Encontrado (Pior Score): " << worsePop.getBest().score << "\n";
  std::cout << "Maior Valor Encontrado (Melhor Score): " << bestPop.getBest().score << "\n";
  std::cout << "Valor Medio dos Scores: " << mediaScores << "\n";
  std::cout << "Tempo médio de execução: " << mediaTime << "ms\n";

  std::cout << "Detalhes da MELHOR solução encontrada (GA):\n";
  PrintInfo(bestPop, options.Tmax);
  std::cout << "Detalhes da PIOR solução encontrada (GA):\n";
  PrintInfo(worsePop, options.Tmax);

  std::cout << "\n";
  if (options.activeMA) {
    std::cout << "\nAplicando Busca Local sobre a Melhor Solucao:\n";
    improve(bestPop, options.Tmax);
    PrintInfo(bestPop, options.Tmax);
    std::cout << "\nAplicando Busca Local sobre a Pior Solucao:\n";
    improve(worsePop, options.Tmax);
    PrintInfo(worsePop, options.Tmax);
  }

  return 0;
}
```

# population.cpp:

```c++
#include "population.hpp"
#include <algorithm>
#include <cstddef>
#include <future>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
namespace pop {

/**
 * @brief  Função para comparar dois indivíduos com base na distância percorrida
 * @param id1  Representa o primeiro indivíduo
 * @param id2  Representa o segundo indivíduo
 * @return bool  Retorna true se a distância do primeiro indivíduo for menor que a do segundo, caso contrário, retorna
 * false
 */
bool operatorDist(const Individual& id1, const Individual& id2) { return id1.dist < id2.dist; }

/**
 * @brief  Função para comparar dois indivíduos com base na aptidãO
 * @param id1  Representa o primeiro indivíduo
 * @param id2  Representa o segundo indivíduo
 * @return bool Retorna true se a aptidão do primeiro indivíduo for maior que a do segundo, caso contrário, retorna
 * false
 */
bool operatorFitness(const Individual& id1, const Individual& id2) { return id1.fitness > id2.fitness; }

/**
 * @brief  Função para comparar dois indivíduos com base na pontuação
 * @param id1  Representa o primeiro indivíduo
 * @param id2  Representa o segundo indivíduo
 * @return bool Retorna true se a pontuação do primeiro indivíduo for maior que a do segundo, caso contrário, retorna
 * false
 */
bool betterScore(const Individual& id1, const Individual& id2) { return id1.fitness > id2.fitness; }

/**
 * @brief Calcula a pontuação e o fitness do indivíduo.
 *
 * Soma os lucros dos nós visitados, calcula a distância total da rota e aplica
 * uma penalização ao fitness caso a distância exceda `Tmax`.
 *
 * @param dists Matriz de distâncias entre os nós.
 * @param profits Vetor de lucros dos nós.
 * @param endNode Nó de destino da rota.
 * @param Tmax Distância máxima permitida.
 * @param penaltyDelta Fator de penalização por exceder `Tmax`.
 * @return Valor de fitness do indivíduo.
 */
double Individual::calc_score(const std::vector<std::vector<double>>* dists,
                              const std::vector<double>* profits,
                              size_t endNode,
                              double Tmax,
                              double penaltyDelta)
{
  score = (*profits)[path[0]];
  dist = 0;
  size_t prev = path[0];
  visited = 1;
  for (size_t i = 1; i < path.size(); ++i) {
    if (path[i] == SIZE_MAX) continue;

    double edge = (*dists)[prev][path[i]];
    dist += edge;
    score += (*profits)[path[i]];
    prev = path[i];
    visited++;
  }
  dist += (*dists)[prev][endNode];

  //< Essa é o fitness usado pelo artigo do algoritmo genético.
  if (dist > Tmax) {
    double excess = dist - Tmax;

    fitness = score / (1.0 + (excess * penaltyDelta * 5.0));
  } else {
    fitness = score;
  }

  return fitness;
}

/**
 * @brief Remove aleatoriamente um nó da rota do indivíduo.
 *
 * Seleciona uma posição válida do caminho (exceto a primeira) e a marca como
 * `SIZE_MAX`, indicando que o nó foi omitido.
 *
 * @param child Indivíduo cuja rota será modificada.
 */
void Population::omit_a_point(Individual& child)
{
  std::vector<size_t> valid_positions;
  for (size_t i = 1; i < child.path.size(); ++i) {
    if (child.path[i] != SIZE_MAX) valid_positions.push_back(i);
  }

  if (not valid_positions.empty()) {
    std::uniform_int_distribution<size_t> distrib(0, valid_positions.size() - 1);
    size_t target = valid_positions[distrib(detail::tls_gen())];
    child.path[target] = SIZE_MAX;
  }
}

/**
 * @brief Insere um novo nó na rota do indivíduo.
 *
 * Seleciona aleatoriamente um nó ainda não visitado e o insere na posição que
 * produz o menor aumento de distância, desde que a rota permaneça dentro de
 * `Tmax`.
 *
 * @param child Indivíduo cuja rota será modificada.
 */
void Population::add_a_point(Individual& child)
{
  compact(child);

  size_t size = paths->size();
  std::vector<bool> present(size, false);
  size_t valid_count = 0;
  for (unsigned long p : child.path) {
    if (p != SIZE_MAX) {
      present[p] = true;
      ++valid_count;
    }
  }

  std::vector<size_t> missing_cities;
  for (size_t c = 0; c < size; ++c) {
    if (!present[c] && c != startNode && c != endNode) missing_cities.push_back(c);
  }

  if (missing_cities.empty() || valid_count == 0 || valid_count >= child.path.size()) return;

  std::uniform_int_distribution<size_t> dist_city(0, missing_cities.size() - 1);
  size_t city = missing_cities[dist_city(detail::tls_gen())];
  double bestDetour = std::numeric_limits<double>::max();
  size_t bestPos = valid_count;

  for (size_t i = 0; i < valid_count; ++i) {
    size_t u = child.path[i];
    size_t v = (i + 1 < valid_count) ? child.path[i + 1] : endNode;
    double detour = (*paths)[u][city] + (*paths)[city][v] - (*paths)[u][v];
    if (detour < bestDetour && child.dist + detour <= Tmax) {
      bestDetour = detour;
      bestPos = i + 1;
    }
    
  }

  for (size_t i = child.path.size() - 1; i > bestPos; --i) {
    child.path[i] = child.path[i - 1];
  }
  
  child.path[bestPos] = city;
  
}


/**
 * @brief Substitui um nó da rota por um nó ainda não visitado.
 *
 * Escolhe aleatoriamente uma posição válida da rota (exceto a primeira) e a
 * substitui por um nó ausente. Os candidatos são classificados de forma gulosa,
 * considerando o maior lucro ou a melhor relação entre lucro e custo de
 * inserção, sendo um dos melhores candidatos selecionado aleatoriamente.
 *
 * @param child Indivíduo cuja rota será modificada.
 */
void Population::replace_a_point(Individual& child)
{
  compact(child);

  size_t v_count = 0;
  std::vector<bool> present(paths->size(), false);
  for (size_t i = 0; i < child.path.size(); ++i) {
    if (child.path[i] != SIZE_MAX) {
      v_count++;
      present[child.path[i]] = true;
    }
  }

  if (v_count < 2) return;
  std::vector<size_t> missing;
  for (size_t c = 0; c < paths->size(); ++c) {
    if (!present[c] && c != startNode && c != endNode) missing.push_back(c);
  }
  if (missing.empty()) return;

  std::uniform_int_distribution<size_t> dist_pos(1, v_count - 1);
  size_t replace_pos = dist_pos(detail::tls_gen());

  size_t node_old = child.path[replace_pos];
  size_t node_A = child.path[replace_pos - 1];
  size_t node_B = (replace_pos + 1 < v_count) ? child.path[replace_pos + 1] : endNode;

  /**
   * @brief Estrutura para armazenar candidatos à substituição.
   */
  struct Candidate
  {
    double ratio; //> Representa a relação entre lucro e custo de inserção do candidato
    size_t city; //> Representa o índice do vértice candidato à substituição
  };


  std::vector<Candidate> candidates;

  double old_dist = (*paths)[node_A][node_old] + (*paths)[node_old][node_B];
  std::uniform_real_distribution<double> rdist(0.0, 1.0);
  bool greedy_for_profit = (rdist(detail::tls_gen()) < 0.5);

  for (size_t c : missing) {
    double new_dist = (*paths)[node_A][c] + (*paths)[c][node_B];
    double added_cost = new_dist - old_dist;

    added_cost = std::max(added_cost, 0.0001);
    double ratio;
    if (greedy_for_profit) {
      ratio = std::pow((*profits)[c], 2);
    } else {
      ratio = (*profits)[c] / added_cost;
    }

    candidates.push_back({ ratio, c });
  }
  if (candidates.empty()) return;
  std::sort(
    candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) { return a.ratio > b.ratio; });

  size_t kLimit = std::min<size_t>(3, candidates.size());
  std::uniform_int_distribution<size_t> dist_pick(0, kLimit - 1);
  size_t chosen_city = candidates[dist_pick(detail::tls_gen())].city;

  child.path[replace_pos] = chosen_city;
}

/**
 * @brief Gera um indivíduo por meio da heurística de inserção do vizinho mais próximo.
 *
 * A rota é construída de forma incremental, iniciando no nó inicial e inserindo
 * sucessivamente nós ainda não visitados na posição que produz o menor aumento
 * de distância. Em cada iteração, os candidatos viáveis são ordenados pela
 * relação entre lucro e custo de inserção, e um dos melhores é escolhido
 * aleatoriamente para diversificar a solução, sempre respeitando o limite de
 * distância `Tmax`. Ao final, o fitness do indivíduo é calculado.
 *
 * @param city_qnt Quantidade total de nós da instância.
 * @return Indivíduo gerado pela heurística.
 */
Individual Population::genNearestInsertion(const size_t city_qnt)
{
  Individual ind;
  ind.path.assign(city_qnt, SIZE_MAX);

  std::vector<bool> in_tour(city_qnt, false);
  in_tour[startNode] = true;
  in_tour[endNode] = true;

  std::vector<size_t> tour;
  tour.push_back(startNode);
  double current_dist = (*paths)[startNode][endNode];

  /**
   * @brief Estrutura para armazenar candidatos à inserção.
   */
  struct Candidate
  {
    double detour; //> Representa o aumento de distância causado pela inserção do candidato
    size_t node; //> Representa o índice do vértice candidato à inserção
    size_t insertPos; //> Representa a posição na rota onde o candidato será inserido
    double ratio; //> Representa a relação entre lucro e custo de inserção do candidato
  };

  while (true) {
    std::vector<Candidate> candidates;

    for (size_t k{ 0 }; k < city_qnt; ++k) {
      if (in_tour[k] || k == startNode || k == endNode) continue;

      double bestDetourForK = std::numeric_limits<double>::max();
      size_t bestPosForK = 0;
      bool feasible = false;

      for (size_t i{ 0 }; i < tour.size(); ++i) {
        size_t u{ tour[i] };
        size_t v = (i + 1 < tour.size()) ? tour[i + 1] : endNode;
        double detour = (*paths)[u][k] + (*paths)[k][v] - (*paths)[u][v];

        if (detour < bestDetourForK && current_dist + detour <= Tmax) {
          bestDetourForK = detour;
          bestPosForK = i + 1;
          feasible = true;
        }
      }
      if (feasible) {
        double ratio = (*profits)[k] / (1.0 + std::max(bestDetourForK, 0.0));
        candidates.push_back({ bestDetourForK, k, bestPosForK, ratio });
      }
    }

    if (candidates.empty()) break;

    size_t kLimit = std::min(topk, candidates.size());
    std::partial_sort(candidates.begin(),
                      candidates.begin() + kLimit,
                      candidates.end(),
                      [](const Candidate& a, const Candidate& b) { return a.ratio > b.ratio; });

    std::uniform_int_distribution<size_t> pick(0, kLimit - 1);
    const Candidate& chosen = candidates[pick(detail::tls_gen())];

    tour.insert(tour.begin() + chosen.insertPos, chosen.node);
    in_tour[chosen.node] = true;
    current_dist += chosen.detour;
  }

  for (size_t i = 0; i < tour.size(); ++i) {
    ind.path[i] = tour[i];
  }

  if (paths && profits) {
    ind.calc_score(paths, profits, endNode, Tmax, penaltyDelta);
  }

  return ind;
}


/**
 * @brief Gera um indivíduo utilizando a heurística do vizinho mais próximo.
 *
 * A rota é construída incrementalmente a partir do nó inicial. Em cada etapa,
 * é selecionado o nó não visitado mais próximo do nó atual, desde que sua
 * inclusão permita concluir a rota no nó final sem exceder o limite de
 * distância `Tmax`. O processo termina quando não existem mais inserções
 * viáveis ou todos os nós foram avaliados. Ao final, a pontuação e o fitness
 * do indivíduo são calculados.
 *
 * @param city_qnt Quantidade total de nós da instância.
 * @return Indivíduo gerado pela heurística do vizinho mais próximo.
 */
Individual Population::genNearestNeighbor(const size_t city_qnt)
{
  Individual v;                      //> cria um indivíduo vazio
  v.path.assign(city_qnt, SIZE_MAX); // coloca todos os nós como não visitados
  v.path[0] = startNode;             //> coloca o nó inicial na primeira posição
  size_t current = startNode;        //> começa a partir do nó inicial
  double current_dist = 0.0;
  std::vector<bool> visited(city_qnt, false); //> vetor para marcar os nós visitados
  visited[startNode] = true;
  for (size_t i = 1; i < city_qnt; ++i) {
    size_t next = SIZE_MAX;                               // proximo nó a ser visitado
    double min_dist = std::numeric_limits<double>::max(); // gera um valor máximo para a distância mínima
    for (size_t j = 0; j < city_qnt; ++j) //> percorre todos os nós para encontrar o próximo nó mais próximo
    {
      if (not visited[j] and j != endNode) //> se o nó não foi visitado e não é o nó final
      {
        double d = (*paths)[current][j]; //> calcula a distância entre o nó atual e o nó j
        //> verifica se a distância é menor que a distância mínima encontrada até agora e se a distância total não
        //ultrapassa Tmax
        if (d < min_dist and current_dist + d + (*paths)[j][endNode] <= Tmax) {
          min_dist = d;
          next = j;
        }
      }
    }
    if (next == SIZE_MAX) break;

    v.path[i] = next;
    visited[next] = true;
    current_dist += min_dist;
    current = next;
  }
  if (paths && profits) {
    v.calc_score(paths, profits, endNode, Tmax, penaltyDelta);
  }
  return v;
}


/**
 * @brief Gera um indivíduo utilizando uma heurística gulosa aleatorizada.
 *
 * A rota é construída a partir do nó inicial, considerando uma lista de cidades
 * candidatas embaralhada aleatoriamente. A cada iteração, tenta-se inserir a
 * próxima cidade na sequência, aceitando-a apenas se a inclusão mantiver a
 * viabilidade da solução em relação ao limite de distância `Tmax`, incluindo o
 * custo de retorno ao nó final.
 *
 * Essa abordagem produz soluções iniciais diversas, combinando aleatoriedade na
 * ordem de avaliação com uma regra gulosa de viabilidade, o que ajuda a
 * explorar diferentes regiões do espaço de busca. Ao final, a pontuação e o
 * fitness do indivíduo são calculados.
 *
 * @param city_qnt Quantidade total de nós da instância.
 * @return Indivíduo gerado pela heurística gulosa aleatorizada.
 */
Individual Population::generate(const size_t city_qnt)
{
  Individual ind;
  ind.path.assign(city_qnt, SIZE_MAX);
  ind.path[0] = startNode;

  std::vector<size_t> available_cities;
  available_cities.reserve(city_qnt);
  for (size_t i = 0; i < city_qnt; ++i) {
    if (i != startNode && i != endNode) {
      available_cities.push_back(i);
    }
  }

  std::shuffle(available_cities.begin(), available_cities.end(), detail::tls_gen());

  size_t current_node = startNode;
  double current_dist = 0.0;
  size_t path_idx = 1;

  for (size_t next_city : available_cities) {
    if (path_idx >= city_qnt) break;

    double dist_to_next = (*paths)[current_node][next_city];
    double dist_to_end = (*paths)[next_city][endNode];

    if (current_dist + dist_to_next + dist_to_end <= Tmax) {
      ind.path[path_idx] = next_city;
      current_dist += dist_to_next;
      current_node = next_city;
      path_idx++;
    }
  }

  ind.calc_score(paths, profits, endNode, Tmax, penaltyDelta);

  return ind;
}


/**
 * @brief Gera e adiciona um indivíduo à população usando heurísticas ou opção configurada.
 *
 * Dependendo das opções em `RunningOptions`, a função pode gerar um indivíduo
 * usando diferentes heurísticas construtivas:
 *
 * - `allHeuristic`: executa simultaneamente múltiplas heurísticas
 *   (inserção, vizinho mais próximo e construção aleatória), escolhendo o
 *   indivíduo com maior fitness.
 * - `useGenNearestInsertion`: usa a heurística de inserção mais próxima.
 * - `useGenNearestNeighbor`: usa a heurística do vizinho mais próximo.
 * - Caso contrário: usa uma geração gulosa aleatorizada padrão.
 *
 * Quando `allHeuristic` está ativo, as heurísticas são executadas em paralelo
 * via `std::async`, e a melhor solução (maior fitness) é selecionada para
 * compor a população.
 *
 * @param city_qnt Número total de cidades da instância.
 * @param options Estrutura com opções de configuração da geração.
 */
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

/**
 * @brief Calcula a soma de todos os fitness dos indivíduos na população.
 *
 * Itera sobre cada indivíduo na população, somando seus valores de fitness
 * para atualizar o atributo `allFitness`, que representa a soma total de
 * fitness da população.
 */
void Population::processAllFitness()
{
  allFitness = 0;
  for (auto& ind : population) {
    allFitness += ind.fitness;
  }
}

/**
 * @brief Aplica elitismo para formar uma nova população.
 *
 * A nova população é inicialmente composta pelos indivíduos filhos. Em seguida,
 * os piores indivíduos dessa população são removidos com base no critério de
 * ordenação `betterScore`. Depois disso, os melhores indivíduos da população
 * atual (pais) são selecionados e inseridos na nova população, garantindo a
 * preservação das melhores soluções entre gerações.
 *
 * O método combina exploração (filhos) e preservação de elite (pais), mantendo
 * apenas os indivíduos de maior fitness.
 *
 * @param atual População atual (pais).
 * @param childs População gerada (filhos).
 * @return Nova população resultante do elitismo.
 */
std::vector<Individual> Population::elitism(const std::vector<Individual>& atual, const std::vector<Individual>& childs)
{
  std::vector<Individual> newPop = childs;

  std::nth_element(newPop.begin(), newPop.end() - populationSelectionQnt, newPop.end(), betterScore);

  for (size_t i{ 0 }; i < populationSelectionQnt; ++i) 
    newPop.pop_back();
  

  std::vector<const Individual*> ptrs;
  ptrs.reserve(atual.size());

  for (const auto& ind : atual) 
    ptrs.push_back(&ind);
  

  std::nth_element(ptrs.begin(),
                   ptrs.begin() + populationSelectionQnt,
                   ptrs.end(),
                   [](const Individual* a, const Individual* b) { return a->fitness > b->fitness; });

  for (size_t i{ 0 }; i < populationSelectionQnt; ++i) 
    newPop.push_back(*ptrs[i]);
  

  return newPop;
}


/**
 * @brief Aplica a estratégia de steady-state para atualização da população.
 *
 * A população atual é mantida como base, e seus piores indivíduos são
 * identificados. Em seguida, os melhores indivíduos da população de filhos
 * são selecionados e utilizados para substituir, quando superior, os piores
 * indivíduos da população atual.
 *
 * Essa estratégia promove uma evolução incremental, preservando boa parte da
 * população enquanto injeta melhorias pontuais geradas pelos filhos.
 *
 * @param atual População atual (pais).
 * @param childs População de indivíduos gerados (filhos).
 * @return Nova população após aplicação do steady-state.
 */
std::vector<Individual> Population::steadyState(const std::vector<Individual>& atual,
                                                const std::vector<Individual>& childs)
{
  std::vector<Individual> newPop = atual;

  std::nth_element(newPop.begin(), newPop.end() - populationSelectionQnt, newPop.end(), betterScore);

  std::vector<const Individual*> childPtrs;
  childPtrs.reserve(childs.size());
  for (const auto& c : childs) 
    childPtrs.push_back(&c);

  size_t kBest = std::min(populationSelectionQnt, childPtrs.size());
  std::partial_sort(childPtrs.begin(),
                    childPtrs.begin() + kBest,
                    childPtrs.end(),
                    [](const Individual* a, const Individual* b) { return a->fitness > b->fitness; });

  for (size_t i{ 0 }; i < populationSelectionQnt; ++i) 
  {
    Individual& worst = newPop[newPop.size() - populationSelectionQnt + i];

    if (i < kBest && childPtrs[i]->fitness > worst.fitness) 
        worst = *childPtrs[i];
  }

  return newPop;
}

/**
 * @brief Aplica a estratégia de mu-lambda para atualização da população.
 *
 * A nova população é formada inicialmente pelos indivíduos atuais (pais) e
 * pelos indivíduos filhos. Em seguida, todos os indivíduos são ordenados com
 * base no critério de aptidão (fitness), e os piores indivíduos são removidos
 * até que a população retorne ao tamanho original.
 *
 * Essa abordagem promove uma evolução mais agressiva, permitindo que os
 * melhores indivíduos sobrevivam independentemente de sua origem (pais ou
 * filhos).
 *
 * @param atual População atual (pais).
 * @param childs População de indivíduos gerados (filhos).
 * @return Nova população resultante da estratégia mu-lambda.
 */
std::vector<Individual> Population::muLambda(const std::vector<Individual>& atual,
                                             const std::vector<Individual>& childs)
{
  std::vector<Individual> newPop = atual;
  newPop.reserve(atual.size() + childs.size());
  newPop.insert(newPop.end(), childs.begin(), childs.end());

  std::sort(newPop.begin(), newPop.end(), betterScore);

  while (newPop.size() > atual.size()) 
    newPop.pop_back();

  return newPop;
}
/**
 * @brief Aplica mutação genética a um indivíduo.
 *
 * @param child Indivíduo a ser mutado.
 */
void Population::geneticMut(Individual& child)
{
  if (child.dist > Tmax) 
  {
    omit_a_point(child);
  } else {
    std::uniform_int_distribution<int> dist(0, 1);
    if (dist(detail::tls_gen()) == 0) 
      omit_a_point(child);
    else 
        add_a_point(child);
    
  }
}

/**
 * @brief Aplica mutação memética a um indivíduo.
 *
 * A mutação memética combina operações de mutação genética com estratégias
 * locais de otimização. Inicialmente, o indivíduo é compactado para remover
 * nós não visitados. Em seguida, uma operação aleatória (swap, shift ou invert)
 * é aplicada com probabilidade de 50%. Após isso, três estratégias locais são
 * executadas: omitir um ponto, adicionar um ponto e substituir um ponto,
 * cada uma sendo repetida 10 vezes para encontrar a melhor solução local.
 *
 * @param child Indivíduo a ser mutado.
 */
void Population::memeticMut(Individual& child)
{
  compact(child);
  std::uniform_real_distribution<double> rdist(0.0, 1.0);

  if (rdist(detail::tls_gen()) < 0.5) {
    std::uniform_int_distribution<int> op_dist(0, 2);
    int op = op_dist(detail::tls_gen());

    if (op == 0)
      swap(child);
    else if (op == 1)
      shift(child);
    else
      invert(child);

    child.calc_score(paths, profits, endNode, Tmax, penaltyDelta);
  }

  Individual best_omit = child;
  for (int i{ 0 }; i < 10; ++i) {
    Individual clone = child;
    omit_a_point(clone);
    compact(clone);
    clone.calc_score(paths, profits, endNode, Tmax, penaltyDelta);

    if (clone.fitness > best_omit.fitness) 
        best_omit = clone;
  }
  child = best_omit;

  Individual best_add = child;
  for (int i = 0; i < 10; ++i) {
    Individual clone = child;
    add_a_point(clone);
    compact(clone);
    clone.calc_score(paths, profits, endNode, Tmax, penaltyDelta);

    if (clone.fitness > best_add.fitness) 
      best_add = clone;
    
  }
  child = best_add;

  Individual best_replace = child;
  for (int i = 0; i < 10; ++i) {
    Individual clone = child;
    replace_a_point(clone);
    clone.calc_score(paths, profits, endNode, Tmax, penaltyDelta);

    if (clone.fitness > best_replace.fitness) 
      best_replace = clone;
    
  }
  child = best_replace;
}


/** @brief Aplica a operação de shift a um indivíduo.
 *  A operação de shift move um elemento da posição `posOld` para a posição `posNew` na rota do indivíduo,
 *  ajustando os elementos intermediários conforme necessário.
 * @param child Indivíduo a ser modificado.
 * @param posOld Posição original do elemento a ser movido.
 * @param posNew Posição final do elemento a ser movido.
 */
void Population::shift(Individual& child, size_t posOld, size_t posNew)
{
  const size_t n = usedVertices(child);

  if (posOld >= n || posNew >= n) 
    throw std::out_of_range("Population::shift(): invalid position");

  if (posOld == posNew) 
    return;

  if (posOld < posNew) 
    std::rotate(child.path.begin() + posOld, child.path.begin() + posOld + 1, child.path.begin() + posNew + 1);
  else 
    std::rotate(child.path.begin() + posNew, child.path.begin() + posOld, child.path.begin() + posOld + 1);
  

  child.calc_score(paths, profits, endNode, Tmax, penaltyDelta);
}


/**
 * @brief Aplica a operação de swap a um indivíduo.
 *
 * A operação de swap troca os elementos nas posições `pos1` e `pos2` na rota
 * do indivíduo. Se as posições forem iguais, nenhuma ação é realizada.
 *
 * @param child Indivíduo a ser modificado.
 * @param pos1 Primeira posição a ser trocada.
 * @param pos2 Segunda posição a ser trocada.
 */
void Population::swap(Individual& child, size_t pos1, size_t pos2)
{
  const size_t n = usedVertices(child);

  if (pos1 >= n || pos2 >= n) 
    throw std::out_of_range("Population::swap(): invalid position");

  if (pos1 == pos2) 
    return;

  std::swap(child.path[pos1], child.path[pos2]);

  child.calc_score(paths, profits, endNode, Tmax, penaltyDelta);
}

/**
 * @brief Aplica a operação de inversão a um indivíduo.
 *
 * A operação de inversão inverte a ordem dos elementos entre as posições `start` e `end` na rota
 * do indivíduo. Se as posições forem iguais, nenhuma ação é realizada.
 *
 * @param child Indivíduo a ser modificado.
 * @param start Posição inicial da subsequência a ser invertida.
 * @param end Posição final da subsequência a ser invertida.
 */
void Population::invert(Individual& child, size_t start, size_t end)
{
  const size_t n = usedVertices(child);

  if (start >= n || end >= n) 
    throw std::out_of_range("Population::invert(): invalid position");

  if (start > end) 
    std::swap(start, end);

  if (start == end) 
    return;

  std::reverse(child.path.begin() + start, child.path.begin() + end + 1);

  child.calc_score(paths, profits, endNode, Tmax, penaltyDelta);
}


/**
 * @brief Aplica a operação de shift a um indivíduo.
 *
 * A operação de shift move um elemento aleatório da rota do indivíduo para
 * uma nova posição aleatória, ajustando os elementos intermediários conforme
 * necessário. Se houver menos de dois elementos válidos na rota, nenhuma ação
 * é realizada.
 *
 * @param child Indivíduo a ser modificado.
 */
void Population::shift(Individual& child)
{
  std::vector<size_t> vp;
  for (size_t i = 1; i < child.path.size(); ++i)
    if (child.path[i] != SIZE_MAX) 
        vp.push_back(i);

  if (vp.size() < 2) 
    return;

  std::uniform_int_distribution<size_t> distrib(1, vp.size() - 1);
  size_t id = distrib(detail::tls_gen());
  size_t newid = distrib(detail::tls_gen());

  if (id == newid) 
    return;

  std::vector<size_t> cities;
  cities.reserve(vp.size());

  for (size_t i : vp) 
    cities.push_back(child.path[i]);

  if (id < newid)
    std::rotate(cities.begin() + id, cities.begin() + id + 1, cities.begin() + newid + 1);
  else
    std::rotate(cities.begin() + newid, cities.begin() + id, cities.begin() + id + 1);

  for (size_t i = 0; i < vp.size(); ++i) 
    child.path[vp[i]] = cities[i];
  
}

/**
 * @brief Aplica a operação de swap a um indivíduo.
 *
 * A operação de swap troca dois elementos aleatórios da rota do indivíduo.
 * Se houver menos de dois elementos válidos na rota, nenhuma ação é realizada.
 *
 * @param child Indivíduo a ser modificado.
 */
void Population::swap(Individual& child)
{
  std::vector<size_t> vp;
  for (size_t i = 1; i < child.path.size(); ++i)
    if (child.path[i] != SIZE_MAX) 
        vp.push_back(i);

  if (vp.size() < 2) 
    return;

  std::uniform_int_distribution<size_t> distrib(1, vp.size() - 1);
  size_t id1 = distrib(detail::tls_gen());
  size_t id2 = distrib(detail::tls_gen());

  std::swap(child.path[vp[id1]], child.path[vp[id2]]);
}


/**
 * @brief Aplica a operação de inversão a um indivíduo.
 *
 * A operação de inversão inverte a ordem de uma subsequência aleatória da
 * rota do indivíduo. Se houver menos de dois elementos válidos na rota, nenhuma
 * ação é realizada.
 *
 * @param child Indivíduo a ser modificado.
 */
void Population::invert(Individual& child)
{
  std::vector<size_t> vp;
  for (size_t i = 1; i < child.path.size(); ++i)
    if (child.path[i] != SIZE_MAX) 
        vp.push_back(i);

  if (vp.size() < 2) 
    return;

  std::uniform_int_distribution<size_t> distrib(1, vp.size() - 1);
  size_t start = distrib(detail::tls_gen());
  size_t end = distrib(detail::tls_gen());
  if (start > end) 
    std::swap(start, end);

  while (start < end) {
    std::swap(child.path[vp[start]], child.path[vp[end]]);
    start++;
    end--;
  }
}

/**
 * @brief Realiza um torneio entre indivíduos da população.
 *
 * Seleciona `qnt` indivíduos aleatórios da população e retorna o que possui a melhor aptidão.
 *
 * @param qnt Número de indivíduos a serem selecionados para o torneio.
 * @return Referência ao indivíduo vencedor do torneio.
 */
const Individual& Population::tournament(size_t qnt)
{
  std::uniform_int_distribution<size_t> distrib(0, population.size() - 1);
  size_t candidate = distrib(detail::tls_gen());

  for (size_t i{ 1 }; i < qnt; ++i) 
  {
    size_t challenger = distrib(detail::tls_gen());
    if (population[challenger].fitness > population[candidate].fitness) 
      candidate = challenger;
    
  }
  return population[candidate];
}

/**
 * @brief Seleciona um indivíduo aleatório da população.
 *
 * @param qnt Parâmetro não utilizado, mantido para compatibilidade de interface.
 * @return Referência ao indivíduo selecionado aleatoriamente.
 */
const Individual& Population::random_choice(size_t)
{
  std::uniform_int_distribution<size_t> distrib(0, population.size() - 1);
  return population[distrib(detail::tls_gen())];
}

/**
 * @brief Seleciona um indivíduo com base na roleta.
 *
 * @param qnt Parâmetro não utilizado, mantido para compatibilidade de interface.
 * @return Referência ao indivíduo selecionado pela roleta.
 */
const Individual& Population::roulette(size_t)
{
  std::uniform_real_distribution<double> fitDistrib(0.0, allFitness);
  double sortedv = fitDistrib(detail::tls_gen());
  double sum = 0.0;
  for (const auto& ind : population) {
    sum += ind.fitness;
    if (sum >= sortedv) 
      return ind;
    
  }
  return population.back();
}


/**
 * @brief Realiza o cruzamento entre dois indivíduos (pai e mãe) para gerar um filho.
 *
 * O método utiliza uma abordagem de cruzamento baseada na média do tamanho das rotas dos pais,
 * com uma variação aleatória. Inicialmente, o filho herda o nó inicial do pai. Em seguida,
 * são selecionadas cidades dos pais para compor a rota do filho, garantindo que não haja duplicatas.
 * Se necessário, cidades adicionais são escolhidas aleatoriamente para preencher a rota até atingir
 * o tamanho alvo.
 *
 * @param father Referência ao indivíduo pai.
 * @param mother Referência ao indivíduo mãe.
 * @return Indivíduo filho resultante do cruzamento.
 */
Individual Population::x1(const Individual& father, const Individual& mother)
{
  size_t size = father.path.size();
  Individual child;
  child.path.assign(size, SIZE_MAX);
  child.path[0] = father.path[0];

  std::vector<size_t> f_cities;
  std::vector<size_t> m_cities;
  f_cities.reserve(size);
  m_cities.reserve(size);
  for (size_t i = 1; i < size; ++i) {
    if (father.path[i] != SIZE_MAX) 
        f_cities.push_back(father.path[i]); 
    if (mother.path[i] != SIZE_MAX) 
        m_cities.push_back(mother.path[i]); 
  }
  size_t father_len = f_cities.size();
  size_t mother_len = m_cities.size();

  size_t avg_len = (father_len + mother_len) / 2;

  std::uniform_int_distribution<int> dist_delta(-2, 2);
  int target = static_cast<int>(avg_len) + dist_delta(detail::tls_gen());

  target = std::max(target, 1);
  if (target >= static_cast<int>(size)) target = size - 1;
  size_t target_len = static_cast<size_t>(target);

  std::vector<size_t> chosen_cities;
  chosen_cities.reserve(size);
  chosen_cities.push_back(father.path[0]);

  std::vector<int> in_child(size, 0);
  in_child[father.path[0]] = 1;

  if (father_len > 0) {
    std::uniform_int_distribution<size_t> distrib(0, father_len - 1);
    size_t start = distrib(detail::tls_gen());
    size_t end = distrib(detail::tls_gen());
    if (start > end) std::swap(start, end);

    for (size_t i = start; i <= end; ++i) {
      size_t city = f_cities[i];
      if (in_child[city] == 0) {
        chosen_cities.push_back(city);
        in_child[city] = 1;
      }
    }
  }

  if (chosen_cities.size() - 1 < target_len && mother_len > 0) {
    std::uniform_int_distribution<size_t> dist_m(0, mother_len - 1);
    size_t start_mother_idx = dist_m(detail::tls_gen());

    for (size_t i = 0; i < mother_len; ++i) {
      size_t idx = (start_mother_idx + i) % mother_len;
      size_t city = m_cities[idx];

      if (in_child[city] == 0) {
        chosen_cities.push_back(city);
        in_child[city] = 1;

        if (chosen_cities.size() - 1 >= target_len) break;
      }
    }
  }

  if (chosen_cities.size() - 1 < target_len) {
    std::vector<size_t> available_cities;
    available_cities.reserve(size);
    for (size_t c = 0; c < size; ++c)
      if (in_child[c] == 0 && c != startNode && c != endNode) available_cities.push_back(c);

    if (!available_cities.empty()) {
      std::shuffle(available_cities.begin(), available_cities.end(), detail::tls_gen());
      for (size_t city : available_cities) {
        chosen_cities.push_back(city);
        in_child[city] = 1;
        if (chosen_cities.size() - 1 >= target_len) break;
      }
    }
  }

  for (size_t i = 0; i < chosen_cities.size(); ++i) child.path[i] = chosen_cities[i];

  return child;
}

/**
 * @brief Compacta a rota de um indivíduo, removendo elementos inválidos.
 * Ele remove elementos com valor `SIZE_MAX` da rota do indivíduo, reorganizando os elementos válidos para ocupar as primeiras posições.
 * @param ind Indivíduo a ser compactado.
 */
void Population::compact(Individual& ind)
{
  std::vector<size_t> valid_cities;
  for (size_t i = 1; i < ind.path.size(); ++i) {
    if (ind.path[i] != SIZE_MAX) {
      valid_cities.push_back(ind.path[i]);
    }
  }
  for (size_t i = 1; i < ind.path.size(); ++i) {
    if (i - 1 < valid_cities.size()) {
      ind.path[i] = valid_cities[i - 1];
    } else {
      ind.path[i] = SIZE_MAX;
    }
  }
}

/**
 * @brief Retorna o indivíduo com o melhor fitness na população.
 *
 * Utiliza `std::max_element` para encontrar o indivíduo com o maior valor de fitness
 * na população. A função retorna uma referência constante para esse indivíduo.
 *
 * @return Referência constante para o indivíduo com o melhor fitness.
 */
const Individual& Population::getBest() const
{
  return *std::max_element(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
    return a.fitness < b.fitness;
  });
}

/**
 * @brief Substitui o indivíduo com o melhor fitness na população por um novo indivíduo.
 *
 * A função encontra o indivíduo com o maior valor de fitness na população e o substitui
 * pelo indivíduo fornecido como argumento. Se a população estiver vazia, a função não realiza nenhuma ação.
 *
 * @param best Referência constante para o novo indivíduo que substituirá o melhor da população.
 */
void Population::replaceBest(const Individual& best)
  {
    auto it = std::max_element(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
      return a.fitness < b.fitness;
    });
    if (it != population.end()) {
      *it = best;
    }
  }


/**
 * @brief Intensifica o indivíduo com o melhor fitness na população.
 *
 * A função encontra o indivíduo com o maior valor de fitness na população e aplica
 * a mutação memética repetidamente até que não haja mais melhorias ou até atingir
 * o número máximo de iterações especificado por `max_iter`. Se a população estiver
 * vazia, a função não realiza nenhuma ação.
 *
 * @param max_iter Número máximo de iterações para tentar melhorar o indivíduo.
 */
void Population::intensifyBest(int max_iter)
{
  if (population.empty()) return;

  auto it = std::max_element(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
    return a.fitness < b.fitness;
  });

  bool improved = true;
  int count = 0;
  while (improved && count < max_iter) {
    improved = false;
    Individual backup = *it;
    memeticMut(*it);
    it->calc_score(paths, profits, endNode, Tmax, penaltyDelta);
    if (it->fitness > backup.fitness) {
      improved = true;
    } else {
      *it = std::move(backup);
    }
    count++;
  }
}

/**
 * @brief Realiza a imigração de novos indivíduos na população.
 *
 * A função substitui os piores indivíduos da população por novos indivíduos gerados
 * aleatoriamente ou utilizando a heurística de inserção mais próxima, com base em uma
 * probabilidade de 30%. A imigração é realizada apenas se o valor de `immigration` for
 * maior que zero. Antes da substituição, a população é ordenada com base no fitness dos
 * indivíduos, garantindo que os piores sejam substituídos.
 *
 * @param city_qnt Quantidade total de nós da instância.
 */
void Population::imigrate(size_t city_qnt)
{
  if (immigration == 0) return;
  std::uniform_real_distribution<double> rDist(0.0, 1.0);
  std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
    return a.fitness > b.fitness;
  });

  for (size_t i = 0; i < immigration; ++i) {
    if (rDist(detail::tls_gen()) < 0.3)
      population[population.size() - 1 - i] = generate(city_qnt);
    else
      population[population.size() - 1 - i] = genNearestInsertion(city_qnt);
  }
}
};
``` 