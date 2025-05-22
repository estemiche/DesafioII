TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        alojamiento.cpp \
        anfitrion.cpp \
        fecha.cpp \
        huesped.cpp \
        main.cpp \
        plataforma.cpp \
        reservacion.cpp \
        usuario.cpp

HEADERS += \
    alojamiento.h \
    anfitrion.h \
    fecha.h \
    huesped.h \
    plataforma.h \
    plataforma.h \
    reservacion.h \
    usuario.h \
    utilidades.h

DISTFILES += \
    alojamientos.txt \
    anfitriones.txt \
    huespedes.txt \
    reservas_activas.txt \
    reservas_historicas.txt
