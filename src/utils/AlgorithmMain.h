#pragma once

#include <iostream>
#include <algorithms/SavingsHeuristic.h>
#include "entities/entrypoint/InputCVRP.h"
#include "algorithms/SavingsHeuristic.h"
#include "entities/entrypoint/OutputCVRP.h"

using namespace std;

class AlgorithmMain {
public:
    AlgorithmMain() = default;

    virtual ~AlgorithmMain() = default;

    static InputCVRP *input_from_python() {
        auto *inputCVRP = new InputCVRP();
        int vertex, capacity;
        std::cin >> vertex;
        std::cin >> capacity;
        inputCVRP->setVertex(vertex);
        inputCVRP->setCapacity(capacity);
        std::vector<Dot> dots;
        for (int dot = 0; dot < vertex; dot++) {
            int x, y, objetivo;
            std::cin >> x;
            std::cin >> y;
            std::cin >> objetivo;

            dots.emplace_back(x, y, objetivo);
        }
        inputCVRP->setVertexCordenates(dots);
        return inputCVRP;
    }

    static void print(OutputCVRP output) {
        std::cout << output.getCantidadDeCamiones() << std::endl;
        for (const auto& camino : output.getCaminos()) {
            std::string camino_str;
            for (auto vertice : camino) {
                camino_str += std::to_string(vertice) + " ";
            }
            camino_str.pop_back();

            std::cout << camino_str << std::endl;
        }
        std::cout << output.getCostoSolucion() << std::endl;
    }
};
