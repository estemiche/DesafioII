#include "Huesped.h"
#include <cstdio>
#include <cstring>

Huesped::Huesped(const char* doc, int ant, float punt)
    : Usuario(doc, ant, punt) {
    capacidad = 5;
    totalReservas = 0;
    reservas = new Reservacion*[capacidad];
}

Huesped::~Huesped() {
    for (int i = 0; i < totalReservas; i++) {
        delete reservas[i];
    }
    delete[] reservas;
}

void Huesped::expandirReservas() {
    capacidad *= 2;
    Reservacion** nuevo = new Reservacion*[capacidad];
    for (int i = 0; i < totalReservas; i++) {
        nuevo[i] = reservas[i];
    }
    delete[] reservas;
    reservas = nuevo;
}

void Huesped::agregarReserva(Reservacion* r) {
    if (totalReservas == capacidad) {
        expandirReservas();
    }
    reservas[totalReservas++] = r;
}

void Huesped::anularReserva(int codigoReserva) {
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i]->getCodigo() == codigoReserva) {
            delete reservas[i];
            for (int j = i; j < totalReservas - 1; j++) {
                reservas[j] = reservas[j + 1];
            }
            totalReservas--;
            printf("Reserva anulada correctamente.\n");
            return;
        }
    }
    printf("Reserva no encontrada.\n");
}

void Huesped::mostrarReservas() const {
    for (int i = 0; i < totalReservas; i++) {
        reservas[i]->mostrarResumen(); // se implementará en Reservacion
    }
}

void Huesped::mostrarDatos() const {
    printf("Huésped: %s | Antigüedad: %d meses | Puntuación: %.1f\n",
           documento, antiguedad, puntuacion);
}
