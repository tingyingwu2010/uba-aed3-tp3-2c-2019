//
// Created by Christian nahuel Rivera on 12/12/19.
//

#pragma once

class StationCoordinate{
private:
    double radius;
    double angle;
    int stationIndex;

public:
    StationCoordinate(double radius, double angle, int station) : radius(radius), angle(angle), stationIndex(station) {}

    bool operator == (StationCoordinate const &obj) const{
        return radius == obj.getRadius() and angle == obj.getAngle() and stationIndex == obj.getStationIndex();
    }

    bool operator < (StationCoordinate const &obj) const{
        if(this->angle == obj.getAngle()){
            return this->radius < obj.getRadius();
        }else{
            return this->angle < obj.getAngle();
        }
    }

    double getRadius() const {
        return radius;
    }

    double getAngle() const {
        return angle;
    }

    int getStationIndex() const {
        return stationIndex;
    }
};
