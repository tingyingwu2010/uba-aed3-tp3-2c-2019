#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "entities/entrypoint/InputCVRP.h"
#include "entities/entrypoint/OutputCVRP.h"
#include "entities/core/Route.h"
#include "entities/core/Station.h"
#include "CVRPHeuristic.h"
#include "utils/CVRP.h"

using namespace std;

class SavingsHeuristic : public CVRPHeuristic {
public:

    SavingsHeuristic() = default;

    ~SavingsHeuristic() override = default;

    typedef struct Saving {

        // Saving index.
        int i, j;

        // Estaciones del saving
        Station *station_i, *station_j;

        // Distancia i <---> j
        long dist_ij;

        // Savings de (i,j).
        long s_ij;

        friend std::ostream &operator<<(std::ostream &os, const Saving &s) {
            os << "{i: " << s.i << ", j: " << s.j << ", station_i: " << *s.station_i << ", station_j: " << *s.station_j;
            os << ", dist_ij: " << s.dist_ij << ", s_ij: " << s.s_ij;
            return os;
        };

        friend inline bool operator>(const Saving &l, const Saving &r) {
            return l.s_ij > r.s_ij;
        }

        friend inline bool operator<(const Saving &l, const Saving &r) {
            return l.s_ij < r.s_ij;
        }
    } Saving;

    static void Run(CVRP *graph);

    OutputCVRP *execute(InputCVRP *input) override;

};
