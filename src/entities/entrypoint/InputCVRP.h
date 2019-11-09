//
// Created by Christian nahuel Rivera on 7/11/19.
//

#ifndef TP3_HEURISTICAS_CVRP_INPUTCVRP_H
#define TP3_HEURISTICAS_CVRP_INPUTCVRP_H


#include <vector>
#include "../core/Dot.h"

class InputCVRP {
public:
    int getVertex() const;

    void setVertex(int vertex);

    int getCapacity() const;

    void setCapacity(int capacity);

    const std::vector<Dot> &getVertexCordenates() const;

    void setVertexCordenates(const std::vector<Dot> &vertexCordenates);

private:
    int vertex;
    int capacity;
    std::vector<Dot> vertexCordenates;
};


#endif //TP3_HEURISTICAS_CVRP_INPUTCVRP_H
