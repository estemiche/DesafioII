#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Fecha.h"

// Convierte una fecha a un número entre 0 y 364 (día del año)
int calcularDiaDelAnio(const Fecha& f);

// Limpia pantalla (funcionalidad simple)
void limpiarPantalla();

// Pausa hasta que el usuario presione ENTER
void pausar();

// Leer cadena segura sin STL
void leerCadena(char* buffer, int tamMax);

#endif
