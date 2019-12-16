#pragma once

#include "CVRPHeuristic.h"

class NearestNeighborAGM : public CVRPHeuristic {
public:
    OutputCVRP *execute(InputCVRP *input) override;

    std::vector<bool> *makeVector(std::vector<int> vector);
};
