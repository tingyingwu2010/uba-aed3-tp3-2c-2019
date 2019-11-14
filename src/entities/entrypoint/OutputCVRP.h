//
// Created by Christian nahuel Rivera on 7/11/19.
//

#ifndef TP3_HEURISTICAS_CVRP_OUTPUTCVRP_H
#define TP3_HEURISTICAS_CVRP_OUTPUTCVRP_H

#include <iostream>
#include <vector>

class OutputCVRP {
public:
    const std::vector<std::vector<int>> &getCaminos() const;

    void setCaminos(const std::vector<std::vector<int>> &caminos);

    int getCantidadDeCamiones() const;

    void setCantidadDeCamiones(int cantidadDeCamiones);

    int getCostoSolucion() const;

    void setCostoSolucion(int costoSolucion);

    friend std::ostream& operator<<(std::ostream& os, const OutputCVRP& o);

private:
    std::vector<std::vector<int>> caminos;
    int cantidadDeCamiones;
    int costoSolucion;

};


#endif //TP3_HEURISTICAS_CVRP_OUTPUTCVRP_H
