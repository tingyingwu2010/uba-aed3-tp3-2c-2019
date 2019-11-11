#pragma once
#include "CVRPEuristic.h"

class GreedyEuristic : public CVRPEuristic{
public:
    OutputCVRP *execute(InputCVRP input) override;

};

