#include <entities/core/Constants.h>
#include "GreedyHeuristic.h"
#include "NearestNeighborTsp.h"

OutputCVRP *GreedyHeuristic::greedySolution(std::vector<int> capacities, Graph *grafo, int size, int capacity) {
    std::vector<int> cycle_route = NearestNeighborTsp::execute(std::vector<bool>(size,true), grafo);
    cycle_route.pop_back();

    std::vector<std::vector<int> > routes;
    int next_c = 1;

    while (next_c < size - 1) {
        std::vector<int> new_route;
        new_route.push_back(DEPOSITO);

        bool is_route = true;

        int suma_demanda = 0;

        while (is_route) {
            suma_demanda += capacities[cycle_route[next_c]];

            if (suma_demanda <= capacity) {
                new_route.push_back(cycle_route[next_c] + 1);
                next_c++;
            }

            is_route = (suma_demanda <= capacity && next_c < size);
        }
        new_route.push_back(DEPOSITO);

        routes.push_back(new_route);
    }

    OutputCVRP *salida = new OutputCVRP(routes, capacities);

    return salida;
}

//circuito Hamiltonio para definir ruta principal/ ciclo


OutputCVRP *GreedyHeuristic::execute(InputCVRP *input) {
    Graph *grafo = new AdjacencyMatrixGraph(input->getVertexCordenates());
    std::vector<int> *capacities = vectorDeCapacidades(input->getVertexCordenates());
    OutputCVRP *outputCVRP = greedySolution(*capacities, grafo, grafo->getVertex(), input->getCapacity());
    return outputCVRP;
}

std::vector<int> *GreedyHeuristic::vectorDeCapacidades(std::vector<Dot> dots){
    auto *result = new std::vector<int>();

    for(auto dot : dots){
        result->push_back(dot.expectedCapacity);
    }

    return result;
}

