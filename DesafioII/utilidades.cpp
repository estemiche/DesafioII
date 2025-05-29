// utilidades.cpp
#include "utilidades.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

int calcularDiaDelAnio(const Fecha& f) {
    static int diasPorMes[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int dia = f.getDia(), mes = f.getMes(), anio = f.getAnio();
    int total = dia;
    for (int i = 1; i < mes; i++) {
        total += diasPorMes[i];
    }
    return total - 1;
}

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("Presione ENTER para continuar...");
    getchar();
    getchar();
}

void leerCadena(char* buffer, int tamMax) {
    fgets(buffer, tamMax, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
}
