#ifndef LISTA_D_H
#define LISTA_D_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo_d.h"
#define digraph_ld "digraph lista_doble {"

typedef struct Lista_d {
    Nodo_d *primero;
    Nodo_d *ultimo;
} Lista_d;


int agregar_recursivo_d(Nodo_d *a, Nodo_d *d) {
    if (strcasecmp(a->valor, d->valor) > 0) {
        d->siguiente = a;
        a->anterior->siguiente = d;
        d->anterior = a->anterior;
        a->anterior = d;

        return 1;
    }
    else if (strcasecmp(a->valor, d->valor) == 0 || strcasecmp(a->anterior->valor, d->valor) == 0) {
        return 0;
    }
    else
    {
        return agregar_recursivo_d(a->siguiente, d);
    }
}

Nodo_d *buscar_recursivo_d(Nodo_d *n, char *d) {
    if (n != NULL) {
        if (strcasecmp(n->valor, d) == 0) {
            return n;
        }
        else if (strcasecmp(d, n->valor) > 0) {
            return buscar_recursivo_d(n->siguiente, d);
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}

Lista_d *nuevaLista_d() {
    Lista_d *l = (Lista_d*)malloc(sizeof(Lista_d));
    l->primero = NULL;
    l->ultimo = NULL;

    return l;
}

Lista_d *liberarLista_d(Lista_d **l) {
    Nodo_d *temp = (*l)->primero;

    while (temp != NULL) {
        (*l)->primero = temp->siguiente;
        temp = liberarNodo_d(&temp);
        temp = (*l)->primero;
    }

    (*l)->ultimo = NULL;

    return (*l);
}

void agregar_d(Lista_d *l, char *dato) {
    Nodo_d *d = nuevoNodo_d();
    d->valor = (char*)malloc(sizeof(dato));
    strcpy(d->valor, dato);

    if (l->primero == NULL) {
        l->primero = l->ultimo = d;
        printf("Se insertó %s con exito.\n", dato);
        return;
    }

    if (strcasecmp(l->primero->valor, dato) > 0) {
        d->siguiente = l->primero;
        l->primero->anterior = d;
        l->primero = d;
        printf("Se insertó %s con exito.\n", dato);
    }
    else if (strcasecmp(dato, l->ultimo->valor) > 0) {
        l->ultimo->siguiente = d;
        d->anterior = l->ultimo;
        l->ultimo = d;
        printf("Se insertó %s con exito.\n", dato);
    }
    else {
        if (agregar_recursivo_d(l->primero->siguiente, d) == 0) {
            d = liberarNodo_d(&d);
            printf("No se insertó %s.\n", dato);
        }
        else {
            printf("Se insertó %s con exito.\n", dato);
        }
    }
}

int graficar_d(Lista_d *l) {
    Nodo_d *temp = l->primero;
    FILE *file;
    file = fopen("lista_doble.dot", "w");
    if (file != NULL) {
        fprintf(file, "%s\n", digraph_ld);
        fflush(file);

        while (temp != NULL) {
            fprintf(file, "%s [label=\"%s\"];\n", temp->valor, temp->valor);
            fflush(file);

            if (temp->anterior != NULL) {
                fprintf(file, "%s -> %s;\n", temp->valor, temp->anterior->valor);
                fflush(file);
            }

            if (temp->siguiente != NULL) {
                fprintf(file, "%s -> %s;\n", temp->valor, temp->siguiente->valor);
                fflush(file);
            }
            temp = temp->siguiente;
        }

        fprintf(file, "}");
        fflush(file);

        system("dot -Tpng -o lista_doble.png lista_doble.dot");
        fclose(file);
        return 1;
    }
    else {
        return 0;
    }
}

Nodo_d *buscar_d(Lista_d *l, char *d) {
    if (l->primero != NULL || l->ultimo != NULL)  {
        if (strcasecmp(d, l->primero->valor) > 0 && strcasecmp(l->ultimo->valor, d) > 0) {
            return buscar_recursivo_d(l->primero, d);
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}

int eliminar_d(Lista_d *l, char *d) {
    Nodo_d *n = buscar_d(l, d);
    if (n != NULL) {
        if (l->primero == n) {
            l->primero = l->primero->siguiente;
            l->primero->anterior = NULL;
            n = liberarNodo_d(&n);
            return 1;
        }
        else {
            Nodo_d *a = n->anterior;
            a->siguiente = n->siguiente;
            if (l->ultimo == n) {
                l->ultimo = a;
            }
            else {
                n->siguiente->anterior = a;
            }
            n = liberarNodo_d(&n);
            return 1;
        }
    }
    else {
        return 0;
    }
}

#endif // LISTA_D_H
