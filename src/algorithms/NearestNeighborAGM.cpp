#include <entities/legacy/entities/AdyacencyMatrixGraph.h>
#include <entities/core/Constants.h>
#include <entities/legacy/algoritmos/Segmentation.h>
#include "NearestNeighborAGM.h"
#include "NearestNeighborTsp.h"

OutputCVRP *NearestNeighborAGM::execute(InputCVRP *input) {
    auto points = input->GetOnlyPoints();

    Segmentation segmentation;
    std::vector<int> clusterized_dots = segmentation.execute(&points, input->getVertex(), input->getCapacity());

    int clusters_n = 0;
    for (int clusterized_dot : clusterized_dots) {
        if (clusterized_dot > clusters_n)
            clusters_n = clusterized_dot;
    }
    std::vector<std::vector<int>> clusters(clusters_n, std::vector<int>());
    for (int i = 0; i < clusters.size(); i++) {
        clusters[clusterized_dots[i]].push_back(i);
    }

    Graph *graph = new AdyacencyMatrixGraph(&points);
    auto rutas = new std::vector<std::vector<int>>();
    for (const auto &cluster : clusters) {
        auto stationsToConnect = new std::vector<bool>(input->getVertex(), false);
        for (int index : cluster) {
            stationsToConnect->at(index) = true;
        }
        std::vector<int> path = NearestNeighborTsp::execute(*stationsToConnect, graph);
        for (int index = 1; index < path.size(); index++) {
            path.at(index) += 1;
        }
        path.emplace_back(DEPOSITO);
        rutas->emplace_back(path);
    }
    return new OutputCVRP(*rutas, input->getTotalCapacityVector());
}
