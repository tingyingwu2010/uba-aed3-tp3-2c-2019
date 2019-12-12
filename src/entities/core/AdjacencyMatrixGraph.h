//
// Created by Christian nahuel Rivera on 6/10/19.
//

#ifndef TP2_MODELADO_CON_GRAFOS_ADYACENCYMATRIXGRAPH_H
#define TP2_MODELADO_CON_GRAFOS_ADYACENCYMATRIXGRAPH_H


#include "Graph.h"
#include "Dot.h"


class AdjacencyMatrixGraph : public Graph {
public:
    AdjacencyMatrixGraph();

    explicit AdjacencyMatrixGraph(std::vector<Dot> pVector);

    bool adyacent(int v1, int v2);

    int getVertex();

    long distance(int v1, int v2) override;

    std::vector<Edge> getEdges() override;

    //Tests:
    AdjacencyMatrixGraph(int size);
    void addEdge(int from, int to, Distancia weigth) override;

private:
    std::vector<std::vector<Distancia>> matrix;

    bool areEquivalent(int xi, int xj, int yi, int yj) const;

    inline Distancia getDistanceBetweenPoints(int xi, int xj, int yi, int yj) const;
};


#endif //TP2_MODELADO_CON_GRAFOS_ADYACENCYMATRIXGRAPH_H
