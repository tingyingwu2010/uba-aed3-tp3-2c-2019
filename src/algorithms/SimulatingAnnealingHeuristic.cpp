#include "SimulatingAnnealingHeuristic.h"
#include "SavingsHeuristic.h"
#include "config/defaults.h"

SimulatingAnnealingHeuristic::SimulatingAnnealingHeuristic() = default;

SimulatingAnnealingHeuristic::~SimulatingAnnealingHeuristic() = default;

// Generates a random number (double floating point precision) in the interval [0.00, 1.00[.
double Rand() {
    double r = (double) rand() / (double) (RAND_MAX + 1.0);
    return r;
}

double CalcAcceptanceProb(
        long delta,
        double temp) {

    // If the route distance from the candidate solution is better, return 
    // a probability of 1.0, i.e. force the SA algorithm to accept this new 
    // solution.
    if (delta >= 0) {
        return 1.0;
    }

    // Calculate the probability of acceptance, using formula (6.1) on 
    // page 130 of Toth2002.
    double p = exp(((double) (delta)) / temp);
    return p;
}

// Initialization of the cooling schedule parameters,
// as defined in Osman1993, i.e. determine an initial temperature value by
// exploring (without performing changes) the entire 1-interchange
// neighborhood of S_c.
SimulatingAnnealingHeuristic::CoolingScheduleParams CalcCoolingSchedule(CVRP *graph) {

    // Starting and final temperatures.
    uint32_t T_s = 0, T_f = UINT32_MAX;

    // Total number of feasible exchanges.
    uint32_t nfeas = 0;

    // Auxiliary variable for keeping track of changes.
    uint32_t abs_change = 0;

    // Other auxiliary variables;
    long dist_i_j = 0;
    long dist_pj_j = 0;
    long dist_pi_i = 0;
    long dist_pi_j = 0;
    long dist_pj_nj = 0;
    long dist_j_nj = 0;
    long dist_pj_i = 0;
    long dist_pi_ni = 0;
    long dist_i_ni = 0;

    long op_ij = 0;
    long op_ji = 0;
    long op_swap = 0;

    int qty_supplied_i = 0;
    int qty_supplied_j = 0;

    std::list<Route *>::iterator it;
    std::list<Route *>::iterator jt;

    // Go through all route combinations.
    for (it = graph->routes.begin(); it != graph->routes.end(); it++) {

        // For clearer code and readability, let's operate over an array, in 
        // which we could work with indexes.
        Station **stations_i = graph->CreateRouteRep(*it);

        jt = it;
        jt++;

        for (; jt != graph->routes.end(); jt++) {

            Station **stations_j = graph->CreateRouteRep(*jt);

            // Evaluate the gains from swapping 1 stations between 
            // routes route_i and route_j. Fortunately, this is never larger 
            // than OSMAN_ICHANGE_MAX_LAMBDA.
            for (int i = 1; i < (*it)->num_stations; i++) {
                for (int j = 1; j < (*jt)->num_stations; j++) {

                    dist_pj_i = CVRP::CalculateDistance(stations_j[j - 1], stations_i[i]);
                    dist_i_j = CVRP::CalculateDistance(stations_i[i], stations_j[j]);
                    dist_pj_j = CVRP::CalculateDistance(stations_j[j - 1], stations_j[j]);

                    dist_pi_ni = CVRP::CalculateDistance(stations_i[i - 1], stations_i[i + 1]);
                    dist_pi_i = CVRP::CalculateDistance(stations_i[i - 1], stations_i[i]);
                    dist_i_ni = CVRP::CalculateDistance(stations_i[i], stations_i[i + 1]);

                    dist_pi_j = CVRP::CalculateDistance(stations_i[i - 1], stations_j[j]);
                    //dist_j_i   = dist_i_j;

                    dist_pj_nj = CVRP::CalculateDistance(stations_j[j - 1], stations_j[j + 1]);
                    dist_j_nj = CVRP::CalculateDistance(stations_j[j], stations_j[j + 1]);

                    // Check if the exchange is feasible, i.e. if the 
                    // route's qty_supplied value does not exceed the 
                    // capacity of the vehicles.
                    qty_supplied_j =
                            (*jt)->qty_supplied
                            + (stations_i[i]->dot.expectedCapacity);

                    // Change in distance caused by including point i in 
                    // route_j, i.e. testing operator (1,0)
                    if ((qty_supplied_j > graph->capacity)) {

                        op_ij = 0;

                    } else {

                        // A feasible (potential) change.
                        nfeas++;

                        op_ij =
                                // Insert station i in between j - 1 and j.
                                +dist_pj_i
                                + dist_i_j
                                - dist_pj_j

                                // New distance between stations (i - 1) and (i + 1).
                                + dist_pi_ni
                                - dist_pi_i
                                - dist_i_ni;

                        abs_change = abs(op_ij);

                        if (abs_change > T_s)
                            T_s = abs_change;

                        if (abs_change < T_f)
                            T_s = abs_change;
                    }

                    qty_supplied_i =
                            (*it)->qty_supplied
                            + (stations_j[j]->dot.expectedCapacity);

                    if (qty_supplied_i > graph->capacity) {

                        op_ji = 0;

                    } else {

                        nfeas++;

                        // Change in distance caused by including point j in 
                        // route_i, i.e. testing operator (0,1).
                        op_ji =
                                // Insert station j in between i - 1 and i.
                                +dist_pi_j
                                + dist_i_j
                                - dist_pi_i

                                // New distance between stations (j - 1) and (j + 1).
                                + dist_pj_nj
                                - dist_pj_j
                                - dist_j_nj;

                        abs_change = abs(op_ji);

                        if (abs_change > T_s)
                            T_s = abs_change;

                        if (abs_change < T_f)
                            T_s = abs_change;
                    }

                    if ((qty_supplied_i - stations_i[i]->dot.expectedCapacity) > graph->capacity
                        || (qty_supplied_j - stations_j[j]->dot.expectedCapacity) > graph->capacity) {

                        op_swap = 0;

                    } else {

                        // Update the number of feasible exchanges by 2 (i.e. 
                        // exchanging points i and j between routes i and j).
                        nfeas = nfeas + 2;

                        // Change in distance by exchanging points i and j between 
                        // route_i and route_j, i.e. testing operator (1,1).
                        op_swap =
                                // Change in distance caused by including point i in
                                // route_j, between stations j - 1 and j.
                                +dist_pj_i
                                + CVRP::CalculateDistance(stations_i[i], stations_j[j + 1])
                                - dist_pi_i
                                - dist_i_ni

                                // Change in distance caused by including point j in
                                // route_i, between stations i - 1 and i.
                                + dist_pi_j
                                + CVRP::CalculateDistance(stations_j[j], stations_i[i + 1])
                                - dist_pj_j
                                - dist_j_nj;

                        abs_change = abs(op_swap);

                        if (abs_change > T_s)
                            T_s = abs_change;

                        if (abs_change < T_f)
                            T_f = abs_change;
                    }
                }
            }

            free(stations_j);
        }

        free(stations_i);
    }

    // Fill the cooling schedule parameters structure.
    SimulatingAnnealingHeuristic::CoolingScheduleParams params;

    params.T_s = (double) T_s;
    params.T_f = (double) T_f;
    params.alpha = (graph->num_stations * nfeas);
    params.gamma = graph->num_stations;
    params.R = 3;
    return params;
}

