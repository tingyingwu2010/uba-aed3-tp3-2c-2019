#include <stdexcept>
#include <climits>

#include "CVRP.h"

CVRP::CVRP() {
    this->num_stations = 0;
    this->num_routes = 0;
    this->total_distance = 0;
    this->capacity = 0;
    this->depot = nullptr;
}

CVRP::CVRP(InputCVRP *dataset) {
    this->num_stations = 0;
    this->num_routes = 0;
    this->total_distance = 0;
    this->capacity = dataset->getCapacity();
    this->depot = nullptr;

    for (int i = 0; i < dataset->getVertexCordenates().size(); i++) {
        Dot dot = dataset->getVertexCordenates()[i];
        this->AddStation(i + 1, dot, dot.expectedCapacity == 0);
    }

    if (this->num_stations != dataset->getVertexCordenates().size()) {
        throw std::runtime_error("num_stations must equal getVertexCoordinates");
    }

}


CVRP::~CVRP() {
    this->num_stations = 0;
    this->num_routes = 0;
    this->total_distance = 0;
    this->capacity = 0;

    this->depot = nullptr;

    // Limpiar stations
    std::vector<Station *>::iterator it;
    for (it = this->stations.begin(); it != this->stations.end(); it++) {
        delete (*it);
    }
    this->stations.clear();

    // Limpiar routes
    std::list<Route *>::iterator rt;
    for (rt = this->routes.begin(); rt != this->routes.end();) {
        delete (*rt);
        rt = this->routes.erase(rt);
    }
}

long CVRP::CalculateDistance(Dot i, Dot j) {
    long x_distance = i.x - j.x;
    long y_distance = i.y - j.y;
    return (long) ceil(sqrt((x_distance * x_distance) + (y_distance * y_distance)));
}

long CVRP::CalculateDistance(Station *i, Station *j) {
    return CalculateDistance(i->dot, j->dot);
}

Station *CVRP::AddStation(
        int index,
        Dot dot,
        bool is_depot) {

    auto *new_station = new Station(dot);

    new_station->index = index;
    new_station->is_depot = is_depot;

    // Actualizar grafo
    this->stations.push_back(new_station);
    this->num_stations++;
    if (new_station->is_depot) {
        if (this->depot != nullptr) {
            throw std::runtime_error("Only depot's demand can be 0");
        }
        this->depot = new_station;
    }

    return new_station;
}

Station *CVRP::GetNextStation(Station *station) {
    return station->next;
}

Station *CVRP::GetPrevStation(Station *station) {
    return station->prev;
}

void CVRP::LinkStations(Station *start, Station *end) {
    if (!start->is_depot && !end->is_depot) {
        Station *next_station = start->next;
        next_station->prev = nullptr;
        Station *previous_station = end->prev;
        previous_station->next = nullptr;
    }
    start->next = end;
    end->prev = start;
}

Station *CVRP::GetDepot() {
    return this->depot;
}

Route *CVRP::AddRoute(
        int qty_supplied,
        long distance,
        Station *start_station,
        Station *end_station) {

    auto *new_route = new Route;
    new_route->index = this->routes.size();
    new_route->qty_supplied = qty_supplied;
    new_route->distance = distance;
    new_route->num_stations = 0;
    new_route->start_station = start_station;
    new_route->end_station = end_station;

    this->total_distance += distance;
    this->routes.push_back(new_route);

    Station *i = start_station;
    while (!i->is_depot) {
        new_route->num_stations++;
        i = i->next;
    }
    return new_route;
}

void CVRP::DeleteRoute(Route *route) {
    this->routes.remove(route);
    delete route;
}

Route *CVRP::AddToRoute(Station *station, Route *route) {
    station->route = route;
    return station->route;
}

vector<vector<int>> CVRP::GetRoutesVector(bool include_depot) {
    std::list<Route *>::iterator it;
    vector<vector<int>> routes_vector(this->routes.size());

    int i = 0;
    for (it = this->routes.begin(); it != this->routes.end(); it++) {
        Station *current_station = (*it)->start_station;
        if (include_depot) routes_vector[i].push_back(this->depot->index);
        do {
            routes_vector[i].push_back(current_station->index);
            current_station = current_station->next;
        } while (!current_station->is_depot);
        if (include_depot) routes_vector[i].push_back(this->depot->index);
        i++;
    }
    return routes_vector;
}

