#pragma once

#include <string>
#include <ostream>

#include "Station.h"

class Route {
public:
    Route()= default;
    ~Route()= default;

    int index;
    int qty_supplied;
    int num_stations;

    long distance;

    Station *start_station;
    Station *end_station;

    friend std::ostream &operator<<(std::ostream &os, const Route &r) {
        Station *current_station = r.start_station;
        if (current_station == nullptr) {
            return os;
        }
        os << "[ " << *current_station;
        current_station = current_station->next;

        while (current_station->next != nullptr) {
            os << ", " << *current_station;
            current_station = current_station->next;
        }
        return os;
    };

    friend class Station;
};
