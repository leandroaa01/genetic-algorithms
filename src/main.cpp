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
         vec<std::pair<int, Population>>&& times = {})
{
    times.resize(20);
    times.assign(20, std::pair<int, Population>{ 0, Population{} });
    for (size_t i{ 0 }; i < 20; ++i) 
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
Usage: Mahl [<options>] 

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
  -s, --seed <value>                   Set the random seed (default: 0)
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
    } else if (std::strcmp(argv[i], "-seed") == 0 or std::strcmp(argv[i], "--seed") == 0) {
      if (i + 1 < argc) {
        options.seed = static_cast<unsigned>(std::stoul(argv[++i]));
      }
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

  if (options.seed != 0) {
    detail::tls_gen().seed(options.seed);
  }

  Run(popSize, N, options, gaPop, std::move(result), std::move(times));


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

  // Machine-readable metric for automated tuning (irace expects a single numeric value).
  // irace minimizes by default; this program maximizes 'score', so we output the negative.
  std::cout << "IRACE_RESULT: " << std::fixed << std::setprecision(6) << -bestPop.getBest().score << "\n";

  
  return 0;
}