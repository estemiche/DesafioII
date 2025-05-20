#include "Usuario.h"
#include <iostream>
#include <cstring>

Usuario::Usuario(const char* doc, int ant, float punt) {
    strncpy(documento, doc, 15);
    antiguedad = ant;
    puntuacion = punt;
}

Usuario::Usuario(const Usuario& other) {
    strncpy(documento, other.documento, 15);
    antiguedad = other.antiguedad;
    puntuacion = other.puntuacion;
}

Usuario::~Usuario() {
    // Destructor virtual
}

const char* Usuario::getDocumento() const {
    return documento;
}

int Usuario::getAntiguedad() const {
    return antiguedad;
}

float Usuario::getPuntuacion() const {
    return puntuacion;
}

void Usuario::setPuntuacion(float p) {
    puntuacion = p;
}
