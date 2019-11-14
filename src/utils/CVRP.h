#pragma once

#include <list>
#include <cmath>
#include <vector>
#include <string>
#include <utility>

#include "entities/core/Dot.h"
#include "entities/core/Route.h"
#include "entities/core/Station.h"
#include "entities/entrypoint/InputCVRP.h"

using namespace std;

class CVRP {

public:

    CVRP();

    explicit CVRP(InputCVRP *dataset);

    ~CVRP();

    uint32_t id{};

    int num_stations;
    int num_routes;
    int capacity;

    long total_distance;

    Station *depot;

    std::vector<Station *> stations;

    std::list<Route *> routes;

    Station *GetDepot();

    static long CalculateDistance(Dot i, Dot j);

    static long CalculateDistance(Station *i, Station *j);

    static Station *GetNextStation(Station *station);

    static Station *GetPrevStation(Station *station);

    Station *AddStation(int index, Dot dot, bool is_depot);

    static void LinkStations(Station *start, Station *end);

    long SwapStations(Station *i, Station *j, int num_stations);


    vector<vector<int>> GetRoutesVector(bool include_depot = true);

    Route *AddRoute(
            int qty_supplied,
            long distance,
            Station *start_station,
            Station *end_station);

    static Route *AddToRoute(Station *station, Route *route);

    long TwoOptExchange(Route *route);

    void DeleteRoute(Route *route);


    friend std::ostream &operator<<(std::ostream &os, const CVRP &cvrp) {
        os << "num_stations: " << cvrp.num_stations << " | num_routes: " << cvrp.num_routes << " | capacity: "
           << cvrp.capacity;
        os << " | total_distance: " << cvrp.total_distance << " | Depot: " << *cvrp.depot << endl;
        os << "_Routes {" << cvrp.routes.size() << "}_\n";
        if (cvrp.routes.empty()) {
            return os;
        }
        for (auto const &r : cvrp.routes) {
            std::cout << "- " << *r << endl;
        }
        return os;
    };
};