long CVRP::SwapStations(Station *i, Station *j, int stations_qty) {

    Station *prev_i, *next_j, *aux, *pos_i, *pos_j, *k, *l;

    long new_distance = +i->route->distance + CalculateDistance(i->prev, j) + CalculateDistance(i, j->next) -
                        CalculateDistance(i->prev, i) - CalculateDistance(j, j->next);

    prev_i = i->prev;
    next_j = j->next;

    prev_i->next = j;
    next_j->prev = i;

    if (prev_i->is_depot) {
        i->route->start_station = j;
    } else if (next_j->is_depot) {
        i->route->end_station = i;
    }

    pos_i = i->next;
    pos_j = j->prev;
    i->prev = pos_i;
    i->next = next_j;
    j->next = pos_j;
    j->prev = prev_i;

    int m = 0;

    while (m++ < ((stations_qty / 2))) {

        k = pos_i->next;
        l = pos_j->prev;

        aux = pos_i->prev;
        pos_i->prev = pos_i->next;
        pos_i->next = aux;

        if (pos_i == pos_j)
            break;

        aux = pos_j->next;
        pos_j->next = pos_j->prev;
        pos_j->prev = aux;

        pos_i = k;
        pos_j = l;
    }

    this->total_distance += (new_distance - i->route->distance);
    i->route->distance = new_distance;

    return i->route->distance;
}

long CVRP::SwapStations(Station *i, Route *route_i, Station *j, Route *route_j) {
    Station *before_i = i->prev;
    Station *after_i = i->next;
    Station *before_j = j->prev;
    Station *after_j = j->next;

    /*printf("SWAP: %3d->next = %3d %3d->prev = %3d\n",
            i->index, i->next->index, i->index, i->prev->index);

    printf("SWAP: %3d->next = %3d %3d->prev = %3d\n",
            j->index, j->next->index, j->index, j->prev->index);*/

    // 1) Update the pointers of the elements before and after i and j
    before_i->next = j;
    after_i->prev = j;

    before_j->next = i;
    after_j->prev = i;

    // 2) Update the prev and next pointers of i and j.
    i->prev = before_j;
    i->next = after_j;

    // 2.1) Update i's route to route_j.
    i->route = route_j;

    // 2.2) If i is the new starting point of route j, update it.
    if (i->prev->is_depot)
        i->route->start_station = i;

    // 2.3) Similarly, if the last station...
    if (i->next->is_depot)
        i->route->end_station = i;

    j->prev = before_i;
    j->next = after_i;

    j->route = route_i;

    if (j->prev->is_depot)
        j->route->start_station = j;

    if (j->next->is_depot)
        j->route->end_station = j;

    /*printf("SWAP: %3d->next = %3d %3d->prev = %3d\n",
            i->index, i->next->index, i->index, i->prev->index);

    printf("SWAP: %3d->next = %3d %3d->prev = %3d\n",
            j->index, j->next->index, j->index, j->prev->index);*/

    // 3) New distances for route_i and route_j.
    /*long new_i_distance =
        + route_i->distance
        + CVRP::Euc2DistCalc(before_i, j)
        + CVRP::Euc2DistCalc(j, after_i)
        - CVRP::Euc2DistCalc(before_j, j)
        - CVRP::Euc2DistCalc(j, after_j);

    long new_j_distance =
        + route_j->distance
        + CVRP::Euc2DistCalc(before_j, i)
        + CVRP::Euc2DistCalc(i, after_j)
        - CVRP::Euc2DistCalc(before_i, i)
        - CVRP::Euc2DistCalc(i, after_i);*/

    long new_j_distance = CVRP::CalcRouteDist(route_j);
    long new_i_distance = CVRP::CalcRouteDist(route_i);

    this->total_distance +=
            +new_i_distance
            + new_j_distance
            - route_i->distance
            - route_j->distance;

    /*printf("SWAP: TOTAL DISTANCE BEFORE 2-OPT: %ld\n",
            this->total_distance);*/

    /*printf("SWAP: TOTAL DISTANCE: %ld \n\n",
            this->total_distance);*/

    // 3.1) Route i
    route_i->distance = new_i_distance;

    // 3.2) Route j
    route_j->distance = new_j_distance;

    // 3.3) Also, update the demand quantities served in each route.
    i->route->qty_supplied += (i->dot.expectedCapacity - j->dot.expectedCapacity);
    j->route->qty_supplied += (j->dot.expectedCapacity - i->dot.expectedCapacity);

    return this->total_distance;
}

