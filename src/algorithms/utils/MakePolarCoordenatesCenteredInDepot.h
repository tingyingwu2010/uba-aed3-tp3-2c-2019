//
// Created by Christian nahuel Rivera on 12/12/19.
//

#pragma once

#define _USE_MATH_DEFINES

#include <entities/core/VertexCoordinate.h>
#include <entities/core/Dot.h>
#include <vector>
#include <cmath>

class MakePolarCoordenatesCenteredInDepot {
public:
    static std::vector<StationCoordinate> * execute(const std::vector<Dot> *dots);

    static double pi(){ return M_PI;}

    static double toDegress(){ return 180.0/pi();}

    static double getAngle(int dotXcentered, int dotYcentered);
};