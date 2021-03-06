//
// Created by Christian nahuel Rivera on 7/11/19.
//

#include "OutputCVRP.h"

const std::vector<std::vector<int>> &OutputCVRP::getCaminos() const {
    return caminos;
}

void OutputCVRP::setCaminos(const std::vector<std::vector<int>> &caminos) {
    OutputCVRP::caminos = caminos;
}

int OutputCVRP::getCantidadDeCamiones() const {
    return cantidadDeCamiones;
}

void OutputCVRP::setCantidadDeCamiones(int cantidadDeCamiones) {
    OutputCVRP::cantidadDeCamiones = cantidadDeCamiones;
}

int OutputCVRP::getCostoSolucion() const {
    return costoSolucion;
}

void OutputCVRP::setCostoSolucion(int costoSolucion) {
    OutputCVRP::costoSolucion = costoSolucion;
}

std::ostream &operator<<(std::ostream &os, const OutputCVRP &o) {
    os << o.getCantidadDeCamiones() << std::endl;
    for (auto camino : o.getCaminos()) {
        std::string camino_str = "";
        for (auto vertice : camino) {
            camino_str += std::to_string(vertice) + " ";
        }
        camino_str.pop_back();

        os << camino_str << std::endl;
    }
    os << o.getCostoSolucion() << std::endl;
    return os;
}

OutputCVRP::OutputCVRP(std::vector<std::vector<int>> rutas, std::vector<int> capacidades) {
    this->caminos = rutas;
    this->cantidadDeCamiones = rutas.size();

    long peso = 0;
    for(auto ruta : rutas){
        for(auto vertice : ruta){
            peso += capacidades.at(vertice-1);
        }
    }
    this->costoSolucion = peso;
}
