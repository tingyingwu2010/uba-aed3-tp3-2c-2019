#pragma once

#include <iostream>
#include <vector>

class OutputCVRP {
public:
    OutputCVRP() {};

    OutputCVRP(std::vector<std::vector<int>> rutas, std::vector<int> capacidades);

    const std::vector<std::vector<int>> &getCaminos() const;

    void setCaminos(const std::vector<std::vector<int>> &caminos);

    int getCantidadDeCamiones() const;

    void setCantidadDeCamiones(int cantidadDeCamiones);

    int getCostoSolucion() const;

    void setCostoSolucion(int costoSolucion);

    friend std::ostream &operator<<(std::ostream &os, const OutputCVRP &o);

private:
    std::vector<std::vector<int>> caminos;
    int cantidadDeCamiones;
    int costoSolucion;

};
