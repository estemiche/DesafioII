#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "Huesped.h"
#include "Anfitrion.h"
#include "Alojamiento.h"
#include "Reservacion.h"
#include "Fecha.h"

class Plataforma {
private:
    Huesped** huespedes;
    int totalHuespedes, capacidadHuespedes;

    Anfitrion** anfitriones;
    int totalAnfitriones, capacidadAnfitriones;

    Alojamiento** alojamientos;
    int totalAlojamientos, capacidadAlojamientos;

    Reservacion** reservaciones;
    int totalReservaciones, capacidadReservaciones;

    int iteraciones;

    void expandirHuespedes();
    void expandirAnfitriones();
    void expandirAlojamientos();
    void expandirReservaciones();

public:
    Plataforma();
    ~Plataforma();

    void login();
    void menuHuesped(Huesped*);
    void menuAnfitrion(Anfitrion*);

    void buscarAlojamientos();               // A implementar
    void crearReservacion(Huesped*);         // A implementar
    void anularReservacion();
    void consultarReservasAnfitrion(Anfitrion*);
    void actualizarHistorico();
    void medirRecursos();

    void cargarDatos();    // Leer de archivos .txt
    void guardarDatos();   // Escribir en archivos .txt
};

#endif