void SimulatingAnnealingHeuristic::Run(CVRP *graph, double cooling_rate, double T_i, uint32_t L, uint16_t stop_n,
                                       bool debug) {

    // Current solution S_c.
    CVRP *S_c = new CVRP();

    // Current solution S_c.
    CVRP *S_n = new CVRP();

    // Best solution S_b.
    CVRP *S_b = new CVRP();

    // Set the initial solution S from the graph given as argument.
    S_c->CopyFrom(graph);


    // Set S_b <- S_c (from the current solution S_c).
    S_b->CopyFrom(graph);
    S_n->CopyFrom(graph);


    // Save the number of iterations for which S_c remains unchanged, i.e. it 
    // is accepted after the 3 step.
    int S_c_unchanged = 0;

    // Although the Osman1993 method is not implemented here, its method for
    // calculation of initial temperature was maintained.
    CoolingScheduleParams params = CalcCoolingSchedule(graph);

    // Variables for Cooling Schedule. FIXME: We're using the initial 
    // temperature calculation method from Osman1993.
    // Use the formula set in our paper for determining the initial 
    // temperature 
    double T_k = (params.T_s / abs(log(0.5))) * 10.0;

    double randomness = 0.0;
    double prob = 0.0;

    uint32_t k = 0;
    uint32_t i = 0;

    long best_distance = INT_MAX;

    // Keep 1-Interchange information, without performing changes. 
    // Notice that changes are always evaluated and performed over S_c.
    CVRP::IChange ichange;

    do {

        for (i = 0; i < L; i++) {

            // Reset ichange
            ichange.i = 0;
            ichange.j = 0;
            ichange.distance = 0;
            ichange.operation = 0;

            // Perform a random 1-interchange on S_n.
            ichange = S_n->RandomOneInterchange();

            // Keep track of the best value of S_n ever recorded, even if it 
            // is worse than S_c or S_b.
            if (S_n->total_distance < best_distance) {
                best_distance = S_n->total_distance;
            }

            if (S_n->total_distance <= S_c->total_distance) {
                // Perform the changes on S_c.
                S_c->OneInterchange(ichange);
                S_c_unchanged = 0;
                if (S_n->total_distance <= S_b->total_distance) {
                    S_b->CopyFrom(S_n);
                }
            } else {
                prob = CalcAcceptanceProb((S_c->total_distance - S_n->total_distance), T_k);
                randomness = Rand();
                if (prob > randomness) {
                    // Accept S_n.

                    // Perform the changes on S_c.
                    S_c->OneInterchange(ichange);
                    S_c_unchanged = 0;
                } else {
                    // Do not accept S_n and keep S_c.

                    // TODO: This is expensive and should be avoided.
                    S_n->CopyFrom(S_c);

                    // TODO: In addition to the copy made above, I figured I have to do this, just because the order of
                    //  the Station vector is different in S_n and S_c after the previous instruction.
                    S_c->CopyFrom(S_n);

                    if (debug)
                        printf("SA: Keeping S_c at iteration i = %d: \n\t[T_k] = %0.4f\n\t[S_i] = %ld\n\t[S_c]"
                               " = %ld\n\t[S_n] = %ld\n\t[ichange.distance] = %ld\n\t[S_b] = %ld\n\t[S_c UNCHANGED FOR]"
                               " = %d\n\n", i, T_k, graph->total_distance, S_c->total_distance, S_n->total_distance,
                               ichange.distance, S_b->total_distance, S_c_unchanged);

                    S_c_unchanged++;
                }
            }
        }

        if (debug)
            printf("SA: At iteration k = %d: \n\t[T_k] = %0.4f\n\t[S_i] = %ld\n\t[S_c] = %ld\n\t[S_n] "
                   "= %ld\n\t[S_b] = %ld\n\t[S_c UNCHANGED FOR] = %d\n\t[BEST S_n SO FAR] = %ld", k, T_k,
                   graph->total_distance, S_c->total_distance, S_n->total_distance, S_b->total_distance, S_c_unchanged,
                   best_distance);

        // Cool it down...
        T_k = T_k * (1 - cooling_rate);

        // Increment L_k
        k++;

    } while (S_c_unchanged < stop_n);

    S_b->Validate();
    graph->CopyFrom(S_b);
}

OutputCVRP *SimulatingAnnealingHeuristic::execute(InputCVRP *input) {
    CVRP cws_cvrp(input);

    // Pointers to different method's solutions.
    SavingsHeuristic::Run(&cws_cvrp);
    this->Run(&cws_cvrp, SA_COOLING, SA_INIT_TEMP, SA_TERMINATION, SA_HALTING);

    auto *output = new OutputCVRP();
    output->setCantidadDeCamiones(cws_cvrp.routes.size());
    output->setCostoSolucion(cws_cvrp.total_distance);
    output->setCaminos(cws_cvrp.GetRoutesVector());

    return output;
}
