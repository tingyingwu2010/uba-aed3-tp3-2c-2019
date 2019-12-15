#pragma once

#include <string>

#include "Dot.h"

class Route;

class Station {
public:
    explicit Station(Dot dot) : dot(dot) {

    }

    // Index original del Station
    int index{};

    Dot dot;

    bool is_depot = false;

    // Pointers to next and previous (adjacent) stations.
    Station *next = nullptr;
    Station *prev = nullptr;

    // Pointer to the route this station belongs to.
    Route *route = nullptr;

    friend std::ostream &operator<<(std::ostream &os, const Station &s) {
        os << "{i: " << s.index << ", x: " << s.dot.x << ", y: " << s.dot.y << ", d: " << s.dot.expectedCapacity
           << ", D: " << s.is_depot << "}";
        return os;
    };

    friend class Route;
};