#include <algorithms/SavingsHeuristic.h>
#include "utils/AlgorithmMain.h"
#include "../algorithms/SavingsHeuristic.h"
#include "../utils/AlgorithmMain.h"
#include "../entities/entrypoint/InputCVRP.h"
#include "../entities/entrypoint/OutputCVRP.h"

int main(){
    InputCVRP *inputCVRP = AlgorithmMain::input_from_python();

    SavingsHeuristic csw;

    OutputCVRP *outputCVRP = csw.execute(inputCVRP);
    AlgorithmMain::print(*outputCVRP);

    return 0;
}
