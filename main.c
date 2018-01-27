#include <stdio.h>
#include "Simple/lista_s.h"
#include "Simple/nodo_s.h"
#define nodo "Nodo"

int main(int argc, char *argv[])
{
    Lista_s *lista = nuevaLista_s();

    for (int i = 0; i < 500; i++) {
        char buffer[8];
        sprintf(buffer, "%s%d", nodo, i);

        agregar_s(lista, buffer);
    }

    if (graficar_s(lista) == 1) {
        printf("Se ha graficado la lista :D\n");
    }
    else {
        printf("No se pudo graficar la lista :(");
    }

    liberarLista_s(&lista);

    return 0;
}
