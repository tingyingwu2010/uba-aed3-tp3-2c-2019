#pragma once

#include <cerrno>
#include <climits>
#include <cmath>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "utils/CVRP.h"
#include "CVRPHeuristic.h"

class SimulatingAnnealingHeuristic : public CVRPHeuristic {

public:

    SimulatingAnnealingHeuristic();

    ~SimulatingAnnealingHeuristic() override;

    typedef struct CoolingScheduleParams {
        double T_s;
        double T_f;
        uint32_t alpha;
        uint32_t gamma;
        int R;
    } CoolingScheduleParams;

    static void Run(CVRP *graph, double cooling_rate, uint32_t L, uint16_t stop_n, bool debug=false);

    OutputCVRP *execute(InputCVRP *input) override;
};
