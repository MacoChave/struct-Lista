#ifndef NODO_S_H
#define NODO_S_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo_s {
    char *valor;
    struct Nodo_s *siguiente;
} Nodo_s;

Nodo_s *nuevoNodo_s() {
    Nodo_s *n = (Nodo_s *)malloc(sizeof(Nodo_s));
    n->valor = NULL;
    n->siguiente = NULL;

    return n;
}

Nodo_s *liberarNodo_s(Nodo_s **n) {
    free((*n)->valor);
    (*n)->valor = NULL;
    (*n)->siguiente = NULL;

    free(*n);
    *n = NULL;

    return *n;
}

#endif // NODO_S_H
