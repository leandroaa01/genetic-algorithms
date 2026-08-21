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

    // ---- Passo 1: mutação memética normal (1 cidade por vez) ----
    memeticMut(*it);
    it->calc_score(paths, profits, endNode, Tmax, penaltyDelta);

    if (it->fitness > backup.fitness) {
      improved = true;
    } else {
      *it = backup; // volta pro estado original antes de tentar o passo 2
    }

    // ---- Passo 2 (NOVO): se o passo 1 não achou nada, tenta uma
    //      perturbação maior (2-3 cidades de uma vez) ----
    if (!improved) {
      Individual ruinCandidate = backup;
      std::uniform_int_distribution<int> ruinSizeDist(2, 3);
      ruinAndRecreate(ruinCandidate, ruinSizeDist(detail::tls_gen()));

      if (ruinCandidate.fitness > backup.fitness) {
        *it = std::move(ruinCandidate);
        improved = true;
      }
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

// population.cpp — substitui a versão anterior de tryGrow.
// Diferença chave: em vez de reusar add_a_point (que sorteia UMA cidade
// aleatória e só decide a posição), aqui avaliamos TODAS as cidades ainda
// não visitadas em TODAS as posições possíveis, e inserimos a que tiver
// o menor detour (aumento de distância) que ainda caiba em Tmax. Isso é
// uma heurística de "cheapest feasible insertion" clássica.
void Population::tryGrow(Individual& ind)
{
  bool grew = true;

  while (grew) {
    grew = false;
    compact(ind);

    size_t valid_count = 0;
    std::vector<bool> present(paths->size(), false);
    for (size_t p : ind.path) {
      if (p != SIZE_MAX) {
        present[p] = true;
        ++valid_count;
      }
    }
    if (valid_count == 0 || valid_count >= ind.path.size()) break;

    std::vector<size_t> missing;
    for (size_t c = 0; c < paths->size(); ++c) {
      if (!present[c] && c != startNode && c != endNode) missing.push_back(c);
    }
    if (missing.empty()) break;

    double bestDetour = std::numeric_limits<double>::max();
    size_t bestCity = SIZE_MAX;
    size_t bestPos = valid_count;

    for (size_t city : missing) {
      for (size_t i = 0; i < valid_count; ++i) {
        size_t u = ind.path[i];
        size_t v = (i + 1 < valid_count) ? ind.path[i + 1] : endNode;
        double detour = (*paths)[u][city] + (*paths)[city][v] - (*paths)[u][v];

        if (ind.dist + detour <= Tmax && detour < bestDetour) {
          bestDetour = detour;
          bestCity = city;
          bestPos = i + 1;
        }
      }
    }

    if (bestCity != SIZE_MAX) {
      for (size_t i = ind.path.size() - 1; i > bestPos; --i) {
        ind.path[i] = ind.path[i - 1];
      }
      ind.path[bestPos] = bestCity;
      ind.calc_score(paths, profits, endNode, Tmax, penaltyDelta);
      grew = true;   // conseguiu inserir -> tenta de novo (pode caber mais uma)
    }
    // se bestCity == SIZE_MAX, nenhuma cidade cabe no orçamento restante -> para
  }
}
void Population::ruinAndRecreate(Individual& child, int ruinCount)
{
  compact(child);
  size_t used = usedVertices(child);

  if (used <= 2) return; // não há o que arrancar além do start

  std::vector<size_t> removablePositions;
  for (size_t i = 1; i < used; ++i) {
    removablePositions.push_back(i); // nunca inclui a posição 0 (start)
  }

  int actualRuin = std::min<int>(ruinCount, static_cast<int>(removablePositions.size()));
  if (actualRuin <= 0) return;

  std::shuffle(removablePositions.begin(), removablePositions.end(), detail::tls_gen());
  std::vector<size_t> toRemove(removablePositions.begin(), removablePositions.begin() + actualRuin);

  // remove do fim pro início pra não invalidar os índices já calculados
  std::sort(toRemove.rbegin(), toRemove.rend());

  for (size_t pos : toRemove) {
    for (size_t i = pos; i + 1 < child.path.size(); ++i) {
      child.path[i] = child.path[i + 1];
    }
    child.path[child.path.size() - 1] = SIZE_MAX;
  }

  child.calc_score(paths, profits, endNode, Tmax, penaltyDelta);

  // reconstrução gulosa: reaproveita o tryGrow que já existe
  tryGrow(child);
}

};