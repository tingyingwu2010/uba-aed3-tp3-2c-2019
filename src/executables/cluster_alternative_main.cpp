#include <algorithms/NearestNeighborAGM.h>
#include "utils/AlgorithmMain.h"

int main() {
    InputCVRP *inputCVRP = AlgorithmMain::input_from_python();

    NearestNeighborAGM nn_agm;
    OutputCVRP *outputCVRP = nn_agm.execute(inputCVRP);

    AlgorithmMain::print(*outputCVRP);

    return 0;
}
