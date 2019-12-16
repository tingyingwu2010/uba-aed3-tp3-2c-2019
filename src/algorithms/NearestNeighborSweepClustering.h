//
// Created by Christian nahuel Rivera on 14/12/19.
//

#ifndef TP3_HEURISTICAS_CVRP_NEARESTNEIGHTBORSWEEPCLUSTERING_H
#define TP3_HEURISTICAS_CVRP_NEARESTNEIGHTBORSWEEPCLUSTERING_H


#include <vector>
#include <entities/core/VertexCoordinate.h>
#include <entities/core/Dot.h>

class NearestNeighborSweepClustering {
public:
    static std::vector<std::vector<int>> *execute(std::vector<StationCoordinate> *stations,
                                                  const std::vector<Dot> *dots,
                                                  long capacity);
};


#endif //TP3_HEURISTICAS_CVRP_NEARESTNEIGHTBORSWEEPCLUSTERING_H
