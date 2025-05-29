#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "Fecha.h"

class Anfitrion;
class Reservacion;

class Alojamiento {
private:
    int codigo;
    char nombre[50];
    char tipo[20];
    char direccion[100];
    char municipio[30];
    char departamento[30];
    float precioPorNoche;

    char** amenidades;
    int totalAmenidades;
    int capacidadAmenidades;

    bool disponibilidad[365];

    Anfitrion* anfitrion;

public:
    Alojamiento(int cod, const char* nom, const char* tip, const char* dir,
                const char* muni, const char* depto, float precio,
                Anfitrion* anfi);

    ~Alojamiento();

    int getCodigo() const;
    float getPrecioPorNoche() const;
    const char* getMunicipio() const;
    const char* getNombre() const;
    Anfitrion* getAnfitrion() const;

    void agregarAmenidad(const char* amenidad);
    void mostrarDetalles() const;

    bool estaDisponible(int diaDelAnio, int noches) const;
    void reservar(int diaDelAnio, int noches);
    void liberar(int diaInicio, int noches);

    void mostrarReservas();
};

#endif