long CVRP::TwoOptExchange(Route *route) {
    long best_distance = route->distance;
    long new_distance;

    // TODO: resolver mejor esto
    auto **route_stations = (Station **) calloc(route->num_stations + 2, sizeof(Station *));
    Station *curr_route_station = route->start_station;

    for (int i = 1; i < route->num_stations + 2; i++) {
        route_stations[i] = curr_route_station;
        curr_route_station = curr_route_station->next;
    }

    // Setear extremos
    route_stations[0] = depot;
    route_stations[route->num_stations + 1] = depot;

    Station *aux = nullptr;

    // Arrancar salteando 0 y n-1
    for (int i = 1; i < route->num_stations - 1; i++) {
        for (int j = (i + 1); j < route->num_stations; j++) {
            // Sirve intercambiar dos Stations?
            new_distance = +route->distance + CVRP::CalculateDistance(route_stations[i - 1], route_stations[j]) +
                           CVRP::CalculateDistance(route_stations[i], route_stations[j + 1]) -
                           CVRP::CalculateDistance(route_stations[i - 1], route_stations[i]) -
                           CVRP::CalculateDistance(route_stations[j], route_stations[j + 1]);

            if (new_distance < best_distance) {
                // Actualizamos grafo y ruta
                this->SwapStations(route_stations[i], route_stations[j], j - i);
                int m = i;
                for (int k = j; k > m; k--) {
                    aux = route_stations[k];
                    route_stations[k] = route_stations[m];
                    route_stations[m++] = aux;
                }
                best_distance = new_distance;
            }
        }
    }
    free(route_stations);
    return best_distance;
}

void CVRP::CopyFrom(CVRP *graph) {

    // General graph attributes.
    this->num_stations = graph->num_stations;
    this->num_routes = graph->num_routes;
    this->capacity = graph->capacity;
    this->total_distance = graph->total_distance;

    // Create a Station object representing the depot.

    Dot depot_dot = Dot(graph->depot->dot.x, graph->depot->dot.y, graph->depot->dot.expectedCapacity);
    auto *depot_ptr = new Station(depot_dot);

    // All the remaining elements are NULL
    depot_ptr->index = graph->depot->index;
    depot_ptr->next = nullptr;
    depot_ptr->prev = nullptr;
    depot_ptr->route = nullptr;
    depot_ptr->is_depot = true;

    this->depot = depot_ptr;

    // For the lists, let's actually create copies of the Station and Route
    // objects pointed by list elements.

    // 1) Erase the previous Station elements.
    std::vector<Station *>::iterator it;

    for (it = this->stations.begin(); it != this->stations.end(); it++) {
        delete (*it);
    }

    this->stations.clear();

    // 2) Erase the previous Route elements.
    std::list<Route *>::iterator rt;

    for (rt = this->routes.begin(); rt != this->routes.end();) {
        delete (*rt);
        rt = this->routes.erase(rt);
    }
    this->stations.push_back(this->depot);

    // 3) Start by copying the Routes and copy the Station objects as you
    // cycle through each route.
    for (rt = graph->routes.begin(); rt != graph->routes.end(); rt++) {
        auto *route = new Route();

        route->index = (*rt)->index;
        route->qty_supplied = (*rt)->qty_supplied;
        route->num_stations = (*rt)->num_stations;
        route->distance = (*rt)->distance;

        Station *curr_station = (*rt)->start_station;
        Station *prev_station = this->depot;
        Station *station;

        while (!curr_station->is_depot) {
            Dot station_dot = Dot(curr_station->dot.x, curr_station->dot.y, curr_station->dot.expectedCapacity);
            station = new Station(station_dot);

            // All the remaining elements are NULL
            station->next = nullptr;
            station->prev = nullptr;
            station->route = nullptr;

            // Copy the elements.
            station->index = (curr_station)->index;
            station->is_depot = (curr_station)->is_depot;
            station->route = route;

            // Make the prev pointer of the new Station object to
            // point to prev_station.
            station->prev = prev_station;

            // Make the next pointer of prev_station point to
            // this new Station object.
            if (prev_station->is_depot) {
                route->start_station = station;
            } else {
                prev_station->next = station;
            }

            // If the next station of the graph being copied is the
            // depot, make the new Station's next pointer point to its depot.
            if (curr_station->next->is_depot) {
                station->next = this->depot;
                route->end_station = station;
            }

            // Add the new object to the Station vector.
            this->stations.push_back(station);

            // Advance.
            prev_station = station;
            curr_station = curr_station->next;
        }
        // Add the new route to the Route list.
        this->routes.push_back(route);
    }
}

