#include "algorithms/GreedyHeuristic.h"
#include "utils/AlgorithmMain.h"


int main() {
    InputCVRP *inputCVRP = AlgorithmMain::input_from_python();

    GreedyHeuristic greedy;

    OutputCVRP *outputCVRP = greedy.execute(inputCVRP);
    AlgorithmMain::print(*outputCVRP);

    return 0;
}
