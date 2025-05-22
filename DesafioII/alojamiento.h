#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "Fecha.h"

class Anfitrion; // Declaración adelantada
class Reservacion;

class Alojamiento {
private:
    int codigo;
    char nombre[50];
    char tipo[20];            // "Casa" o "Apartamento"
    char direccion[100];
    char municipio[30];
    char departamento[30];
    float precioPorNoche;

    char** amenidades;
    int totalAmenidades;
    int capacidadAmenidades;

    bool disponibilidad[365]; // 1 año de disponibilidad (1 = ocupado)

    Anfitrion* anfitrion;

public:
    Alojamiento(int cod, const char* nom, const char* tip, const char* dir,
                const char* muni, const char* depto, float precio,
                Anfitrion* anfi);

    ~Alojamiento();

    int getCodigo() const;
    float getPrecioPorNoche() const;
    const char* getMunicipio() const;
    Anfitrion* getAnfitrion() const;

    void agregarAmenidad(const char* amenidad);
    void mostrarDetalles() const;

    bool estaDisponible(int diaDelAnio, int noches) const;
    void reservar(int diaDelAnio, int noches);

    void mostrarReservas(); // se enlaza con lista de Reservaciones más adelante
};

#endif
