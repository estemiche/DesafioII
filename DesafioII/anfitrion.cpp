#include "Anfitrion.h"
#include <cstdio>
#include <cstring>

Anfitrion::Anfitrion(const char* doc, int ant, float punt)
    : Usuario(doc, ant, punt) {
    capacidad = 3;
    totalAlojamientos = 0;
    alojamientos = new Alojamiento*[capacidad];
}

Anfitrion::~Anfitrion() {
    for (int i = 0; i < totalAlojamientos; i++) {
        delete alojamientos[i];
    }
    delete[] alojamientos;
}

void Anfitrion::expandirAlojamientos() {
    capacidad *= 2;
    Alojamiento** nuevo = new Alojamiento*[capacidad];
    for (int i = 0; i < totalAlojamientos; i++) {
        nuevo[i] = alojamientos[i];
    }
    delete[] alojamientos;
    alojamientos = nuevo;
}

void Anfitrion::agregarAlojamiento(Alojamiento* a) {
    if (totalAlojamientos == capacidad) {
        expandirAlojamientos();
    }
    alojamientos[totalAlojamientos++] = a;
}

void Anfitrion::consultarReservasActivas() const {
    for (int i = 0; i < totalAlojamientos; i++) {
        alojamientos[i]->mostrarReservas(); // asumimos que esta función existe en Alojamiento
    }
}

void Anfitrion::mostrarDatos() const {
    printf("Anfitrion: %s | Antigüedad: %d meses | Puntuacion: %.1f\n", documento, antiguedad, puntuacion);
}
