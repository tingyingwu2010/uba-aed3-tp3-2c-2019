//
// Created by Christian nahuel Rivera on 11/11/19.
//

#include "../utils/util.hpp"
#include "../entities/core/AdyacencyMatrixGraph.h"
#include "../entities/entrypoint/InputCVRP.h"
#include "../entities/entrypoint/OutputCVRP.h"
#include "../utils/AlgorithmMain.h"

int main(){
    InputCVRP *inputCVRP = AlgorithmMain::input_from_python();

    Graph* grafo = new AdyacencyMatrixGraph(inputCVRP->getVertexCordenates());
    std::vector<int> *capacities = vectorDeCapacidades(inputCVRP->getVertexCordenates());

    /**
     * Tu código
     */

    OutputCVRP *outputCVRP;

    AlgorithmMain::print(*outputCVRP);

    return 0;
}