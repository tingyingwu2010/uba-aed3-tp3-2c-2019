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

    bool is_depot{};

    // Pointers to next and previous (adjacent) stations.
    Station *next{};
    Station *prev{};

    // Pointer to the route this station belongs to.
    Route *route{};

    friend std::ostream &operator<<(std::ostream &os, const Station &s) {
        os << "{i: " << s.index << ", x: " << s.dot.x << ", y: " << s.dot.y << ", d: " << s.dot.expectedCapacity
           << "}";
        return os;
    };

    friend class Route;
};