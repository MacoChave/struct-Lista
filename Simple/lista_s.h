#ifndef LISTA_S_H
#define LISTA_S_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo_s.h"

typedef struct Lista_s {
    Nodo_s *primero;
    Nodo_s *ultimo;
} Lista_s;

Lista_s *nuevaLista_s() {
    Lista_s *l = (Lista_s*)malloc(sizeof(Lista_s));
    l->primero = NULL;
    l->ultimo = NULL;

    return l;
}

Lista_s *liberarLista_s(Lista_s **l) {
    Nodo_s *temp = (*l)->primero;

    while (temp != NULL) {
        (*l)->primero = temp->siguiente;
        temp = liberarNodo_s(&temp);
        temp = (*l)->primero;
    }

    (*l)->ultimo = NULL;
}

void agregar_s(Nodo_s *p, Nodo_s *u, char *dato) {
    Nodo_s *d = nuevoNodo_s();
    d->valor = (char*)malloc(sizeof(dato));
    strcpy(d->valor, dato);

    if (p == NULL) {
        p = u = d;
        printf("Se insertó &s con exito.\n", dato);
        return;
    }

    if (strcmp(p->valor, dato) > 0) {
        d->siguiente = p;
        p = d;
        printf("Se insertó &s con exito.\n", dato);
    }
    else if (strcmp(dato, u->valor) > 0) {
        u->siguiente = d;
        u = d;
        printf("Se insertó &s con exito.\n", dato);
    }
    else {
        if (agregar_recursivo_s(p, p->siguiente, d) == 1) {
            d = liberarNodo_s(&d);
            printf("No se insertó %s.\n", dato);
        }
        else {
            printf("Se insertó &s con exito.\n", dato);
        }
    }
}

int agregar_recursivo_s(Nodo_s *a, Nodo_s *s, Nodo_s *d) {
    if (strcmp(s->valor, d->valor) > 0) {
        d->siguiente = s;
        a->siguiente = d;

        return 1;
    }
    else if (strcmp(s->valor, d->valor) == 0 || strcmp(a->valor, d->valor) == 0) {
        return 0;
    }
    else
    {
        return agregar_recursivo_s(s, s->siguiente, d);
    }
}

#endif // LISTA_S_H
