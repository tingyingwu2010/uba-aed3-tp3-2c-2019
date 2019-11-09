//
// Created by Christian nahuel Rivera on 7/11/19.
//

#include <iostream>
#include "../entities/entrypoint/InputCVRP.h"
#include "../algorithms/SavingsEuristic.h"
#include "../entities/entrypoint/OutputCVRP.h"

InputCVRP *input_from_python();

void print(OutputCVRP output);

int main(){
    InputCVRP *inputCVRP = input_from_python();

    CVRPEuristic *savingsEuristic = new SavingsEuristic();

    OutputCVRP *outputCVRP = savingsEuristic->execute(*inputCVRP);

    print(*outputCVRP);

    return 0;
}

InputCVRP *input_from_python() {
    InputCVRP *inputCVRP = new InputCVRP();
    int vertex, capacity;
    std::cin >> vertex;
    std::cin >> capacity;
    inputCVRP->setVertex(vertex);
    inputCVRP->setCapacity(capacity);
    std::vector<Dot> dots;
    for(int dot = 0; dot < vertex; dot++){
        int x, y, objetivo;
        std::cin >> x;
        std::cin >> y;
        std::cin >> objetivo;

        dots.push_back(Dot(x,y,objetivo));
    }
    return inputCVRP;
}

void print(OutputCVRP output) {
    std::cout << output.getCantidadDeCamiones() << std::endl;
    for(auto camino : output.getCaminos()){
        std::string camino_str = "";
        for(auto vertice : camino){
            camino_str += std::to_string(vertice) + " ";
        }
        camino_str.pop_back();

        std::cout << camino_str << std::endl;
    }
    std::cout << output.getCostoSolución() << std::endl;
}