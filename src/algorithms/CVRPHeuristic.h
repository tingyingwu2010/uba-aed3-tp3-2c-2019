#pragma once

#include "entities/entrypoint/OutputCVRP.h"
#include "entities/entrypoint/InputCVRP.h"

class CVRPHeuristic {

public:
    CVRPHeuristic() = default;

    virtual ~CVRPHeuristic() = default;

    virtual OutputCVRP *execute(InputCVRP *input) = 0;
};
