#include "Reservacion.h"
#include "Huesped.h"
#include "Alojamiento.h"
#include <cstring>
#include <cstdio>

Reservacion::Reservacion(int codigo, Fecha fecha, int duracion,
                         const char* metodoPago, float monto,
                         const char* notas, Huesped* h, Alojamiento* a)
{
    this->codigo = codigo;
    this->fechaInicio = fecha;
    this->duracion = duracion;
    strcpy(this->metodoPago, metodoPago);
    this->monto = monto;
    strcpy(this->notas, notas);
    this->huesped = h;
    this->alojamiento = a;
}

int Reservacion::getCodigo() { return codigo; }
Fecha Reservacion::getFechaInicio() { return fechaInicio; }
int Reservacion::getDuracion() { return duracion; }
const char* Reservacion::getMetodoPago() { return metodoPago; }
float Reservacion::getMonto() { return monto; }
const char* Reservacion::getNotas() { return notas; }
Alojamiento* Reservacion::getAlojamiento() { return alojamiento; }

void Reservacion::mostrarResumen() {
    printf("Reserva #%d - %d noches - $%.2f - %s\n", codigo, duracion, monto, metodoPago);
}
Huesped* Reservacion::getHuesped() {
    return huesped;
}
