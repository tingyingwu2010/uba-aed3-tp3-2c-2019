//
// Created by Christian nahuel Rivera on 7/11/19.
//

#include "InputCVRP.h"

int InputCVRP::getVertex() const {
    return vertex;
}

void InputCVRP::setVertex(int vertex) {
    InputCVRP::vertex = vertex;
}

int InputCVRP::getCapacity() const {
    return capacity;
}

void InputCVRP::setCapacity(int capacity) {
    InputCVRP::capacity = capacity;
}

const std::vector<Dot> &InputCVRP::getVertexCordenates() const {
    return vertexCordenates;
}

void InputCVRP::setVertexCordenates(const std::vector<Dot> &vertexCordenates) {
    InputCVRP::vertexCordenates = vertexCordenates;
}
