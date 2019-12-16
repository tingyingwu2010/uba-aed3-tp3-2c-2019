#include <algorithms/SimulatingAnnealingHeuristic.h>
#include "utils/AlgorithmMain.h"

int main(){
    InputCVRP *inputCVRP = AlgorithmMain::input_from_python();

    SimulatingAnnealingHeuristic sa;
    OutputCVRP *outputCVRP = sa.execute(inputCVRP);

    AlgorithmMain::print(*outputCVRP);
    return 0;
}
