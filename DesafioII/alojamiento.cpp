#include "Alojamiento.h"
#include <cstdio>
#include <cstring>

Alojamiento::Alojamiento(int cod, const char* nom, const char* tip, const char* dir,
                         const char* muni, const char* depto, float precio,
                         Anfitrion* anfi)
    : codigo(cod), precioPorNoche(precio), anfitrion(anfi) {
    strncpy(nombre, nom, 49); nombre[49] = '\0';
    strncpy(tipo, tip, 19); tipo[19] = '\0';
    strncpy(direccion, dir, 99); direccion[99] = '\0';
    strncpy(municipio, muni, 29); municipio[29] = '\0';
    strncpy(departamento, depto, 29); departamento[29] = '\0';

    totalAmenidades = 0;
    capacidadAmenidades = 5;
    amenidades = new char*[capacidadAmenidades];

    for (int i = 0; i < 365; i++) {
        disponibilidad[i] = false; // todo está libre al principio
    }
}

Alojamiento::~Alojamiento() {
    for (int i = 0; i < totalAmenidades; i++) {
        delete[] amenidades[i];
    }
    delete[] amenidades;
}

int Alojamiento::getCodigo() const {
    return codigo;
}

float Alojamiento::getPrecioPorNoche() const {
    return precioPorNoche;
}

const char* Alojamiento::getMunicipio() const {
    return municipio;
}

Anfitrion* Alojamiento::getAnfitrion() const {
    return anfitrion;
}

void Alojamiento::agregarAmenidad(const char* amenidad) {
    if (totalAmenidades == capacidadAmenidades) {
        capacidadAmenidades *= 2;
        char** nuevo = new char*[capacidadAmenidades];
        for (int i = 0; i < totalAmenidades; i++) {
            nuevo[i] = amenidades[i];
        }
        delete[] amenidades;
        amenidades = nuevo;
    }

    amenidades[totalAmenidades] = new char[strlen(amenidad) + 1];
    strcpy(amenidades[totalAmenidades], amenidad);
    totalAmenidades++;
}

void Alojamiento::mostrarDetalles() const {
    printf("Alojamiento #%d\n", codigo);
    printf("Nombre: %s | Tipo: %s | Dirección: %s\n", nombre, tipo, direccion);
    printf("Ubicación: %s - %s | Precio por noche: %.2f\n", municipio, departamento, precioPorNoche);
    printf("Amenidades: ");
    for (int i = 0; i < totalAmenidades; i++) {
        printf("%s", amenidades[i]);
        if (i < totalAmenidades - 1) printf(", ");
    }
    printf("\n");
}

bool Alojamiento::estaDisponible(int diaDelAnio, int noches) const {
    for (int i = diaDelAnio; i < diaDelAnio + noches && i < 365; i++) {
        if (disponibilidad[i]) return false;
    }
    return true;
}

void Alojamiento::reservar(int diaDelAnio, int noches) {
    for (int i = diaDelAnio; i < diaDelAnio + noches && i < 365; i++) {
        disponibilidad[i] = true;
    }
}

void Alojamiento::mostrarReservas() {
    printf("[Pendiente de implementar: conexión con lista de reservaciones]\n");
}
