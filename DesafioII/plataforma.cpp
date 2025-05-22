// Plataforma.cpp (completo sin STL)
#include "Plataforma.h"
#include "utilidades.h"
#include <cstdio>
#include <cstring>

// Constructor
Plataforma::Plataforma() {
    totalHuespedes = 0; capacidadHuespedes = 5;
    huespedes = new Huesped*[capacidadHuespedes];

    totalAnfitriones = 0; capacidadAnfitriones = 5;
    anfitriones = new Anfitrion*[capacidadAnfitriones];

    totalAlojamientos = 0; capacidadAlojamientos = 10;
    alojamientos = new Alojamiento*[capacidadAlojamientos];

    totalReservaciones = 0; capacidadReservaciones = 20;
    reservaciones = new Reservacion*[capacidadReservaciones];

    iteraciones = 0;
}

// Destructor
Plataforma::~Plataforma() {
    for (int i = 0; i < totalHuespedes; i++) delete huespedes[i];
    delete[] huespedes;

    for (int i = 0; i < totalAnfitriones; i++) delete anfitriones[i];
    delete[] anfitriones;

    for (int i = 0; i < totalAlojamientos; i++) delete alojamientos[i];
    delete[] alojamientos;

    for (int i = 0; i < totalReservaciones; i++) delete reservaciones[i];
    delete[] reservaciones;
}

// Métodos de expansión
void Plataforma::expandirHuespedes() {
    capacidadHuespedes *= 2;
    Huesped** nuevo = new Huesped*[capacidadHuespedes];
    for (int i = 0; i < totalHuespedes; i++) nuevo[i] = huespedes[i];
    delete[] huespedes;
    huespedes = nuevo;
}

void Plataforma::expandirAnfitriones() {
    capacidadAnfitriones *= 2;
    Anfitrion** nuevo = new Anfitrion*[capacidadAnfitriones];
    for (int i = 0; i < totalAnfitriones; i++) nuevo[i] = anfitriones[i];
    delete[] anfitriones;
    anfitriones = nuevo;
}

void Plataforma::expandirAlojamientos() {
    capacidadAlojamientos *= 2;
    Alojamiento** nuevo = new Alojamiento*[capacidadAlojamientos];
    for (int i = 0; i < totalAlojamientos; i++) nuevo[i] = alojamientos[i];
    delete[] alojamientos;
    alojamientos = nuevo;
}

void Plataforma::expandirReservaciones() {
    capacidadReservaciones *= 2;
    Reservacion** nuevo = new Reservacion*[capacidadReservaciones];
    for (int i = 0; i < totalReservaciones; i++) nuevo[i] = reservaciones[i];
    delete[] reservaciones;
    reservaciones = nuevo;
}

// Funciones del sistema
void Plataforma::login() {
    char documento[15];
    printf("\n Ingrese su número de documento: ");
    scanf("%s", documento);

    for (int i = 0; i < totalHuespedes; i++) {
        if (strcmp(huespedes[i]->getDocumento(), documento) == 0) {
            printf("Bienvenido huésped.\n");
            menuHuesped(huespedes[i]);
            return;
        }
    }

    for (int i = 0; i < totalAnfitriones; i++) {
        if (strcmp(anfitriones[i]->getDocumento(), documento) == 0) {
            printf("Bienvenido anfitrión.\n");
            menuAnfitrion(anfitriones[i]);
            return;
        }
    }

    printf("Usuario no encontrado.\n");
}

void Plataforma::menuHuesped(Huesped* h) {
    int opcion;
    do {
        printf("\n--- Menú Huésped ---\n");
        printf("1. Buscar y reservar alojamiento\n2. Anular reservación\n3. Ver mis reservaciones\n4. Salir\nSeleccione una opción: ");
        scanf("%d", &opcion);

        if (opcion == 1) buscarAlojamientos();
        else if (opcion == 2) anularReservacion();
        else if (opcion == 3) h->mostrarReservas();
    } while (opcion != 4);
}

void Plataforma::menuAnfitrion(Anfitrion* a) {
    int opcion;
    do {
        printf("\n--- Menú Anfitrión ---\n");
        printf("1. Consultar reservaciones activas\n2. Actualizar histórico\n3. Salir\nSeleccione una opción: ");
        scanf("%d", &opcion);

        if (opcion == 1) consultarReservasAnfitrion(a);
        else if (opcion == 2) actualizarHistorico();
    } while (opcion != 3);
}

void Plataforma::medirRecursos() {
    int memoria = totalHuespedes * sizeof(Huesped) +
                  totalAnfitriones * sizeof(Anfitrion) +
                  totalAlojamientos * sizeof(Alojamiento) +
                  totalReservaciones * sizeof(Reservacion);

    printf("\n🧠 Recursos del sistema:\n");
    printf("Total de iteraciones: %d\n", iteraciones);
    printf("Memoria usada: %d bytes\n", memoria);
}

void Plataforma::anularReservacion() {
    int codigo;
    printf("\n Anulación de reservación\nIngrese el código de la reservación a anular: ");
    scanf("%d", &codigo);

    for (int i = 0; i < totalReservaciones; i++) {
        if (reservaciones[i]->getCodigo() == codigo) {
            Fecha inicio = reservaciones[i]->getFechaInicio();
            int diaInicio = calcularDiaDelAnio(inicio);
            reservaciones[i]->getAlojamiento()->liberar(diaInicio, reservaciones[i]->getDuracion());
            delete reservaciones[i];
            for (int j = i; j < totalReservaciones - 1; j++)
                reservaciones[j] = reservaciones[j + 1];
            totalReservaciones--;
            printf("Reservación anulada correctamente.\n");
            return;
        }
    }
    printf(" No se encontró una reservación con ese código.\n");
}