long CVRP::CalcRouteDist(Route *rt) {
    long distance = 0;
    Station *curr_station = (rt)->start_station;

    while (!curr_station->next->is_depot) {
        distance += CalculateDistance(curr_station->prev, curr_station);
        curr_station = curr_station->next; // Advance.
    }
    distance += CalculateDistance(curr_station->prev, curr_station);
    distance += CalculateDistance(curr_station, curr_station->next);
    return distance;
}


Station **CVRP::CreateRouteRep(Route *route) {
    auto **route_stations = (Station **) calloc(
            route->num_stations + 2,
            sizeof(Station *));

    Station *curr_route_station = route->start_station;

    // Just a reference to the graph's depot.
    Station *depot_station = this->GetDepot();

    for (int i = 1; i < route->num_stations + 2; i++) {
        route_stations[i] = curr_route_station;
        curr_route_station = curr_route_station->next;
    }

    // Set the edges of the array to point to the depot.
    route_stations[0] = depot_station;
    route_stations[route->num_stations + 1] = depot_station;
    return route_stations;
}

long CVRP::InsertIntoRoute(Station *i, Route *route_j, Station *j) {

    // P.1) If i is the depot, abort.
    if (i->is_depot) {
        printf("INSERT: Station[%d] is the depot. ABORTING.\n", i->index);
        return -1;
    }

    // P.2) If j is the depot, abort.
    if (j->is_depot) {
        printf("INSERT: Station[%d] is the depot. ABORTING.\n", j->index);
        return -1;
    }

    // P.3) Also, let's avoid depleting route_i.
    Route *route_i = i->route;

    if (route_i->num_stations < 2) {
        printf("INSERT: Route[%d] is too small. ABORTING.\n", i->route->index);
        return -1;
    }

    // 1.1) Pointers to the Stations [i - 1] and [i + 1].
    Station *before_i = i->prev;
    Station *after_i = i->next;

    // 1.2) Pointer to the Station [j + 1].
    Station *after_j = j->next;

    // 2.1) Update the pointers of elements [j] and [j + 1], in route_j.
    j->next = i;

    if (!after_j->is_depot)
        after_j->prev = i;

    // 2.2) Update the pointers of elements [i - 1] and [i + 1], in route_i.
    if (!before_i->is_depot)
        before_i->next = after_i;

    if (!after_i->is_depot)
        after_i->prev = before_i;

    // 2.3) Update the prev and next pointers of i.
    i->prev = j;
    i->next = after_j;

    // 3.1) Update the route of i.
    i->route = route_j;

    // 3.2) If i is the new starting point of route_j, update it.
    if (i->prev->is_depot)
        i->route->start_station = i;

    // 3.3) Similarly, if the last station...
    if (i->next->is_depot)
        i->route->end_station = i;

    // 3.4) Do the same with route_i.
    if (before_i->is_depot)
        route_i->start_station = after_i;

    if (after_i->is_depot)
        route_i->end_station = before_i;

    // 4) Update distances.
    /*long new_j_distance =
            + route_j->distance
            + CVRP::Euc2DistCalc(j, i)
            + CVRP::Euc2DistCalc(i, after_j)
            - CVRP::Euc2DistCalc(j, after_j);

    long new_i_distance =
            + route_i->distance
            + CVRP::Euc2DistCalc(before_i, after_i)
            - CVRP::Euc2DistCalc(before_i, i)
            - CVRP::Euc2DistCalc(i, after_i);*/
    long new_j_distance = this->CalcRouteDist(route_j);
    long new_i_distance = this->CalcRouteDist(route_i);

    /*printf("INSERT: i(%ld,%ld) j(%ld,%ld) total(%ld)\n",
            route_i->distance, new_i_distance,
            route_j->distance, new_j_distance,
            this->total_distance);*/

    this->total_distance +=
            +new_i_distance
            + new_j_distance
            - route_i->distance
            - route_j->distance;

    /*printf("INSERT: TOTAL DISTANCE BEFORE 2-OPT: %ld\n",
            this->total_distance);*/

    // 4.1) Route j
    route_j->distance = new_j_distance;

    // 4.2) Route i
    route_i->distance = new_i_distance;

    // 4.4) Also, update the demand quantities served in each route.
    i->route->qty_supplied += i->dot.expectedCapacity;
    route_i->qty_supplied -= i->dot.expectedCapacity;

    // 4.5) ... aaaaand the number of stations.
    i->route->num_stations++;
    route_i->num_stations--;

    //this->PrintRoutes();

    return this->total_distance;
}


