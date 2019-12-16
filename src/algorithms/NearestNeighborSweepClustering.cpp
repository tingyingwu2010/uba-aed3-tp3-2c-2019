//
// Created by Christian nahuel Rivera on 14/12/19.
//
#include <algorithm>

#include "NearestNeighborSweepClustering.h"

std::vector<std::vector<int>> *NearestNeighborSweepClustering::execute(std::vector<StationCoordinate> *stations,
                                                                       const std::vector<Dot> *dots,
                                                                       long capacity) {
    std::sort(stations->begin(), stations->end());

    auto clusters = new std::vector<std::vector<int>>();
    auto cluster = std::vector<int>();
    long clusterCapacity = 0;
    for(int stationIndex = 1; stationIndex< stations->size(); stationIndex++){
        int stationCapacity = dots->at(stations->at(stationIndex).getStationIndex()).expectedCapacity;

        if(stationCapacity + clusterCapacity > capacity){
            clusters->emplace_back(cluster);

            cluster = std::vector<int>();
            clusterCapacity = 0;
        }

        cluster.emplace_back(stations->at(stationIndex).getStationIndex());
        clusterCapacity += stationCapacity;
    }

    if( !cluster.empty() ) clusters->emplace_back(cluster);

    return clusters;
}
