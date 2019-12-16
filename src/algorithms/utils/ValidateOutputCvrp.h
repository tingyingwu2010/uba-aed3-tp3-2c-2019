//
// Created by Christian nahuel Rivera on 11/12/19.
//

#pragma once

#include <entities/entrypoint/OutputCVRP.h>
#include <entities/entrypoint/InputCVRP.h>

class ValidateOutputCvrp {
public:
    static bool validate(OutputCVRP* outputCVRP, InputCVRP* inputCVRP);

    static bool allDotsInOnlyOnePath(std::vector<std::vector<int>> caminos, int dotsSize);
    static bool allPathsBeginAndEndInDepot(std::vector<std::vector<int>> caminos);
    static bool anyPathWeightIsBiggerThanCapacity(std::vector<std::vector<int>> caminos, std::vector<Dot> vertexCordenates, int capacity);

private:
    static bool allVisited(std::vector<bool> visited);
    static long weightOfPath(std::vector<int> camino, std::vector<Dot> cordenates);
};