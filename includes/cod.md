// ============================================================
// 1) population.hpp — dentro de "public:", junto dos outros
//    métodos de mutação/reparo:
// ============================================================
//
//   void ruinAndRecreate(Individual&, int ruinCount = 2);


// ============================================================
// 2) population.cpp — novo método
// ============================================================
//
// Remove `ruinCount` cidades aleatórias da rota (nunca o startNode,
// posição 0) e reconstrói gulosamente com tryGrow(), que já busca a
// melhor inserção possível entre TODAS as cidades faltantes. Isso
// permite escapar de mínimos locais que add_a_point/omit_a_point/
// replace_a_point (que só mexem 1 cidade por vez) não conseguem ver.
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


// ============================================================
// 3) population.cpp — intensifyBest atualizado
//    (só a parte de dentro do while muda; a assinatura e o
//    max_element continuam iguais)
// ============================================================
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