//
// Created by Christian nahuel Rivera on 7/11/19.
//

#ifndef TP3_HEURISTICAS_CVRP_SAVINGSEURISTIC_H
#define TP3_HEURISTICAS_CVRP_SAVINGSEURISTIC_H

#include "CVRPEuristic.h"

class SavingsEuristic : public CVRPEuristic{
public:
    OutputCVRP *execute(InputCVRP input) override;

};


#endif //TP3_HEURISTICAS_CVRP_SAVINGSEURISTIC_H
