#pragma once

#include "CVRPHeuristic.h"
#include "entities/entrypoint/OutputCVRP.h"
#include "entities/entrypoint/InputCVRP.h"
#include "entities/core/Graph.h"
#include "entities/core/AdjacencyMatrixGraph.h"

class GreedyHeuristic : public CVRPHeuristic {
public:
    GreedyHeuristic() = default;

    ~GreedyHeuristic() override = default;

    OutputCVRP *execute(InputCVRP *input) override;

    OutputCVRP *greedySolution(std::vector<int> capacities, Graph *grafo, int size, int capacity);

    std::vector<int> nearestVecino(Graph *grafo, int size);

    int minimoCercano(int node, std::vector<bool> &visited, Graph *grafo, int size);

    std::vector<int> *vectorDeCapacidades(std::vector<Dot> dots);
};
