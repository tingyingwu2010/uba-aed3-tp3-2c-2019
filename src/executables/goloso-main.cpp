//
// Created by Christian nahuel Rivera on 11/11/19.
//

#include "../utils/io.hpp"
#include "../utils/util.hpp"
#include "../entities/core/AdyacencyMatrixGraph.h"

int main(){
    InputCVRP *inputCVRP = input_from_python();

    Graph* grafo = new AdyacencyMatrixGraph(inputCVRP->getVertexCordenates());
    std::vector<int> *capacities = vectorDeCapacidades(inputCVRP->getVertexCordenates());

    /**
     * Tu código
     */

    OutputCVRP *outputCVRP;

    print(*outputCVRP);

    return 0;
}