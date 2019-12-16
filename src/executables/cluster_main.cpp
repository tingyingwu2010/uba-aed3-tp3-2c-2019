#include <algorithms/SavingsHeuristic.h>
#include <algorithms/NearestNeighborSweep.h>
#include "utils/AlgorithmMain.h"

int main(){
    InputCVRP *inputCVRP = AlgorithmMain::input_from_python();

    NearestNeighborSweep csw;
    OutputCVRP *outputCVRP = csw.execute(inputCVRP);

    AlgorithmMain::print(*outputCVRP);

    return 0;
}