long CVRP::OneInterchange(CVRP::IChange &ichange) {

    /*printf("1-INTERCHANGE W/ PARAMS: "\
            "\n\tstation[%d] = %d"\
            "\n\tstation[%d] = %d"\
            "\n\troute[%d] = %d"\
            "\n\troute[%d] = %d"\
            "\n\tOP = %d"\
            "\n\t[DISTANCE (OR.)] = %ld"\
            "\n\t[DISTANCE (NEW)] = %ld\n\n",
            ichange.i, stations[ichange.i]->index - 1,
            ichange.j, stations[ichange.j]->index - 1,
            ichange.i, stations[ichange.i]->route->index,
            ichange.j, stations[ichange.j]->route->index,
            ichange.operation,
            this->total_distance,
            ichange.distance);*/

    Station *station_i = this->stations[ichange.i];
    Station *station_j = this->stations[ichange.j];

    Route *route_i = this->stations[ichange.i]->route;
    Route *route_j = this->stations[ichange.j]->route;

    int qty_supplied_i = 0;
    int qty_supplied_j = 0;

    int demand_i = 0;
    int demand_j = 0;

    long distance = 0;

    // Operator (0,1), i.e. element j goes into route of element i.
    if (ichange.operation == 0) {

        qty_supplied_i = station_i->route->qty_supplied;
        demand_j = station_j->dot.expectedCapacity;

        // First verify if the change is feasible.
        if (qty_supplied_i + demand_j <= this->capacity) {

            this->InsertIntoRoute(
                    station_j,
                    station_i->route,
                    station_i);

            this->TwoOptExchange(station_i->route, true);
            this->TwoOptExchange(station_j->route, true);

            distance = this->total_distance;
        }
        // Operator (1,0), i.e. element i goes into route of element j.
    } else if (ichange.operation == 1) {

        qty_supplied_j = station_j->route->qty_supplied;
        demand_i = station_i->dot.expectedCapacity;

        // First verify if the change is feasible.
        if (qty_supplied_j + demand_i <= this->capacity) {

            this->InsertIntoRoute(
                    station_i,
                    station_j->route,
                    station_j);

            this->TwoOptExchange(station_i->route, true);
            this->TwoOptExchange(station_j->route, true);

            distance = this->total_distance;
        }
        // Operator (1,1), i.e. exchange between elements i and j.
    } else {

        if ((qty_supplied_i - demand_i) <= this->capacity
            && (qty_supplied_j - demand_j) <= this->capacity) {

            this->SwapStations(
                    station_i,
                    route_i,
                    station_j,
                    route_j);

            this->TwoOptExchange(route_i, true);
            this->TwoOptExchange(route_j, true);

            distance = this->total_distance;
        }
    }

    //this->PrintRoutes();
    //this->Validate();

    return distance;
}

