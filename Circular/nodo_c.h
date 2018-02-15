#ifndef NODO_C_H
#define NODO_C_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo_c {
    char *valor;
    struct Nodo_c *anterior;
    struct Nodo_c *siguiente;
} Nodo_c;


Nodo_c *nuevoNodo_c() {
    Nodo_c *n = (Nodo_c *)malloc(sizeof(Nodo_c));
    n->valor = NULL;
    n->anterior = NULL;
    n->siguiente = NULL;

    return n;
}

Nodo_c *liberarNodo_c(Nodo_c *n) {
    free(n->valor);
    n->valor = NULL;
    n->anterior = NULL;
    n->siguiente = NULL;

    free(n);
    n = NULL;

    return n;
}


#endif // NODO_C_H
