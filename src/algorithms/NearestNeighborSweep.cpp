//
// Created by Christian nahuel Rivera on 15/12/19.
//

#include <entities/core/VertexCoordinate.h>
#include <algorithms/utils/MakePolarCoordenatesCenteredInDepot.h>
#include <entities/core/AdjacencyMatrixGraph.h>
#include <entities/core/Constants.h>
#include "NearestNeighborSweep.h"
#include "NearestNeighborSweepClustering.h"
#include "NearestNeighborTsp.h"

OutputCVRP *NearestNeighborSweep::execute(InputCVRP *input) {
    std::vector<StationCoordinate> * stationCoordinates = MakePolarCoordenatesCenteredInDepot::execute(&input->getVertexCordenates());

    std::vector<std::vector<int>> *clusters = NearestNeighborSweepClustering::execute(stationCoordinates, &input->getVertexCordenates(),
                                           input->getCapacity());

    Graph* graph = new AdjacencyMatrixGraph(input->getVertexCordenates());

    auto rutas = new std::vector<std::vector<int>>();
    for(auto cluster : *clusters){

        auto stationsToConnect = new std::vector<bool>(input->getVertex(),false);
        for(int index : cluster){
            stationsToConnect->at(index) = true;
        }

        std::vector<int> path =  NearestNeighborTsp::execute(*stationsToConnect, graph);

        for(int index = 1; index <path.size(); index++){
            path.at(index) += 1;
        }
        path.emplace_back(DEPOSITO);

        rutas->emplace_back(path);
    }

    auto capacidades = new std::vector<int>();
    for(auto dot : input->getVertexCordenates()){
        capacidades->emplace_back(dot.expectedCapacity);
    }

    return new OutputCVRP(*rutas, *capacidades);
}
