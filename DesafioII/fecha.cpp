#include "Fecha.h"
#include <cstdio>

Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

void Fecha::setFecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
}

bool Fecha::esBisiesto(int anio) const {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int Fecha::diasDelMes(int mes, int anio) const {
    int dias[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (mes == 2 && esBisiesto(anio)) return 29;
    return dias[mes - 1];
}

void Fecha::sumarDias(int dias) {
    while (dias > 0) {
        int diasMes = diasDelMes(mes, anio);
        if (dia + dias <= diasMes) {
            dia += dias;
            break;
        } else {
            dias -= (diasMes - dia + 1);
            dia = 1;
            mes++;
            if (mes > 12) {
                mes = 1;
                anio++;
            }
        }
    }
}

int Fecha::comparar(const Fecha& otra) const {
    if (anio < otra.anio) return -1;
    if (anio > otra.anio) return 1;
    if (mes < otra.mes) return -1;
    if (mes > otra.mes) return 1;
    if (dia < otra.dia) return -1;
    if (dia > otra.dia) return 1;
    return 0;
}

void Fecha::mostrarFecha() const {
    printf("%02d/%02d/%04d", dia, mes, anio);
}

void Fecha::cargarDesdeTexto(const char* texto) {
    sscanf(texto, "%d/%d/%d", &dia, &mes, &anio);
}

void Fecha::aCadena(char* buffer) const {
    sprintf(buffer, "%02d/%02d/%04d", dia, mes, anio);
}
Fecha Fecha::desdeCadena(const char* texto) {
    int d, m, a;
    sscanf(texto, "%d-%d-%d", &d, &m, &a);
    return Fecha(d, m, a);
}
