#ifndef LISTA_S_H
#define LISTA_S_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo_s.h"
#define digraph_ls "digraph lista_simple {"

typedef struct Lista_s {
    Nodo_s *primero;
    Nodo_s *ultimo;
} Lista_s;

int agregar_recursivo_s(Nodo_s *a, Nodo_s *s, Nodo_s *d) {
    if (strcasecmp(s->valor, d->valor) > 0) {
        d->siguiente = s;
        a->siguiente = d;

        return 1;
    }
    else if (strcasecmp(s->valor, d->valor) == 0 || strcasecmp(a->valor, d->valor) == 0) {
        return 0;
    }
    else
    {
        return agregar_recursivo_s(s, s->siguiente, d);
    }
}

Nodo_s *buscar_recursivo_s(Nodo_s *n, char *d) {
    if (n != NULL) {
        if (strcasecmp(n->valor, d) == 0) {
            return n;
        }
        else if (strcasecmp(d, n->valor) > 0) {
            return buscar_recursivo_s(n->siguiente, d);
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}

Nodo_s *buscar_anterior_s(Nodo_s *a, Nodo_s *n) {
    if (a != NULL) {
        if (a->siguiente == n) {
            return a;
        }
        else {
            return buscar_anterior_s(a->siguiente, n);
        }
    }
    else {
        return NULL;
    }
}

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

    return (*l);
}

void agregar_s(Lista_s *l, char *dato) {
    Nodo_s *d = nuevoNodo_s();
    d->valor = (char*)malloc(sizeof(dato));
    strcpy(d->valor, dato);

    if (l->primero == NULL) {
        l->primero = l->ultimo = d;
        printf("Se insertó %s con exito.\n", dato);
        return;
    }

    if (strcasecmp(l->primero->valor, dato) > 0) {
        d->siguiente = l->primero;
        l->primero = d;
        printf("Se insertó %s con exito.\n", dato);
    }
    else if (strcasecmp(dato, l->ultimo->valor) > 0) {
        l->ultimo->siguiente = d;
        l->ultimo = d;
        printf("Se insertó %s con exito.\n", dato);
    }
    else {
        if (agregar_recursivo_s(l->primero, l->primero->siguiente, d) == 0) {
            d = liberarNodo_s(&d);
            printf("No se insertó %s.\n", dato);
        }
        else {
            printf("Se insertó %s con exito.\n", dato);
        }
    }
}

int graficar_s(Lista_s *l) {
    Nodo_s *temp = l->primero;
    FILE *file;
    file = fopen("lista_simple.dot", "w+");
    if (file != NULL) {
        fprintf(file, "%s\n", digraph_ls);
        fflush(file);

        while (temp != NULL) {
            fprintf(file, "%s [label=\"%s\"];\n", temp->valor, temp->valor);
            fflush(file);

            if (temp->siguiente != NULL) {
                fprintf(file, "%s -> %s;\n", temp->valor, temp->siguiente->valor);
                fflush(file);
            }
            temp = temp->siguiente;
        }

        fprintf(file, "}");
        fflush(file);

        system("dot -Tpng -o lista_simple.png lista_simple.dot");
        fclose(file);
        return 1;
    }
    else {
        return 0;
    }
}

Nodo_s *buscar_s(Lista_s *l, char *d) {
    if (l->primero != NULL || l->ultimo != NULL)  {
        if (strcasecmp(d, l->primero->valor) > 0 && strcasecmp(l->ultimo->valor, d) > 0) {
            return buscar_recursivo_s(l->primero, d);
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}

int eliminar_s(Lista_s *l, char *d) {
    Nodo_s *n = buscar_s(l, d);
    if (n != NULL) {
        if (l->primero == n) {
            l->primero = l->primero->siguiente;
            n = liberarNodo_s(&n);
            return 1;
        }
        else {
            Nodo_s *a = buscar_anterior_s(l->primero, n);
            a->siguiente = n->siguiente;
            if (l->ultimo == n) {
                l->ultimo = a;
            }
            n = liberarNodo_s(&n);
            return 1;
        }
    }
    else {
        return 0;
    }
}

#endif // LISTA_S_H
