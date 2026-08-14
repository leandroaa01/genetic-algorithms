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
