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
    void mostrarReservacionesHuesped(Huesped* h);



public:
    Plataforma();
    ~Plataforma();

    void login();
    void menuHuesped(Huesped*);
    void menuAnfitrion(Anfitrion* anfitrion);

    void buscarAlojamientos();
    void crearReservacion(Huesped*);
    void anularReservacion();
    void consultarReservasAnfitrion(Anfitrion*);
    void actualizarHistorico();
    void medirRecursos();

    void cargarDatos();
    void guardarDatos();
    void guardarDatosReservas();
    void cargarDatosReservas();
    void cargarDatosAlojamientos();
    void cargarDatosAnfitriones();

    void mostrarTodasReservacionesAnfitrion(Anfitrion* a);
    void cancelarReservacionAnfitrion(Anfitrion* a);
    void actualizarHistoricoAutomatico();


    Huesped* buscarHuesped(const char* doc);
    Alojamiento* buscarAlojamiento(int cod);

    Huesped* loginHuesped();
    Anfitrion* loginAnfitrion();
    Anfitrion* buscarAnfitrion(const char* doc);
};

#endif
