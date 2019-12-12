#include "GreedyHeuristic.h"

OutputCVRP *GreedyHeuristic::greedySolution(std::vector<int> capacities, Graph *grafo, int size, int capacity) {
    std::vector<int> cycle_route = nearestVecino(grafo, size);

    std::vector<std::vector<int> > routes;
    int next_c = 1;

    while (next_c < size - 1) {
    	if (capacities[cycle_route[next_c]] > capacity)
    	{
    		next_c++;
    	}
    	else
    	{
        	std::vector<int> new_route;
        	new_route.push_back(1);

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
        	new_route.push_back(1);

        	routes.push_back(new_route);
    	}
    }   

    int suma_costo = 0;
    for (int i = 0; i < routes.size(); i++) {
        for (int j = 1; j < routes[i].size(); j++) {
            suma_costo += grafo->distance(routes[i][j - 1] - 1, routes[i][j] - 1);
        }
    }

    OutputCVRP *salida = new OutputCVRP();

    salida->setCaminos(routes);
    salida->setCantidadDeCamiones(routes.size());
    salida->setCostoSolucion(suma_costo);

    return salida;
}

//circuito Hamiltonio para definir ruta principal/ ciclo
std::vector<int> GreedyHeuristic::nearestVecino(Graph *grafo, int size) {
    std::vector<int> cycle;
    std::vector<bool> visited(size, false);
    visited[0] = true;
    cycle.push_back(0);

    int i = 0;
    int node = 0;
    while (i < size - 1) {
        int min_vecino = minimoCercano(node, visited, grafo, size);
        cycle.push_back(min_vecino);
        node = min_vecino;
        visited[node] = true;
        i++;
    }

    return cycle;
}

// busco el minimo mas cercano a node mientras no este visitado
int GreedyHeuristic::minimoCercano(int node, std::vector<bool> &visited, Graph *grafo, int size) {
    int minV = node;
    int min_dist = __INT_MAX__;
    for (int i = 1; i < size; i++) {
        if (!visited[i] && i != node) {
            if (grafo->distance(node, i) < min_dist) {
                minV = i;
                min_dist = grafo->distance(node, i);
            }
        }
    }

    return minV;
}

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

