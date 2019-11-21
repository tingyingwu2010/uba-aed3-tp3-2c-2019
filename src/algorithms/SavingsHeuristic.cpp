#include "SavingsHeuristic.h"
#include "utils/QuickSort.h"

/**
 * Updatear ruta
 * Complexity: O(V)
 *
 * @param graph
 * @param destination
 * @param source
 * @param merge_right
 * @param s
 * @return
 */
int UpdateRoute(
        CVRP *graph,
        Route *destination,
        Route *source,
        bool merge_right,
        SavingsHeuristic::Saving s) {

    // Demanda total usada en la ruta
    destination->qty_supplied += source->qty_supplied;

    // Calculamos la distancia
    destination->distance += source->distance - s.s_ij;

    // Actualizamos el estado del grafo (distancias)
    graph->total_distance += -s.s_ij;

    destination->num_stations += source->num_stations;

    if (merge_right) {
        destination->end_station = source->end_station;
    } else {
        destination->start_station = source->start_station;
    }

    Station *curr_station = source->end_station;

    while (!curr_station->is_depot) {
        curr_station->route = destination;
        curr_station = curr_station->prev;
    } // Peor caso O(V)

    graph->DeleteRoute(source);

    // Retornamos el index de la ruta destino.
    return destination->index;
}

/**
 * Mergear rutas
 * Complexity: O(V)
 *
 * @param graph
 * @param s
 * @param capacity
 * @return
 */
int MergeRoutes(CVRP *graph, SavingsHeuristic::Saving &s, int capacity) {

    Station *i = s.station_i;
    Station *j = s.station_j;

    // Error si estamos en la misma ruta
    if (i->route->index == j->route->index) {
        return -1;
    }

    int route_i_qty_supplied = i->route->qty_supplied;
    int route_j_qty_supplied = j->route->qty_supplied;

    // Nos queda capacity?
    if ((route_i_qty_supplied + route_j_qty_supplied) > capacity) {
        return -1;
    }

    int route_i_size = i->route->num_stations;
    int route_j_size = j->route->num_stations;
    int route_index = -1;

    if (CVRP::GetNextStation(i)->is_depot && CVRP::GetPrevStation(j)->is_depot) {
        Route *a = i->route;
        Route *b = j->route;
        if (route_j_size > route_i_size) {
            b = i->route;
            a = j->route;
        }
        route_index = UpdateRoute(graph, a, b, (route_i_size >= route_j_size), s); // O(V)

        // Agregar eje (linkear estaciones, pisando el default)
        CVRP::LinkStations(i, j); // O(1)
    } else if (CVRP::GetNextStation(j)->is_depot
               && CVRP::GetPrevStation(i)->is_depot) {

        Route *a = i->route;
        Route *b = j->route;
        if (route_i_size < route_j_size) {
            b = i->route;
            a = j->route;
        }

        route_index = UpdateRoute(
                graph,
                a,
                b,
                (route_i_size < route_j_size),
                s); // O(V)

        // Agregar eje (linkear estaciones, pisando el default)
        CVRP::LinkStations(j, i); // O(1)
    }
    return route_index;
}

/**
 * Calcular savings para todos los vertices del grafo
 * Complextiy: O(V^2 / 2) | ( (V^2 - (3*V) + 2) / 2 )
 * @param graph Grafo sobre el cual operar
 * @param savings Savings
 * @return
 */
int CalcSavings(CVRP *graph, SavingsHeuristic::Saving *savings) {
    long savings_index = 0;
    long dist_ij = 0;
    long dist_Di = 0;
    long dist_Dj = 0;

    Station *depot = graph->GetDepot();

    std::vector<Station *>::iterator it;
    std::vector<Station *>::iterator jt;

    it = graph->stations.begin();
    it++; // O(1) hasta aca

    for (; it != graph->stations.end(); it++) {
        // Distancia depot <---> i
        dist_Di = CVRP::CalculateDistance(
                depot->dot,
                (*it)->dot);
        jt = it;
        jt++;

        for (; jt != graph->stations.end(); jt++) {
            // Distancia i <---> j
            dist_ij = CVRP::CalculateDistance(
                    (*it)->dot,
                    (*jt)->dot);

            // Distancia depot <---> j.
            dist_Dj = CVRP::CalculateDistance(
                    depot->dot,
                    (*jt)->dot);

            // Calcular savings
            savings[savings_index].i = (*it)->index - 1;
            savings[savings_index].station_i = *it;
            savings[savings_index].j = (*jt)->index - 1;
            savings[savings_index].station_j = *jt;
            savings[savings_index].dist_ij = dist_ij;
            savings[savings_index].s_ij = (dist_Di + dist_Dj - dist_ij);

            savings_index++; // All O(1) actions
        } // O(V - i)
    }  // O(V^2 / 2)

    return 0;
}

/**
 * Inicializar rutas
 * Complexity: O(V)
 *
 * @param graph
 */
void InitRoutes(CVRP *graph) {
    Station *depot = graph->GetDepot();
    std::vector<Station *>::iterator it;

    it = graph->stations.begin();
    it++;

    for (; it != graph->stations.end(); it++) {

        // Linkear el estado incial de las rutas: (depot, i) --- (i, depot)
        CVRP::LinkStations(depot, *it); // O(1)
        CVRP::LinkStations(*it, depot); // O(1)

        // Agregar ruta al grafo
        Route *route_info = graph->AddRoute(
                (*it)->dot.expectedCapacity,
                2 * CVRP::CalculateDistance(
                        depot->dot,
                        (*it)->dot),
                (*it),
                (*it)); // O(1)

        // Asignamos la instancia de la ruta a la estacion i.
        CVRP::AddToRoute(*it, route_info); // O(1)
    } // O(V)
}

void SavingsHeuristic::Run(CVRP *graph) {
    // ( (V^2 - (3*V) + 2) / 2 ) ---> V * (V-3) / 2 + 1
    long savings_size = ((graph->num_stations * graph->num_stations) - ((3 * graph->num_stations) - 2)) / 2;
    auto *savings = (SavingsHeuristic::Saving *) calloc(savings_size, sizeof(SavingsHeuristic::Saving));

    // 1 - Para cada par (i, j) calcular savings: s(i, j) = d(D, i) + d(D, j) - d(i, j)
    CalcSavings(graph, savings); // O(V^2 / 2)

    // 2 - Ordenar savings por valor
    QuickSort::Sort(savings, 0, savings_size - 1); // O((V^2 / 2) log (V^2 / 2))

    // 3 - Inicializar rutas con (depot, i, depot)
    InitRoutes(graph); // O(V)

    // 4 - Mergear rutas (SavingsHeuristic magic)
    for (long i = 0; i < (savings_size); i++) {
        MergeRoutes(
                graph,
                savings[i],
                graph->capacity); // O(V)
    } // O(V * V^2 / 2) ---> O(V^3 / 2)

    int total_cost = 0;
    std::list<Route *>::iterator it;

    for (it = graph->routes.begin(); it != graph->routes.end(); it++) {
        total_cost += graph->TwoOptExchange(*it); // O(V^3)
    } // O(V^4) --> Puede llegar a existir una ruta por vertice

    free(savings);
}

OutputCVRP *SavingsHeuristic::execute(InputCVRP *input) {
    CVRP cvrp(input);

    this->Run(&cvrp);

    auto *output = new OutputCVRP();

    output->setCantidadDeCamiones(cvrp.routes.size());
    output->setCostoSolucion(cvrp.total_distance);
    output->setCaminos(cvrp.GetRoutesVector());

    return output;
}