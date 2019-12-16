//
// Created by Christian nahuel Rivera on 15/12/19.
//

#ifndef TP3_HEURISTICAS_CVRP_NEARESTNEIGHBORSWEEP_H
#define TP3_HEURISTICAS_CVRP_NEARESTNEIGHBORSWEEP_H


#include "CVRPHeuristic.h"

class NearestNeighborSweep : public CVRPHeuristic {
public:
    OutputCVRP *execute(InputCVRP *input) override;


    std::vector<bool> *makeVector(std::vector<int> vector);
};


#endif //TP3_HEURISTICAS_CVRP_NEARESTNEIGHBORSWEEP_H
