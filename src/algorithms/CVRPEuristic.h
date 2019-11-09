//
// Created by Christian nahuel Rivera on 7/11/19.
//

#ifndef TP3_HEURISTICAS_CVRP_CVRPEURISTIC_H
#define TP3_HEURISTICAS_CVRP_CVRPEURISTIC_H

#include "../entities/entrypoint/OutputCVRP.h"
#include "../entities/entrypoint/InputCVRP.h"

class CVRPEuristic{

public:
    virtual OutputCVRP * execute(InputCVRP input) = 0;
};
#endif //TP3_HEURISTICAS_CVRP_CVRPEURISTIC_H
