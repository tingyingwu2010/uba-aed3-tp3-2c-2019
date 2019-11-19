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

std::ostream& operator<<(std::ostream &os, const InputCVRP &dt) {
  os << "InputCVRP: \nCapacity: " << dt.getCapacity() << " | Depot vertex: " << dt.getVertex() << std::endl;
  os << "Coordinates list: [ " << dt.getVertexCordenates()[0];
  for (int i = 1; i < dt.getVertexCordenates().size(); i++) {
    os << ", " << "" << dt.getVertexCordenates()[i];
  }
  os << " ] \n";
  return os;
}