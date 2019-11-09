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

int OutputCVRP::getCostoSolución() const {
    return costoSolución;
}

void OutputCVRP::setCostoSolución(int costoSolución) {
    OutputCVRP::costoSolución = costoSolución;
}
