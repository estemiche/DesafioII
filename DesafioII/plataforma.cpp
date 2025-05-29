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
    printf("\n Ingrese su numero de documento: ");
    scanf("%s", documento);

    for (int i = 0; i < totalHuespedes; i++) {
        if (strcmp(huespedes[i]->getDocumento(), documento) == 0) {
            printf("Bienvenido huesped.\n");
            menuHuesped(huespedes[i]);
            return;
        }
    }

    for (int i = 0; i < totalAnfitriones; i++) {
        if (strcmp(anfitriones[i]->getDocumento(), documento) == 0) {
            printf("Bienvenido anfitrion.\n");
            menuAnfitrion(anfitriones[i]);
            return;
        }
    }

    printf("Usuario no encontrado.\n");
}


void Plataforma::menuHuesped(Huesped* h) {
    int opcion;
    do {
        printf("\n--- Menu Huesped ---\n");
        printf("1. Buscar y reservar alojamiento\n"
               "2. Anular reservacion\n"
               "3. Ver mis reservaciones\n"
               "4. Salir\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1) crearReservacion(h);
        else if (opcion == 2) anularReservacion();
        else if (opcion == 3) mostrarReservacionesHuesped(h); // ← CORRECCIÓN

    } while (opcion != 4);
}
void Plataforma::mostrarReservacionesHuesped(Huesped* h) {
    printf("\n=== Mis Reservaciones ===\n");
    int encontradas = 0;

    for (int i = 0; i < totalReservaciones; i++) {
        if (reservaciones[i]->getHuesped() == h) {
            printf("\n--- Reservacion %d ---\n", reservaciones[i]->getCodigo());
            reservaciones[i]->mostrarResumen();
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("No tienes reservaciones activas.\n");
    } else {
        printf("\nTotal de reservaciones: %d\n", encontradas);
    }
}

void Plataforma::cancelarReservacionAnfitrion(Anfitrion* a) {
    // Mostrar las reservaciones del anfitrión
    printf("\n=== Reservaciones que puedes cancelar ===\n");
    int encontradas = 0;

    for (int i = 0; i < totalReservaciones; i++) {
        if (reservaciones[i]->getAlojamiento()->getAnfitrion() == a) {
            printf("Codigo: %d | Alojamiento: %s\n",
                   reservaciones[i]->getCodigo(),
                   reservaciones[i]->getAlojamiento()->getNombre());
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("No tienes reservaciones para cancelar.\n");
        return;
    }

    int codigo;
    printf("\nIngrese el codigo de la reservacion a cancelar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < totalReservaciones; i++) {
        if (reservaciones[i]->getCodigo() == codigo &&
            reservaciones[i]->getAlojamiento()->getAnfitrion() == a) {

            // Liberar las fechas en el alojamiento
            Fecha inicio = reservaciones[i]->getFechaInicio();
            int diaInicio = calcularDiaDelAnio(inicio);
            reservaciones[i]->getAlojamiento()->liberar(diaInicio, reservaciones[i]->getDuracion());

            // Eliminar la reservación
            delete reservaciones[i];
            for (int j = i; j < totalReservaciones - 1; j++)
                reservaciones[j] = reservaciones[j + 1];
            totalReservaciones--;

            // Guardar automáticamente los cambios
            guardarDatosReservas();

            printf("Reservacion cancelada correctamente.\n");
            return;
        }
    }
    printf("No se encontro una reservacion con ese codigo o no es tuya.\n");
}


void Plataforma::menuAnfitrion(Anfitrion* a) {
    int opcion;
    do {
        printf("\n--- Menu Anfitrion ---\n");
        printf("1. Ver mis reservaciones\n");
        printf("2. Cancelar una reservacion\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1) {

            consultarReservasAnfitrion(a);
        }
        else if (opcion == 2) {
            cancelarReservacionAnfitrion(a);
        }
        else if (opcion != 3) {
            printf("Opción inválida.\n");
        }

    } while (opcion != 3);
}
void Plataforma::mostrarTodasReservacionesAnfitrion(Anfitrion* a) {
    printf("\n=== Mis Reservaciones ===\n");
    int encontradas = 0;

    for (int i = 0; i < totalReservaciones; i++) {
        if (reservaciones[i]->getAlojamiento()->getAnfitrion() == a) {
            printf("\n--- Reservacion %d ---\n", reservaciones[i]->getCodigo());
            reservaciones[i]->mostrarResumen();
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("No tienes reservaciones activas.\n");
    } else {
        printf("\nTotal de reservaciones: %d\n", encontradas);
    }
}
void Plataforma::medirRecursos() {
    int memoria = totalHuespedes * sizeof(Huesped) +
                  totalAnfitriones * sizeof(Anfitrion) +
                  totalAlojamientos * sizeof(Alojamiento) +
                  totalReservaciones * sizeof(Reservacion);

    printf("\n Recursos del sistema:\n");
    printf("Total de iteraciones: %d\n", iteraciones);
    printf("Memoria usada: %d bytes\n", memoria);
}

void Plataforma::anularReservacion() {
    int codigo;
    printf("\n Anulacion de reservacion\n"
           "Ingrese el codigo de la reservacion a anular: ");
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
            guardarDatosReservas();
            printf("Reservacion anulada correctamente.\n");
            return;
        }
    }
    printf(" No se encontro una reservacion con ese codigo.\n");
}

void Plataforma::consultarReservasAnfitrion(Anfitrion* a) {
    int d1, m1, a1, d2, m2, a2;
    printf("Ingrese la fecha de inicio (DD MM AAAA): ");
    scanf("%d %d %d", &d1, &m1, &a1);
    printf("Ingrese la fecha de fin (DD MM AAAA): ");
    scanf("%d %d %d", &d2, &m2, &a2);

    Fecha inicio(d1, m1, a1);
    Fecha fin(d2, m2, a2);

    printf("\n=== Reservaciones del Anfitrion ===\n");
    int encontradas = 0;

    for (int i = 0; i < totalReservaciones; i++) {
        Reservacion* r = reservaciones[i];

        // Debug: mostrar información de comparación
        bool esDelAnfitrion = (r->getAlojamiento()->getAnfitrion() == a);
        bool estaEnRango = (r->getFechaInicio().comparar(inicio) >= 0 &&
                            r->getFechaInicio().comparar(fin) <= 0);

        if (esDelAnfitrion && estaEnRango) {
            printf("\n--- Reservacion %d ---\n", r->getCodigo());
            r->mostrarResumen();
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("No se encontraron reservaciones en el rango de fechas especificado.\n");
        printf("Total de reservaciones en el sistema: %d\n", totalReservaciones);

        // Debug: mostrar cuántas reservaciones tiene este anfitrión
        int totalAnfitrion = 0;
        for (int i = 0; i < totalReservaciones; i++) {
            if (reservaciones[i]->getAlojamiento()->getAnfitrion() == a) {
                totalAnfitrion++;
            }
        }
        printf("Reservaciones del anfitrion (todas las fechas): %d\n", totalAnfitrion);
    } else {
        printf("\nTotal encontradas: %d\n", encontradas);
    }
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
void Plataforma::cargarDatosAlojamientos() {
    FILE* f = fopen("data/alojamientos.txt", "r");
    if (!f) {
        printf("No se pudo abrir data/alojamientos.txt\n");
        return;
    }

    int cod;
    char nom[50], tip[20], dir[100], muni[30], depto[30];
    float precio;
    char docAnfitrion[15];

    while (fscanf(f, "%d,%49[^,],%19[^,],%99[^,],%29[^,],%29[^,],%f,%14[^\n]",
                  &cod, nom, tip, dir, muni, depto, &precio, docAnfitrion) == 8) {

        Anfitrion* a = buscarAnfitrion(docAnfitrion);
        if (!a) {
            printf("Anfitrion %s no encontrado. Alojamiento %d omitido.\n", docAnfitrion, cod);
            continue;
        }

        if (totalAlojamientos == capacidadAlojamientos)
            expandirAlojamientos();

        alojamientos[totalAlojamientos++] = new Alojamiento(
            cod, nom, tip, dir, muni, depto, precio, a
            );
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
void Plataforma::guardarDatosReservas() {


    // Guardar las reservas activas
    FILE* f = fopen("data/reservas_activas.txt", "w");
    if (!f) {
        printf("Error al guardar reservaciones.\n");
        return;
    }

    for (int i = 0; i < totalReservaciones; i++) {
        Reservacion* r = reservaciones[i];
        char fechaStr[15];
        r->getFechaInicio().aCadena(fechaStr);
        fprintf(f, "%d,%s,%d,%d,%s,%s,%.2f,%s\n",
                r->getCodigo(), fechaStr, r->getDuracion(),
                r->getAlojamiento()->getCodigo(),
                r->getHuesped()->getDocumento(), r->getMetodoPago(),
                r->getMonto(), r->getNotas());
    }

    fclose(f);
    printf("Reservaciones guardadas correctamente.\n");
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

    printf("¿Desea aplicar filtro de precio maximo por noche? "
           "(1 = Sí, 0 = No): ");
    int filtroPrecio;
    scanf("%d", &filtroPrecio);
    if (filtroPrecio) {
        printf("Ingrese el precio maximo: ");
        scanf("%f", &precioMax);
    }

    printf("¿Desea aplicar filtro de puntuacion minima del anfitrion? (1 = Si, 0 = No): ");
    int filtroPunt;
    scanf("%d", &filtroPunt);
    if (filtroPunt) {
        printf("Ingrese la puntuacion minima: ");
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
void Plataforma::crearReservacion(Huesped* h) {
    int d, m, a, noches;
    char municipio[30];

    printf("\n Reservar alojamiento\n");
    printf("Ingrese la fecha de inicio (DD MM AAAA): ");
    scanf("%d %d %d", &d, &m, &a);
    printf("Ingrese el municipio:");
    scanf("%s", municipio);
    printf("Ingrese la cantidad de noches: ");
    scanf("%d", &noches);

    Fecha fechaInicio(d, m, a);
    int diaInicio = calcularDiaDelAnio(fechaInicio);

    // Mostrar alojamientos disponibles
    printf("\nAlojamientos disponibles en %s:\n", municipio);
    int disponibles = 0;
    for (int i = 0; i < totalAlojamientos; i++) {
        Alojamiento* al = alojamientos[i];
        if (strcmp(al->getMunicipio(), municipio) == 0 && al->estaDisponible(diaInicio, noches)) {
            printf("Codigo: %d | %s | $%.2f/noche | %.1f estrellas\n",
                   al->getCodigo(), al->getNombre(), al->getPrecioPorNoche(),
                   al->getAnfitrion()->getPuntuacion());
            disponibles++;
        }
    }

    if (disponibles == 0) {
        printf("No hay alojamientos disponibles.\n");
        return;
    }

    // Seleccionar alojamiento por código
    int codigoSel;
    printf("Ingrese el codigo del alojamiento que desea reservar: ");
    scanf("%d", &codigoSel);

    Alojamiento* elegido = nullptr;
    for (int i = 0; i < totalAlojamientos; i++) {
        if (alojamientos[i]->getCodigo() == codigoSel) {
            elegido = alojamientos[i];
            break;
        }
    }

    if (!elegido || !elegido->estaDisponible(diaInicio, noches)) {
        printf("Alojamiento no valido o no disponible.\n");
        return;
    }

    // Validar que el huésped no tenga otra reserva en conflicto
    for (int i = 0; i < totalReservaciones; i++) {
        if (reservaciones[i]->getHuesped() == h) {
            int inicioExistente = calcularDiaDelAnio(reservaciones[i]->getFechaInicio());
            int dur = reservaciones[i]->getDuracion();
            for (int d1 = diaInicio; d1 < diaInicio + noches; d1++) {
                for (int d2 = inicioExistente; d2 < inicioExistente + dur; d2++) {
                    if (d1 == d2) {
                        printf("Ya tiene una reservacion en esa fecha.\n");
                        return;
                    }
                }
            }
        }
    }

    // Capturar método de pago y notas
    char metodoPago[20];
    char notas[1001];
    float monto = noches * elegido->getPrecioPorNoche();

    printf("Metodo de pago (PSE o Tarjeta de Credito): ");
    scanf("%s", metodoPago);
    printf("Notas (opcional, maximo 1000 caracteres): ");
    getchar(); // Limpiar salto
    fgets(notas, 1000, stdin);
    size_t len = strlen(notas);
    if (len > 0 && notas[len - 1] == '\n') notas[len - 1] = '\0';

    // Crear reservación
    if (totalReservaciones == capacidadReservaciones) expandirReservaciones();
    int nuevoCodigo = totalReservaciones + 1001;

    Reservacion* nuevaReserva = new Reservacion(nuevoCodigo, fechaInicio, noches,
                                                metodoPago, monto, notas, h, elegido);
    reservaciones[totalReservaciones++] = nuevaReserva;

    elegido->reservar(diaInicio, noches);

    // AGREGAR ESTA LÍNEA: Asociar la reservación al huésped
    h->agregarReservacion(nuevaReserva);

    printf("Reservacion creada con exito.\n");
    printf("Codigo: %d | Inicio: %02d/%02d/%04d | Noches: %d | Monto: $%.2f\n",
           nuevoCodigo, d, m, a, noches, monto);
    guardarDatosReservas();
}
// Función buscarHuesped por documento
Huesped* Plataforma::buscarHuesped(const char* doc) {
    for (int i = 0; i < totalHuespedes; i++) {
        if (strcmp(huespedes[i]->getDocumento(), doc) == 0)
            return huespedes[i];
    }
    return nullptr;
}

// Función buscarAlojamiento por código
Alojamiento* Plataforma::buscarAlojamiento(int cod) {
    for (int i = 0; i < totalAlojamientos; i++) {
        if (alojamientos[i]->getCodigo() == cod)
            return alojamientos[i];
    }
    return nullptr;
}

// Función cargarDatosReservas
void Plataforma::cargarDatosReservas() {
    FILE* f = fopen("data/reservas_activas.txt", "r");
    if (!f) {
        printf("No se pudo cargar reservaciones activas.\n");
        return;
    }

    int cod, duracion, codAloj;
    char fechaTxt[15], docHuesped[15];
    char metodo[20], notas[1001];
    float monto;

    while (fscanf(f, "%d,%[^,],%d,%d,%[^,],%[^,],%f,%[^\n]",
                  &cod, fechaTxt, &duracion, &codAloj,
                  docHuesped, metodo, &monto, notas) == 8) {

        Fecha fecha = Fecha::desdeCadena(fechaTxt);
        Huesped* h = buscarHuesped(docHuesped);
        Alojamiento* a = buscarAlojamiento(codAloj);

        if (h && a) {
            if (totalReservaciones == capacidadReservaciones) expandirReservaciones();

            Reservacion* nuevaReserva = new Reservacion(cod, fecha, duracion, metodo, monto, notas, h, a);
            reservaciones[totalReservaciones++] = nuevaReserva;

            int diaInicio = calcularDiaDelAnio(fecha);
            a->reservar(diaInicio, duracion);


            h->agregarReservacion(nuevaReserva);
        }
    }
    fclose(f);
}
// Plataforma.cpp
Huesped* Plataforma::loginHuesped() {
    char doc[15];
    printf("\nIngrese su numero de documento: ");
    scanf("%s", doc);
    for (int i = 0; i < totalHuespedes; i++) {
        if (strcmp(huespedes[i]->getDocumento(), doc) == 0) {
            printf("Bienvenido huesped.\n");
            return huespedes[i];
        }
    }
    printf("Huesped no encontrado.\n");
    return nullptr;
}

Anfitrion* Plataforma::loginAnfitrion() {
    char doc[15];
    printf("\nIngrese su numero de documento: ");
    scanf("%s", doc);
    for (int i = 0; i < totalAnfitriones; i++) {
        if (strcmp(anfitriones[i]->getDocumento(), doc) == 0) {
            printf("Bienvenido anfitrion.\n");
            return anfitriones[i];
        }
    }
    printf("Anfitrion no encontrado.\n");
    return nullptr;
}
Anfitrion* Plataforma::buscarAnfitrion(const char* doc) {
    for (int i = 0; i < totalAnfitriones; i++) {
        if (strcmp(anfitriones[i]->getDocumento(), doc) == 0)
            return anfitriones[i];
    }
    return nullptr;
}
void Plataforma::cargarDatosAnfitriones() {
    FILE* f = fopen("data/anfitriones.txt", "r");
    if (!f) {
        printf("No se pudo abrir data/anfitriones.txt\n");
        return;
    }

    char doc[15];
    int antig;
    float punt;

    while (fscanf(f, "%[^,],%d,%f\n", doc, &antig, &punt) == 3) {
        if (totalAnfitriones == capacidadAnfitriones) expandirAnfitriones();
        anfitriones[totalAnfitriones++] = new Anfitrion(doc, antig, punt);
    }

    fclose(f);

}
void Plataforma::actualizarHistoricoAutomatico() {
    FILE* archivo = fopen("data/reservas_historicas.txt", "a");
    if (!archivo) {
        return;
    }

    int i = 0;
    int movidas = 0;

    // Solo archiva reservas que tengan más de 365 días desde inicio del año
    while (i < totalReservaciones) {
        Reservacion* r = reservaciones[i];
        Fecha inicio = r->getFechaInicio();
        int diaInicio = calcularDiaDelAnio(inicio);
        int duracion = r->getDuracion();
        int diaFin = diaInicio + duracion;


        if (diaFin < 100) {
            char fechaTxt[15];
            inicio.aCadena(fechaTxt);
            fprintf(archivo, "%d,%s,%d,%s,%.2f,%s\n",
                    r->getCodigo(), fechaTxt, r->getDuracion(),
                    r->getMetodoPago(), r->getMonto(), r->getNotas());

            delete reservaciones[i];
            for (int j = i; j < totalReservaciones - 1; j++)
                reservaciones[j] = reservaciones[j + 1];
            totalReservaciones--;
            movidas++;
        } else {
            i++;
        }
    }

    fclose(archivo);


}
