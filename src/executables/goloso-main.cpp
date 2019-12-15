//
// Created by Christian nahuel Rivera on 11/11/19.
//

#include "../utils/io.hpp"
#include "../utils/util.hpp"
#include "entities/core/AdjacencyMatrixGraph.h"

int main(){
    InputCVRP *inputCVRP = input_from_python();

    Graph* grafo = new AdjacencyMatrixGraph(inputCVRP->getVertexCordenates());
    std::vector<int> *capacities = vectorDeCapacidades(inputCVRP->getVertexCordenates());

    /**
     * Tu código
     */

    OutputCVRP *outputCVRP;

    print(*outputCVRP);

    return 0;
}