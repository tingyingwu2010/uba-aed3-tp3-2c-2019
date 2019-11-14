#include <stdexcept>

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
        this->AddStation(i, dot, dot.expectedCapacity == 0);
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
        if (include_depot) routes_vector[i].push_back(this->depot->index + 1);
        do {
            routes_vector[i].push_back(current_station->index + 1);
            current_station = current_station->next;
        } while (!current_station->is_depot);
        if (include_depot) routes_vector[i].push_back(this->depot->index + 1);
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
