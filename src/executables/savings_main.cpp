#include <algorithms/SavingsHeuristic.h>
#include "utils/AlgorithmMain.h"

int main(){
    InputCVRP *inputCVRP = AlgorithmMain::input_from_python();

    SavingsHeuristic csw;

    OutputCVRP *outputCVRP = csw.execute(inputCVRP);
    AlgorithmMain::print(*outputCVRP);

    return 0;
}
