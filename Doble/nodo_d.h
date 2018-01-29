#ifndef NODO_D_H
#define NODO_D_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo_d {
    char *valor;
    struct Nodo_d *anterior;
    struct Nodo_d *siguiente;
} Nodo_d;


Nodo_d *nuevoNodo_d() {
    Nodo_d *n = (Nodo_d *)malloc(sizeof(Nodo_d));
    n->valor = NULL;
    n->anterior = NULL;
    n->siguiente = NULL;

    return n;
}

Nodo_d *liberarNodo_d(Nodo_d **n) {
    free((*n)->valor);
    (*n)->valor = NULL;
    (*n)->anterior = NULL;
    (*n)->siguiente = NULL;

    free(*n);
    *n = NULL;

    return *n;
}


#endif // NODO_D_H
