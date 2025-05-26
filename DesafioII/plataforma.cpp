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
        else if (opcion == 3) h->mostrarReservas();
    } while (opcion != 4);
}

void Plataforma::menuAnfitrion(Anfitrion* a) {
    int opcion;
    do {
        printf("\n--- Menu Anfitrion ---\n");
        printf("1. Consultar reservaciones activas\n"
               "2. Actualizar histórico\n"
               "3. Salir\nSeleccione una opción: ");
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
        printf("Error al abrir el archivo de historico.\n");
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
// Función guardarDatosReservas()
void Plataforma::guardarDatosReservas() {
    FILE* f = fopen("data/reservaciones.txt", "w");
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

    printf("¿Desea aplicar filtro de puntuación mínima del anfitrion? (1 = Sí, 0 = No): ");
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
    printf("Ingrese el municipio: ");
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
            printf("Código: %d | %s | $%.2f/noche | %.1f estrellas\n",
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
    reservaciones[totalReservaciones++] = new Reservacion(nuevoCodigo, fechaInicio, noches,
                                                          metodoPago, monto, notas, h, elegido);

    elegido->reservar(diaInicio, noches);

    printf("Reservación creada con exito.\n");
    printf("Codigo: %d | Inicio: %02d/%02d/%04d | Noches: %d | Monto: $%.2f\n",
           nuevoCodigo, d, m, a, noches, monto);
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
    FILE* f = fopen("data/reservaciones.txt", "r");
    if (!f) return;

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
            reservaciones[totalReservaciones++] = new Reservacion(cod, fecha, duracion, metodo, monto, notas, h, a);

            int diaInicio = calcularDiaDelAnio(fecha);
            a->reservar(diaInicio, duracion);
            h->agregarReservacion(reservaciones[totalReservaciones - 1]);
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


