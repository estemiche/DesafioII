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
        usuario.cpp \
        utilidades.cpp

HEADERS += \
    alojamiento.h \
    anfitrion.h \
    fecha.h \
    huesped.h \
    plataforma.h \
    reservacion.h \
    usuario.h \
    utilidades.h

DISTFILES += \
    data/alojamientos.txt \
    data/anfitriones.txt \
    data/huespedes.txt \
    data/reservas_activas.txt \
    data/reservas_historicas.txt \
    huespedes.txt