CVRP::IChange CVRP::RandomOneInterchange() {

    // Get pointers to 2 random stations (indexes between 1 and
    // stations_size - 1), located in 2 different routes.
    int stations_size = this->stations.size();
    int i = 0;
    int j = 0;

    //long distance = 0;

    IChange ichange;

    // Keep trying until a change is accepted.
    bool ichange_accepted = false;

    do {

        do {

            // Never choose the depot, at stations[0].
            i = rand() % (stations_size - 1) + 1;
            j = rand() % (stations_size - 1) + 1;

        } while (stations[i]->route->index == stations[j]->route->index);

        // Choose between i-change operators (0) (0,1); (1) (1,0) or (2)
        // (1,1).
        int opt = rand() % 3;
        //int opt = ICHANGE_OP11;

        int qty_supplied_i = stations[i]->route->qty_supplied;
        int qty_supplied_j = stations[j]->route->qty_supplied;

        int demand_i = stations[i]->dot.expectedCapacity;
        int demand_j = stations[j]->dot.expectedCapacity;

        // Pre-calculate the euclidean distances used for the
        // route cost (distance) calculations of new solutions.
        int dist_i_j =
                CalculateDistance(stations[i], stations[j]);
        int dist_pj_j =
                CalculateDistance(stations[j]->prev, stations[j]);
        int dist_pi_i =
                CalculateDistance(stations[i]->prev, stations[i]);
        int dist_pi_j =
                CalculateDistance(stations[i]->prev, stations[j]);
        int dist_pj_nj =
                CalculateDistance(stations[j]->prev, stations[j]->next);
        int dist_j_ni =
                CalculateDistance(stations[j], stations[i]->next);
        int dist_j_nj =
                CalculateDistance(stations[j], stations[j]->next);
        int dist_pj_i =
                CalculateDistance(stations[j]->prev, stations[i]);
        int dist_pi_ni =
                CalculateDistance(stations[i]->prev, stations[i]->next);
        int dist_i_ni =
                CalculateDistance(stations[i], stations[i]->next);
        int dist_i_nj =
                CalculateDistance(stations[i], stations[j]->next);

        // Operator (0,1), i.e. element j goes into route of element i.
        if (opt == 0) {
            // First verify if the change is feasible.
            if ((qty_supplied_i + demand_j) <= this->capacity) {
                ichange_accepted = true;
                ichange.distance =
                        // Insert stations[j] after [i].
                        +dist_i_j + dist_j_ni - dist_i_ni

                        // New distance between stations[j] and [j + 1],
                        // in route j.
                        + dist_pj_nj - dist_pj_j - dist_j_nj;

                ichange.operation = 0;
            }

        } else if (opt == 1) {
            // First verify if the change is feasible.
            if (qty_supplied_j + demand_i <= this->capacity) {
                ichange_accepted = true;
                ichange.distance =
                        // Insert stations[i] after [j].
                        +dist_i_j + dist_i_nj - dist_j_nj

                        // New distance between stations[i] and [i + 1],
                        // in route i.
                        + dist_pi_ni - dist_pi_i - dist_i_ni;

                ichange.operation = 1;
            }
        } else {
            if ((qty_supplied_i - demand_i + demand_j) <= this->capacity
                && (qty_supplied_j - demand_j + demand_i) <= this->capacity) {
                ichange_accepted = true;
                ichange.distance =
                        // Change in distance caused by including stations[i] in
                        // route j, between stations [j - 1] and [j + 1].
                        dist_pj_i + dist_i_nj - dist_pi_i - dist_i_ni

                        // Change in distance caused by including stations[j] in
                        // route i, between stations [i - 1] and [i + 1].
                        + dist_pi_j + dist_j_ni - dist_pj_j - dist_j_nj;
                ichange.operation = 2;
            }
        }
    } while (!ichange_accepted);

    ichange.i = i;
    ichange.j = j;
    ichange.distance += this->total_distance;

    // Perform the 1-interchange procedure.
    this->OneInterchange(ichange);

    return ichange;
}

