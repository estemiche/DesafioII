#ifndef RESERVACION_H
#define RESERVACION_H

#include "Fecha.h"

class Huesped;
class Alojamiento;
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
    Reservacion(int codigo, Fecha fecha, int duracion,
                const char* metodoPago, float monto,
                const char* notas, Huesped* h, Alojamiento* a);

    int getCodigo();
    Fecha getFechaInicio();
    int getDuracion();
    const char* getMetodoPago();
    float getMonto();
    const char* getNotas();
    Alojamiento* getAlojamiento();

    void mostrarResumen();
};

#endif
