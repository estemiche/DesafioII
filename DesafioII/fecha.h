#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    int dia;
    int mes;
    int anio;

    bool esBisiesto(int anio) const;
    int diasDelMes(int mes, int anio) const;

public:
    Fecha(int d = 1, int m = 1, int a = 2025);

    int getDia() const;
    int getMes() const;
    int getAnio() const;
    void setFecha(int d, int m, int a);

    void sumarDias(int dias);
    int comparar(const Fecha& otra) const;
    void mostrarFecha() const;

    void cargarDesdeTexto(const char* texto);
    void aCadena(char* buffer) const;
    static Fecha desdeCadena(const char* texto);
};

#endif
