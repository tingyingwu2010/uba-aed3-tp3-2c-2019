//
// Created by Christian nahuel Rivera on 10/12/19.
//

#pragma once

#include <vector>
#include "entities/core/Graph.h"

class NearestNeighborTsp {
public:
    static std::vector<int> execute(std::vector<bool> verticesAAnalizar, Graph *graph);

private:
    static int nearestNeigthbour(int node, std::vector<bool> &visited, Graph *grafo, int size,
                                 std::vector<bool> verticesAAnalizar);

    static void setAsVisited(std::vector<bool> visitados, std::vector<bool> analizar);

    static bool anyToVisit(std::vector<bool> vector, std::vector<bool> aAnalizar);
};