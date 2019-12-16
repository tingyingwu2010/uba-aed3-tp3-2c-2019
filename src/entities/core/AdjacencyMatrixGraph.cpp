//
// Created by Christian nahuel Rivera on 6/10/19.
//

#include "AdjacencyMatrixGraph.h"
#include <cmath>
#include "assert.h"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(std::vector<Dot> dots) {
    for(int iter = 0; iter < dots.size(); iter ++){
        matrix.emplace_back(std::vector<Distancia>(dots.size(), NotDefined));
    }

    for(int i = 0; i < dots.size(); i++){
        for(int j = i+1; j < dots.size(); j++){
            int xi = dots.at(i).x;
            int xj = dots.at(j).y;
            int yi = dots.at(i).x;
            int yj = dots.at(j).y;
            matrix[i][j] = getDistanceBetweenPoints(xi, xj, yi, yj);
            matrix[j][i] = getDistanceBetweenPoints(xi, xj, yi, yj);
        }
    }
}

Distancia AdjacencyMatrixGraph::getDistanceBetweenPoints(int xi, int xj, int yi, int yj) const {
    return sqrt(pow(xi - xj, 2) + pow(yi - yj, 2));
}

bool AdjacencyMatrixGraph::areEquivalent(int xi, int xj, int yi, int yj) const {
    return xi == xj && yi == yj;
}

std::vector<Edge> AdjacencyMatrixGraph::getEdges() {
    return std::vector<Edge>();
}

void AdjacencyMatrixGraph::addEdge(int from, int to, Distancia weigth) {}

bool AdjacencyMatrixGraph::adyacent(int v1, int v2) {
    return matrix.at(v1).at(v2) != NotDefined;
}

int AdjacencyMatrixGraph::getVertex() {
    return matrix.size();
}

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int size) {
    for(int iter = 0; iter < size; iter ++){
        matrix.emplace_back(std::vector<Distancia>(size, NotDefined));
    }
}

long AdjacencyMatrixGraph::distance(int v1, int v2) {
    assert(adyacent(v1,v2));
    return matrix.at(v1).at(v2);
}
