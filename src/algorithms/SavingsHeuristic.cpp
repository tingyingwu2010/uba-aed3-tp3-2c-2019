#include "SavingsHeuristic.h"
#include "utils/QuickSort.h"

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
    }

    graph->DeleteRoute(source);

    // Retornamos el index de la ruta destino.
    return destination->index;
}

int MergeRoutes(
        CVRP *graph,
        SavingsHeuristic::Saving &s,
        int capacity) {

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

        route_index = UpdateRoute(graph, a, b, (route_i_size >= route_j_size), s);

        // Agregar eje (linkear estaciones, pisando el default)
        CVRP::LinkStations(i, j);

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
                s);

        // Agregar eje (linkear estaciones, pisando el default)
        CVRP::LinkStations(j, i);
    }
    return route_index;
}

int CalcSavings(CVRP *graph, SavingsHeuristic::Saving *savings) {
    long savings_index = 0;
    long dist_ij = 0;
    long dist_Di = 0;
    long dist_Dj = 0;

    Station *depot = graph->GetDepot();

    std::vector<Station *>::iterator it;
    std::vector<Station *>::iterator jt;

    it = graph->stations.begin();
    it++;

    for (; it != graph->stations.end(); it++) {
        // Distancia entre depot e i
        dist_Di = CVRP::CalculateDistance(
                depot->dot,
                (*it)->dot);
        jt = it;
        jt++;

        for (; jt != graph->stations.end(); jt++) {
            // Distancia entre i y j
            dist_ij = CVRP::CalculateDistance(
                    (*it)->dot,
                    (*jt)->dot);

            // Distancia entre depot y j.
            dist_Dj = CVRP::CalculateDistance(
                    depot->dot,
                    (*jt)->dot);

            // Calcular los savings y almacenarlos
            savings[savings_index].i = (*it)->index - 1;
            savings[savings_index].station_i = *it;
            savings[savings_index].j = (*jt)->index - 1;
            savings[savings_index].station_j = *jt;
            savings[savings_index].dist_ij = dist_ij;
            savings[savings_index].s_ij = (dist_Di + dist_Dj - dist_ij);

            savings_index++;
        }
    }

    return 0;
}

void InitRoutes(CVRP *graph) {

    Station *depot = graph->GetDepot();

    std::vector<Station *>::iterator it;

    it = graph->stations.begin();
    it++;

    for (; it != graph->stations.end(); it++) {

        // Linkear el estado incial de las rutas: (depot, i) --- (i, depot)
        CVRP::LinkStations(depot, *it);
        CVRP::LinkStations(*it, depot);

        // Agregar ruta al grafo
        Route *route_info = graph->AddRoute(
                (*it)->dot.expectedCapacity,
                2 * CVRP::CalculateDistance(
                        depot->dot,
                        (*it)->dot),
                (*it),
                (*it));

        // Asignamos la instancia de la ruta a la estacion i.
        CVRP::AddToRoute(*it, route_info);
    }
}

void SavingsHeuristic::Run(CVRP *graph) {
    long savings_size = ((graph->num_stations * graph->num_stations) - ((3 * graph->num_stations) - 2)) / 2;
    auto *savings = (SavingsHeuristic::Saving *) calloc(savings_size, sizeof(SavingsHeuristic::Saving));

    // 1 - Para cada par (i, j) calcular savings: s(i, j) = d(D, i) + d(D, j) - d(i, j)
    CalcSavings(graph, savings);

    // 2 - Ordenar savings por valor
    QuickSort::Sort(savings, 0, savings_size - 1);

    // 3 - Inicializar rutas con (depot, i, depot)
    InitRoutes(graph);

    // 4 - Mergear rutas (SavingsHeuristic magic)
    for (long i = 0; i < (savings_size); i++) {
        MergeRoutes(
                graph,
                savings[i],
                graph->capacity);
    }

    int total_cost = 0;
    std::list<Route *>::iterator it;

    for (it = graph->routes.begin(); it != graph->routes.end(); it++) {
        total_cost += graph->TwoOptExchange(*it);
    }

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