void Plataforma::consultarReservasAnfitrion(Anfitrion* a) {
    int d1, m1, a1, d2, m2, a2;
    printf("Ingrese la fecha de inicio (DD MM AAAA): ");
    scanf("%d %d %d", &d1, &m1, &a1);
    printf("Ingrese la fecha de fin (DD MM AAAA): ");
    scanf("%d %d %d", &d2, &m2, &a2);

    Fecha inicio(d1, m1, a1);
    Fecha fin(d2, m2, a2);

    for (int i = 0; i < totalReservaciones; i++) {
        Reservacion* r = reservaciones[i];
        if (r->getAlojamiento()->getAnfitrion() == a &&
            r->getFechaInicio().comparar(inicio) >= 0 &&
            r->getFechaInicio().comparar(fin) <= 0) {
            r->mostrarResumen();
        }
    }
}

void Plataforma::actualizarHistorico() {
    int d, m, a;
    printf("Ingrese la fecha de corte (DD MM AAAA): ");
    scanf("%d %d %d", &d, &m, &a);
    Fecha corte(d, m, a);

    FILE* archivo = fopen("data/reservas_historicas.txt", "a");
    if (!archivo) {
        printf("Error al abrir el archivo de histórico.\n");
        return;
    }

    int i = 0;
    while (i < totalReservaciones) {
        Reservacion* r = reservaciones[i];
        Fecha inicio = r->getFechaInicio();
        Fecha fin = inicio;
        fin.sumarDias(r->getDuracion());

        if (fin.comparar(corte) < 0) {
            char fechaTxt[15];
            inicio.aCadena(fechaTxt);
            fprintf(archivo, "%d,%s,%d,%s,%.2f,%s\n",
                    r->getCodigo(), fechaTxt, r->getDuracion(),
                    r->getMetodoPago(), r->getMonto(), r->getNotas());

            int diaInicio = calcularDiaDelAnio(inicio);
            r->getAlojamiento()->liberar(diaInicio, r->getDuracion());

            delete reservaciones[i];
            for (int j = i; j < totalReservaciones - 1; j++)
                reservaciones[j] = reservaciones[j + 1];
            totalReservaciones--;
        } else {
            i++;
        }
    }

    fclose(archivo);
    printf(" Reservaciones antiguas archivadas correctamente.\n");
}

void Plataforma::cargarDatos() {
    FILE* f = fopen("data/huespedes.txt", "r");
    if (!f) return;
    char doc[15]; int ant; float punt;
    while (fscanf(f, "%[^,],%d,%f\n", doc, &ant, &punt) == 3) {
        if (totalHuespedes == capacidadHuespedes) expandirHuespedes();
        huespedes[totalHuespedes++] = new Huesped(doc, ant, punt);
    }
    fclose(f);
}

void Plataforma::guardarDatos() {
    FILE* f = fopen("data/huespedes.txt", "w");
    if (!f) return;
    for (int i = 0; i < totalHuespedes; i++) {
        fprintf(f, "%s,%d,%.1f\n",
                huespedes[i]->getDocumento(),
                huespedes[i]->getAntiguedad(),
                huespedes[i]->getPuntuacion());
    }
    fclose(f);
}
void Plataforma::buscarAlojamientos() {
    int d, m, a, noches;
    char municipio[30];
    float precioMax;
    float puntuacionMin;

    printf("Ingrese la fecha de inicio (DD MM AAAA): ");
    scanf("%d %d %d", &d, &m, &a);
    printf("Ingrese el municipio: ");
    scanf("%s", municipio);
    printf("Ingrese la cantidad de noches: ");
    scanf("%d", &noches);

    printf("¿Desea aplicar filtro de precio máximo por noche? (1 = Sí, 0 = No): ");
    int filtroPrecio;
    scanf("%d", &filtroPrecio);
    if (filtroPrecio) {
        printf("Ingrese el precio máximo: ");
        scanf("%f", &precioMax);
    }

    printf("¿Desea aplicar filtro de puntuación mínima del anfitrión? (1 = Sí, 0 = No): ");
    int filtroPunt;
    scanf("%d", &filtroPunt);
    if (filtroPunt) {
        printf("Ingrese la puntuación mínima: ");
        scanf("%f", &puntuacionMin);
    }

    Fecha fechaInicio(d, m, a);
    int diaInicio = calcularDiaDelAnio(fechaInicio);

    int encontrados = 0;
    printf("\nAlojamientos disponibles:\n");
    for (int i = 0; i < totalAlojamientos; i++) {
        Alojamiento* al = alojamientos[i];
        bool coincideMunicipio = strcmp(al->getMunicipio(), municipio) == 0;
        bool cumplePrecio = !filtroPrecio || al->getPrecioPorNoche() <= precioMax;
        bool cumplePunt = !filtroPunt || al->getAnfitrion()->getPuntuacion() >= puntuacionMin;
        bool disponible = al->estaDisponible(diaInicio, noches);

        if (coincideMunicipio && cumplePrecio && cumplePunt && disponible) {
            printf("Código: %d | %s | $%.2f/noche | %.1f estrellas\n",
                   al->getCodigo(), al->getNombre(), al->getPrecioPorNoche(),
                   al->getAnfitrion()->getPuntuacion());
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron alojamientos disponibles bajo esos criterios.\n");
    }
}
