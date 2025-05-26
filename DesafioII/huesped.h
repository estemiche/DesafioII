#ifndef HUESPED_H
#define HUESPED_H

#include "Usuario.h"
#include "Reservacion.h"

class Huesped : public Usuario {
private:
    Reservacion** reservas;
    int totalReservas;
    int capacidad;

    void expandirReservas();

public:
    Huesped(const char* doc = "", int ant = 0, float punt = 0.0f);
    ~Huesped();

    void agregarReserva(Reservacion* r);
    void anularReserva(int codigoReserva);
    void mostrarReservas() const;

    void mostrarDatos() const override;
    void agregarReservacion(Reservacion* r);
};

#endif
