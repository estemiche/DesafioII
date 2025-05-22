#include "Reservacion.h"
#include "Fecha.h"
#include <cstdio>
#include <cstring>

Reservacion::Reservacion(int cod, Fecha f, int dur, const char* metodo, float m,
                         const char* nota, Huesped* h, Alojamiento* a)
    : codigo(cod), fechaInicio(f), duracion(dur), monto(m),
    huesped(h), alojamiento(a) {
    strncpy(metodoPago, metodo, 19);
    metodoPago[19] = '\0';

    strncpy(notas, nota, 1000);
    notas[1000] = '\0';
}

Reservacion::~Reservacion() {
    // No elimina huésped ni alojamiento (se gestionan aparte)
}

int Reservacion::getCodigo() const {
    return codigo;
}

Fecha Reservacion::getFechaInicio() const {
    return fechaInicio;
}

int Reservacion::getDuracion() const {
    return duracion;
}

float Reservacion::getMonto() const {
    return monto;
}

void Reservacion::mostrarResumen() const {
    printf("Reserva #%d\n", codigo);
    printf("Fecha inicio: ");
    fechaInicio.mostrarFecha();
    printf(" | Duración: %d noche(s)\n", duracion);
    printf("Método de pago: %s | Monto: %.2f\n", metodoPago, monto);
    printf("Notas: %s\n", notas);
}
