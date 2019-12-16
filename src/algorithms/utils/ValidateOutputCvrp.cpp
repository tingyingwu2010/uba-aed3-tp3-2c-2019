//
// Created by Christian nahuel Rivera on 11/12/19.
//

#include <entities/core/Constants.h>
#include "ValidateOutputCvrp.h"

bool ValidateOutputCvrp::allDotsInOnlyOnePath(std::vector<std::vector<int>> caminos, int dotsSize){
    auto visited = std::vector<bool>(dotsSize+1, false);
    visited.at(0) = true;
    visited.at(DEPOSITO) = true;

    for(auto camino : caminos){
        for(auto vertice : camino){
            if(vertice != DEPOSITO and visited.at(vertice)){
                return false;
            }
            visited.at(vertice) = true;
        }
    }

    return allVisited(visited);
}

bool ValidateOutputCvrp::allVisited(std::vector<bool> visited){
    for(auto vertex : visited){
        if( !vertex ){
            return false;
        }
    }

    return true;
}

bool ValidateOutputCvrp::allPathsBeginAndEndInDepot(std::vector<std::vector<int>> caminos){
    for(auto camino : caminos){
        if( camino.size() < 3)
            return false;

        if(! (camino.at(0) == DEPOSITO and camino.at(camino.size()-1) == DEPOSITO) )
            return false;
    }

    return true;
}

bool ValidateOutputCvrp::anyPathWeightIsBiggerThanCapacity(std::vector<std::vector<int>> caminos, std::vector<Dot> vertexCordenates, int capacity){
    for(auto camino : caminos){
        if(weightOfPath(camino, vertexCordenates) > capacity){
            return false;
        }
    }

    return true;
}

long ValidateOutputCvrp::weightOfPath(std::vector<int> camino, std::vector<Dot> cordenates) {
    long peso = 0;
    for(auto vertice : camino){
        peso += cordenates.at(vertice-1).expectedCapacity;
    }
    return peso;
}

bool ValidateOutputCvrp::validate(OutputCVRP *outputCVRP, InputCVRP *inputCVRP) {
    return ValidateOutputCvrp::allDotsInOnlyOnePath(outputCVRP->getCaminos(),inputCVRP->getVertexCordenates().size()) and
            ValidateOutputCvrp::allPathsBeginAndEndInDepot(outputCVRP->getCaminos()) and
            ValidateOutputCvrp::anyPathWeightIsBiggerThanCapacity(outputCVRP->getCaminos(), inputCVRP->getVertexCordenates(), inputCVRP->getCapacity());
}
