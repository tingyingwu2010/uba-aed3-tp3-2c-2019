//
// Created by Christian nahuel Rivera on 11/11/19.
//

#ifndef TP3_IO
#define TP3_IO

#include  <iostream>
#include "../entities/entrypoint/InputCVRP.h"
#include "../entities/entrypoint/OutputCVRP.h"

InputCVRP *input_from_python();
void print(OutputCVRP output);

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
    std::cout << output.getCostoSolucion() << std::endl;
}

#endif