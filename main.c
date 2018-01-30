#include <stdio.h>
#include "Simple/lista_s.h"
#include "Simple/nodo_s.h"
#include "Doble/lista_d.h"
#include "Doble/nodo_d.h"

void listaSimple(Lista_s **lista) {
    int cantidad = 0;
    char dato[10];

    printf("Cantidad de ingresos: ");
    scanf("%d", &cantidad);

    for (int i = 0; i <= cantidad; i++) {
        printf("Ingresar el dato(String): ");
        scanf("%s", dato);
        agregar_s(*lista, dato);
        memset(dato, '\0', strlen(dato));
    }

    if (graficar_s(*lista) == 1) {
        printf("Se grafico la lista :D\n");
    }
    else {
        printf("No se pudo graficar la lista :(\n");
    }
}

void listaDoble(Lista_d **lista) {
    int cantidad = 0;
    char dato[10];

    printf("Cantidad de ingresos: ");
    scanf("%d", &cantidad);

    for (int i = 0; i <= cantidad; i++) {
        printf("Ingresar el dato(String): ");
        scanf("%s", dato);
        agregar_d(*lista, dato);
        memset(dato, '\0', strlen(dato));
    }

    if (graficar_d(*lista) == 1) {
        printf("Se grafico la lista :D\n");
    }
    else {
        printf("No se pudo graficar la lista :(\n");
    }
}

int main(int argc, char *argv[])
{
    Lista_s *ls = nuevaLista_s();
    Lista_d *ld = nuevaLista_d();
    int opcion = 0;

    do {
        printf("Elegir opcion\n");
        printf("[0] Salir\n"
               "[1] Lista Simple\n"
               "[2] Lista Doble\n");
        scanf("%d", &opcion);

        switch (opcion) {
        case 0:
            ls = liberarLista_s(&ls);
            ld = liberarLista_d(&ld);
            break;
        case 1:
            listaSimple(&ls);
            break;
        case 2:
            listaDoble(&ld);
            break;
        default:
            printf("Opción no esperada");
            break;
        }
    } while (opcion != 0);

    return 0;
}
