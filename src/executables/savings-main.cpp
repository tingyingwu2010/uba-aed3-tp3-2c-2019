//
// Created by Christian nahuel Rivera on 7/11/19.
//

#include "../algorithms/SavingsEuristic.h"
#include "../utils/io.hpp"

int main(){
    InputCVRP *inputCVRP = input_from_python();

    CVRPEuristic *savingsEuristic = new SavingsEuristic();

    OutputCVRP *outputCVRP = savingsEuristic->execute(*inputCVRP);

    print(*outputCVRP);

    return 0;
}