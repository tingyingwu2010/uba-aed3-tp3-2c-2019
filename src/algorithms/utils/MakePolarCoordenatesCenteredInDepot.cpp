//
// Created by Christian nahuel Rivera on 12/12/19.
//

#include <cmath>
#include "MakePolarCoordenatesCenteredInDepot.h"

std::vector<StationCoordinate> * MakePolarCoordenatesCenteredInDepot::execute(const std::vector<Dot> *dots){
    auto depotX = dots->at(0).x;
    auto depotY = dots->at(0).y;

    auto results = new std::vector<StationCoordinate>();
    results->emplace_back(StationCoordinate(0,0,0));

    for(int index = 1; index < dots->size(); index++){
        auto dotXcentered = dots->at(index).x - depotX;
        auto dotYcentered = dots->at(index).y - depotY;

        double dotRadius = std::sqrt( std::pow(dotXcentered,2) + std::pow(dotYcentered,2) );
        double dotAngle = getAngle(dotXcentered, dotYcentered);

        results->emplace_back(StationCoordinate( dotRadius, dotAngle, index));
    }

    return results;
}

double MakePolarCoordenatesCenteredInDepot::getAngle(int dotXcentered, int dotYcentered) {
    double angle = atan2(dotYcentered, dotXcentered) * MakePolarCoordenatesCenteredInDepot::toDegress();

    if(dotYcentered < 0){
        angle += 360.0;
    }

    return angle;
}
