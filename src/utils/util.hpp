//
// Created by Christian nahuel Rivera on 11/11/19.
//

#pragma once

#include <vector>
#include "../entities/core/Dot.h"

std::vector<int> *vectorDeCapacidades(std::vector<Dot> dots){
    auto *result = new std::vector<int>();

    for(auto dot : dots){
        result->push_back(dot.expectedCapacity);
    }

    return result;
}
