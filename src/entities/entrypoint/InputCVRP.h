#pragma once

#include <iostream>
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

    int getTotalCapacity();

    std::vector<int> getTotalCapacityVector();

    std::vector<std::pair<int, int>> GetOnlyPoints();

    friend std::ostream &operator<<(std::ostream &os, const InputCVRP &dt);

private:
    int vertex;
    int capacity;
    std::vector<Dot> vertexCordenates;

};
