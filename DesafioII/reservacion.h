#ifndef RESERVACION_H
#define RESERVACION_H

#include "Fecha.h"

class Huesped;       // Declaración adelantada
class Alojamiento;   // Declaración adelantada

class Reservacion {
private:
    int codigo;
    Fecha fechaInicio;
    int duracion;
    char metodoPago[20];
    float monto;
    char notas[1001];

    Huesped* huesped;
    Alojamiento* alojamiento;

public:
    Reservacion(int cod, Fecha f, int dur, const char* metodo, float monto,
                const char* nota, Huesped* h, Alojamiento* a);

    ~Reservacion();

    int getCodigo() const;
    Fecha getFechaInicio() const;
    int getDuracion() const;
    float getMonto() const;

    void mostrarResumen() const;
};

#endif
