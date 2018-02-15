#ifndef LISTA_C_H
#define LISTA_C_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo_c.h"
#define digraph_c "digraph lista_circular {"

typedef struct Lista_c {
    Nodo_c *primero;
    Nodo_c *ultimo;
} Lista_c;


int _agregar_c(Nodo_c *a, Nodo_c *d) {
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
        return _agregar_c(a->siguiente, d);
    }
}

Nodo_c *_buscar_c(Nodo_c *n, char *d) {
    if (n != NULL) {
        if (strcasecmp(n->valor, d) == 0) {
            return n;
        }
        else if (strcasecmp(d, n->valor) > 0) {
            return _buscar_c(n->siguiente, d);
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}

Lista_c *nuevaLista_c() {
    Lista_c *l = (Lista_c*)malloc(sizeof(Lista_c));
    l->primero = NULL;
    l->ultimo = NULL;

    return l;
}

Lista_c *liberarLista_c(Lista_c *l) {
    Nodo_c *temp = l->primero;
    if (temp == NULL)
        return l;

    l->primero->anterior = NULL;
    l->ultimo->siguiente = NULL;

    while (temp != NULL) {
        l->primero = temp->siguiente;
        temp = liberarNodo_c(temp);
        temp = l->primero;
    }

    l->ultimo = NULL;

    return l;
}

void agregar_c(Lista_c *l, char *dato) {
    Nodo_c *d = nuevoNodo_c();
    d->valor = (char*)malloc(sizeof(dato));
    strcpy(d->valor, dato);

    if (l->primero == NULL) {
        l->primero = l->ultimo = d;
        l->primero->anterior = d;
        l->ultimo->siguiente = d;
        printf("Se insertó %s con exito.\n", dato);
        return;
    }

    if (strcasecmp(l->primero->valor, dato) > 0) {
        d->siguiente = l->primero;
        d->anterior = l->ultimo;
        l->primero->anterior = d;
        l->ultimo->siguiente = d;
        l->primero = d;
        printf("Se insertó %s con exito.\n", dato);
    }
    else if (strcasecmp(dato, l->ultimo->valor) > 0) {
        d->anterior = l->ultimo;
        d->siguiente = l->primero;
        l->ultimo->siguiente = d;
        l->primero->anterior = d;
        l->ultimo = d;
        printf("Se insertó %s con exito.\n", dato);
    }
    else {
        if (_agregar_c(l->primero->siguiente, d) == 0) {
            d = liberarNodo_c(d);
            printf("No se insertó %s.\n", dato);
        }
        else {
            printf("Se insertó %s con exito.\n", dato);
        }
    }
}

int graficar_c(Lista_c *l) {
    Nodo_c *temp = l->primero;
    FILE *file;
    file = fopen("Lista_circular.dot", "w");
    if (file != NULL) {
        fprintf(file, "%s\n", digraph_c);
        fprintf(file, "\trankdir = LR\n");
        fprintf(file, "\tnode [shape=record]\n\n");
        fflush(file);

        while (temp != NULL) {
            fprintf(file, "\t%s [label=\"%s\"];\n", temp->valor, temp->valor);
            fflush(file);

            if (temp->siguiente != NULL) {
                fprintf(file, "\t%s -> %s;\n", temp->valor, temp->siguiente->valor);
                fflush(file);
            }

            if (temp->anterior != NULL) {
                fprintf(file, "\t%s -> %s;\n", temp->valor, temp->anterior->valor);
                fflush(file);
            }

            if (temp->siguiente != l->primero) {
                temp = temp->siguiente;
            }
            else {
                temp = NULL;
            }
        }

        fprintf(file, "}");
        fflush(file);

        system("dot -Tpng -o Lista_circular.png Lista_circular.dot");
        fclose(file);
        return 1;
    }
    else {
        return 0;
    }
}

Nodo_c *buscar_c(Lista_c *l, char *d) {
    if (l->primero != NULL || l->ultimo != NULL)  {
        if (strcasecmp(d, l->primero->valor) > 0 && strcasecmp(l->ultimo->valor, d) > 0) {
            return _buscar_c(l->primero, d);
        }
        else {
            if (strcasecmp(l->primero->valor, d) == 0) {
                return l->primero;
            }
            else if (strcasecmp(l->ultimo->valor, d) == 0) {
                return l->ultimo;
            }
            else {
                return NULL;
            }
        }
    }
    else {
        return NULL;
    }
}

int eliminar_c(Lista_c *l, char *d) {
    Nodo_c *n = buscar_c(l, d);
    if (n != NULL) {
        if (l->primero == n) {
            l->primero = l->primero->siguiente;
            l->primero->anterior = l->ultimo;
            l->ultimo->siguiente = l->primero;
            n = liberarNodo_c(n);
            return 1;
        }
        else {
            Nodo_c *a = n->anterior;
            a->siguiente = n->siguiente;
            if (l->ultimo == n) {
                l->primero->anterior = a;
                l->ultimo = a;
            }
            else {
                n->siguiente->anterior = a;
            }
            n = liberarNodo_c(n);
            return 1;
        }
    }
    else {
        return 0;
    }
}

#endif // LISTA_C_H
