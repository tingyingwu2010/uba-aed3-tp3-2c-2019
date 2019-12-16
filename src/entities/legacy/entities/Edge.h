#pragma once
#include "Utils.h"

class Edge {
public:
    Edge(int v1, int v2, Distancia weight);

    int getFromVertex() const;

    int getToVertex() const;

    Distancia getWeight() const;

    bool operator<(const Edge& edge)const;

    bool operator==(Edge edge)const;

private:
    int fromVertex;
    int toVertex;
    Distancia weight;

};

