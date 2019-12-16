//
// Created by Christian nahuel Rivera on 10/12/19.
//

#include <entities/core/Constants.h>
#include "NearestNeighborTsp.h"

std::vector<int> NearestNeighborTsp::execute(std::vector<bool> verticesAAnalizar, Graph *graph) {
    std::vector<int> cycle;
    cycle.push_back(DEPOSITO);

    std::vector<bool> visited(graph->getVertex(), false);
    setAsVisited(visited, verticesAAnalizar);
    visited[0] = true;

    int node = DEPOSITO;
    while(anyToVisit(visited, verticesAAnalizar)) {
        int min_vecino = nearestNeigthbour(node, visited, graph, graph->getVertex(), verticesAAnalizar);
        cycle.push_back(min_vecino);
        node = min_vecino;
        visited[node] = true;
    }

    return cycle;
}

// busco el minimo mas cercano a node mientras no este visitado
int NearestNeighborTsp::nearestNeigthbour(int node, std::vector<bool> &visited, Graph *grafo, int size,
                                           std::vector<bool> verticesAAnalizar) {
    int minV = node;
    int min_dist = __INT_MAX__;
    for (int index = 1; index < size; index++) {
        if ( verticesAAnalizar.at(index) and !visited[index] and index != node) {
            if (grafo->distance(node, index) < min_dist) {
                minV = index;
                min_dist = grafo->distance(node, index);
            }
        }
    }

    return minV;
}

void NearestNeighborTsp::setAsVisited(std::vector<bool> visitados, std::vector<bool> analizar) {
    for(int index = 0; index < analizar.size(); index++){
        if(! analizar.at(index)){
            visitados.at(index) = true;
        }
    }
}

bool NearestNeighborTsp::anyToVisit(std::vector<bool> vector, std::vector<bool> aAnalizar) {
    for(int vectorIndex = 0; vectorIndex < vector.size(); vectorIndex++){
        if(aAnalizar.at(vectorIndex) and ! vector.at(vectorIndex)){
            return true;
        }
    }
    return false;
}