long CVRP::TwoOptExchange(Route *route, bool is_hard) {

    long best_distance = route->distance;
    long new_distance = INT_MAX;

    /*printf("2-OPT: Starting local search on route: "\
            "\n\t[NUMBER] : %2d"\
            "\n\t[NS] : %3d"\
            "\n\t[D] : %3ld\n",
            route->index,
            route->num_stations,
            route->distance);*/

    // For clearer code and readability, let's operate over an array, in
    // which we could work with indexes.
    Station **route_stations = (Station **) calloc(route->num_stations + 2, sizeof(Station *));
    Station *curr_route_station = route->start_station;

    // Just a reference to the graph's depot.
    Station *depot = this->GetDepot();

    for (int i = 1; i < route->num_stations + 2; i++) {

        route_stations[i] = curr_route_station;
        curr_route_station = curr_route_station->next;
    }

    // Set the edges of the array to point to the depot.
    route_stations[0] = depot;
    route_stations[route->num_stations + 1] = depot;

    Station *aux = nullptr;

    // Start after the depot, hence i = 1.
    for (int i = 1; i < route->num_stations - 1; i++) {
        for (int j = (i + 1); j < route->num_stations; j++) {

            /*printf("2-OPT: Evaluating potential of exchanging nodes "\
                    "(%2d [i = %d][%2d][%2d], %2d [j = %d][%2d][%2d]).\n",
                    route_stations[i]->index, i, route_stations[i]->coords.x, route_stations[i]->coords.y,
                    route_stations[j]->index, j, route_stations[j]->coords.x, route_stations[j]->coords.y);*/

            // Note that we're not using the next or prev pointers here,
            // one is just evaluating what would happen if 2 stations
            // swapped.
            new_distance =
                    +route->distance
                    + CalculateDistance(route_stations[i - 1], route_stations[j])
                    + CalculateDistance(route_stations[i], route_stations[j + 1])
                    - CalculateDistance(route_stations[i - 1], route_stations[i])
                    - CalculateDistance(route_stations[j], route_stations[j + 1]);

            if (new_distance < best_distance) {

                /*printf("2-OPT: Produced new best distance by exchanging nodes "\
                        "(%2d [%d], %2d [%d]). \n\t[D] : %3ld\n",
                        route_stations[i]->index, i, route_stations[j]->index, j,
                        new_distance);*/

                // Effectively swap the stations in the graph if the calling
                // mode is different than CVRP::DRY_2_OPT.
                if (is_hard) {
                    this->SwapStations(route_stations[i], route_stations[j], j - i);
                }

                // Swap the stations in the local array representing the
                // Route.
                int m = i;
                for (int k = j; k > m; k--) {
                    aux = route_stations[k];
                    route_stations[k] = route_stations[m];
                    route_stations[m++] = aux;
                }

                best_distance = new_distance;
            }
        }
    }

    free(route_stations);

    return best_distance;
}

void CVRP::PrintRoutes() {
    printf("ROUTE LIST:\n");
    int k = 0;
    std::list<Route *>::iterator it;

    // Go through the list of current routes held by this graph.
    // For each route, go from a Station u to the adjacent Station v (only 1 in
    // this graph, considering that u != depot), printing its index as you go.
    for (it = this->routes.begin(); it != this->routes.end(); it++) {

        // Vertex descriptor for the initial station (i.e. immediately after
        // the depot) of the route.
        Station *current_station = (*it)->start_station;

        printf("\n\tROUTE #%2d: %3d",
                //(*it)->GetIndex(),
               ++k,
               (this->depot->index - 1));

        do {

            printf("|%3d", current_station->index - 1);
            current_station = current_station->next;

        } while (!current_station->is_depot);

        printf("|%3d,  [D:%3ld][QS:%3d][NS:%3d]\n",
               (this->depot->index - 1),
               (*it)->distance,
               (*it)->qty_supplied,
               (*it)->num_stations);
    }
}

bool CVRP::Validate() {

    std::vector<bool> validation_array;
    bool validation = false;
    long distance = 0;

    for (int i = 0; i < this->num_stations; i++) {
        validation_array.push_back(true);
    }

    std::list<Route *>::iterator rt;

    for (rt = this->routes.begin(); rt != this->routes.end(); rt++) {
        Station *curr_station = (*rt)->start_station;
        Station *prev_station = nullptr;

        while (!curr_station->is_depot) {
            // Check if this position was already taken.
            if (validation_array[curr_station->index - 1] == false) {
                validation = true;
            }
            validation_array[curr_station->index - 1] = false;
            distance += CalculateDistance(curr_station->prev, curr_station);

            // Advance.
            prev_station = curr_station;
            curr_station = curr_station->next;
        }
        distance += CalculateDistance(prev_station, prev_station->next);
        validation_array[curr_station->index - 1] = false;
    }

    int validation_array_size = validation_array.size();
    for (int i = 0; i < validation_array_size; i++) {
        validation = (validation | validation_array[i]);
//        printf("ROUTE VALIDATION: station[%d] %s in solution\n", i, (validation_array[i] ? "NOT" : "IS"));
    }

//    printf("\nSOLUTION VALIDATION REPORT: "\
//            "\n\t[NUM STATIONS] = %d %d"\
//            "\n\t[STATION INCLUSION] = %s\n\t[MEAS. TOTAL DISTANCE] = %ld (SAVED IS %ld)\n\n",
//           (int) this->num_stations, (int) this->stations.size(),
//           (validation ? "NOT OK" : "OK"),
//           distance,
//           this->total_distance);

    return !(validation);
}
