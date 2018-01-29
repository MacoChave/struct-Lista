#include <stdio.h>
#include "Simple/lista_s.h"
#include "Simple/nodo_s.h"

int main(int argc, char *argv[])
{
    Lista_s *lista = nuevaLista_s();

    char nodo[10];
    strcpy(nodo, "Barcelona");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    strcpy(nodo, "Atletico");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    strcpy(nodo, "Valencia");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    strcpy(nodo, "Madrid");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    strcpy(nodo, "City");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    strcpy(nodo, "United");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    strcpy(nodo, "Chelsea");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    strcpy(nodo, "Liverpool");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    strcpy(nodo, "Bayern");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    strcpy(nodo, "Leverkussen");
    agregar_s(lista, nodo);
    memset(nodo,'\0',strlen(nodo));

    if (graficar_s(lista) == 1) {
        printf("Se ha graficado la lista :D\n");
    }
    else {
        printf("No se pudo graficar la lista :(\n");
    }

    Nodo_s *busqueda = buscar_s(lista, "Barcelona");
    if (busqueda != NULL) {
        printf("Se encontró Barcelona :D\n");
        busqueda = NULL;
    }
    else {
        printf("No se encontró Barcelona :(\n");
    }

    if (eliminar_s(lista, "Madrid") == 1) {
        printf("Se eliminó Madrid >:)\n");
    }
    else {
        printf("No se pudo eliminar Madrid >:(\n");
    }

    if (graficar_s(lista) == 1) {
        printf("Se ha graficado la lista :D\n");
    }
    else {
        printf("No se pudo graficar la lista :(\n");
    }

    liberarLista_s(&lista);

    return 0;
}
