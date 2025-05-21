#ifndef ANFITRION_H
#define ANFITRION_H

#include "Usuario.h"
#include "Alojamiento.h"

class Anfitrion : public Usuario {
private:
    Alojamiento** alojamientos;
    int totalAlojamientos;
    int capacidad;

    void expandirAlojamientos();

public:
    Anfitrion(const char* doc = "", int ant = 0, float punt = 0.0f);
    ~Anfitrion();

    void agregarAlojamiento(Alojamiento* a);
    void consultarReservasActivas() const;

    void mostrarDatos() const override;
};

#endif

