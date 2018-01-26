#ifndef LISTA_S_H
#define LISTA_S_H
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

#endif // LISTA_S_H
