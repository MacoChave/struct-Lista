TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    Parser/json.c

HEADERS += \
    Simple/lista_s.h \
    Simple/nodo_s.h \
    Doble/lista_d.h \
    Doble/nodo_d.h \
    Circular/lista_c.h \
    Circular/nodo_c.h \
    Parser/json.h
