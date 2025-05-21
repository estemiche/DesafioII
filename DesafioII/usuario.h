#ifndef USUARIO_H
#define USUARIO_H


class Usuario {
protected:
    char documento[15];
    int antiguedad; // en meses
    float puntuacion; // de 0 a 5

public:
    Usuario(const char* doc = "", int ant = 0, float punt = 0.0f);
    Usuario(const Usuario& other);
    virtual ~Usuario();

    // Getters
    const char* getDocumento() const;
    int getAntiguedad() const;
    float getPuntuacion() const;

    // Setters
    void setPuntuacion(float);

    // Métodos virtuales
    virtual void mostrarDatos() const = 0;
};

#endif
