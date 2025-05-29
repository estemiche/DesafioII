#include "plataforma.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    Plataforma sistema;

    sistema.cargarDatosAnfitriones();
    sistema.cargarDatos();
    sistema.cargarDatosAlojamientos();
    sistema.cargarDatosReservas();



    char buffer[100];
    int opcionPrincipal = 0;

    do {
        printf("\n--- Bienvenido a UdeAStay ---\n");
        printf("1. Ingresar como Huesped\n");
        printf("2. Ingresar como Anfitrion\n");
        printf("3. Salir\nSeleccione una opcion: ");

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Error al leer la entrada. Intente de nuevo.\n");
            continue;
        }

        // Eliminar salto de línea si existe
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        // Validar si es un número
        if (sscanf(buffer, "%d", &opcionPrincipal) != 1) {
            printf("Opcion invalida. Intente nuevamente.\n");
            continue;
        }

        // Procesar opción válida
        if (opcionPrincipal == 1) {
            Huesped* h = sistema.loginHuesped();
            if (h) sistema.menuHuesped(h);
        } else if (opcionPrincipal == 2) {
            Anfitrion* a = sistema.loginAnfitrion();
            if (a) sistema.menuAnfitrion(a);
        } else if (opcionPrincipal != 3) {
            printf("Opcion no valida. Intente nuevamente.\n");
        }

    } while (opcionPrincipal != 3);

    sistema.guardarDatos();
    sistema.guardarDatosReservas();
    sistema.medirRecursos();

    return 0;
}
