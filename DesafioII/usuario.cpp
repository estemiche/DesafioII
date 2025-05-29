#include "Usuario.h"
#include <cstring>

Usuario::Usuario(const char* doc, int ant, float punt) {
    strncpy(documento, doc, 14);
    documento[14] = '\0';
    antiguedad = ant;
    puntuacion = punt;
}

Usuario::Usuario(const Usuario& other) {
    strncpy(documento, other.documento, 14);
    documento[14] = '\0';
    antiguedad = other.antiguedad;
    puntuacion = other.puntuacion;
}

Usuario::~Usuario() {

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
