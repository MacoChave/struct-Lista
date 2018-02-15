#include <stdio.h>
#include <sys/stat.h>
#include "Simple/lista_s.h"
#include "Simple/nodo_s.h"
#include "Doble/lista_d.h"
#include "Doble/nodo_d.h"
#include "Circular/lista_c.h"
#include "Circular/nodo_c.h"
#include "Parser/json.h"

json_value *cargarJSON(char *filename) {
    FILE *file;
    struct stat filestatus;
    int file_size;
    char *file_contents;
    json_char *json;
    json_value *value;

    if (stat(filename, &filestatus) != 0) {
        fprintf(stderr, "Archivo %s no funciona\n", filename);
        return;
    }
    file_size = filestatus.st_size;
    file_contents = (char *)malloc(filestatus.st_size);
    if (file_contents == NULL) {
        fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
        return;
    }
    file = fopen(filename, "rt");
    if (file == NULL) {
        fprintf(stderr, "Unable to open %s\n", filename);
        fclose(file);
        return;
    }
    if (fread(file_contents, file_size, 1, file) != 1) {
        fprintf(stderr, "Unable to read content of %s\n", filename);
        fclose(file);
        free(file_contents);
        return;
    }
    fclose(file);
    file = NULL;

    printf("%s\n", file_contents);
    printf("--------------------------------\n\n");

    json = (json_char*)file_contents;
    value = json_parse(json, file_size);

    if (value == NULL) {
        fprintf(stderr, "Unable to parse data\n");
        free(file_contents);
    }

    free(file_contents);
    file_contents = NULL;

    return value;
}

static void print_depth_shift(int depth)
{
        int j;
        for (j=0; j < depth; j++) {
                printf(" ");
        }
}

static void process_value(json_value* value, int depth);

static void process_object(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.object.length;
        for (x = 0; x < length; x++) {
                print_depth_shift(depth);
                printf("object[%d].name = %s\n", x, value->u.object.values[x].name);
                process_value(value->u.object.values[x].value, depth+1);
        }
}

static void process_array(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.array.length;
        printf("array\n");
        for (x = 0; x < length; x++) {
                process_value(value->u.array.values[x], depth);
        }
}

static void process_value(json_value* value, int depth)
{
        int j;
        if (value == NULL) {
                return;
        }
        if (value->type != json_object) {
                print_depth_shift(depth);
        }
        switch (value->type) {
                case json_none:
                        printf("none\n");
                        break;
                case json_object:
                        process_object(value, depth+1);
                        break;
                case json_array:
                        process_array(value, depth+1);
                        break;
                case json_integer:
                        printf("int: %10" PRId64 "\n", value->u.integer);
                        break;
                case json_double:
                        printf("double: %f\n", value->u.dbl);
                        break;
                case json_string:
                        printf("string: %s\n", value->u.string.ptr);
                        break;
                case json_boolean:
                        printf("bool: %d\n", value->u.boolean);
                        break;
        }
}

void listaSimple(Lista_s **lista) {
    int opcion = 0;
    int cantidad = 0;
    char dato[15];

    do {
        printf("Seleccione un operación:\n");
        printf("[0] Salir\n"
               "[1] Agregar\n"
               "[2] Buscar\n"
               "[3] Eliminar\n");
        scanf("%d", &opcion);

        switch (opcion) {
        case 0: // SALIR
            break;
        case 1: // AGREGAR
            printf("Cantidad de ingresos: ");
            scanf("%d", &cantidad);

            for (int i = 0; i <= cantidad; i++) {
                printf("Ingresar el dato (String):\n");
                scanf("%s", dato);
                agregar_s(*lista, dato);
            }

            break;
        case 2: // BUSCAR
            printf("Ingresar el dato (String):\n");
            scanf("%s", dato);
            Nodo_s *n = buscar_s(*lista, dato);
            if (n != NULL) {
                printf("Se encontró %s :D\n", n->valor);
            }
            else {
                printf("No se pudo encontrar %s :/\n", dato);
            }
            n = NULL;
            break;
        case 3: // ELIMINAR
            printf("Ingresar el dato (String):\n");
            scanf("%s", dato);
            if (eliminar_s(*lista, dato) == 1) {
                printf("Se eliminó %s :D\n", dato);
            }
            else {
                printf("No se pudo eliminar %s :/\n", dato);
            }
            break;
        default:
            printf("Opción no esperada :/\n");
            break;
        }

        if (graficar_s(*lista) == 1) {
            printf("Se grafico la lista :D\n");
        }
        else {
            printf("No se pudo graficar la lista :(\n");
        }
    } while (opcion != 0);
}

void listaDoble(Lista_d **lista) {
    int opcion = 0;
    int cantidad = 0;
    char dato[20];

    do {
        printf("Seleccione un operación:\n");
        printf("[0] Salir\n"
               "[1] Agregar\n"
               "[2] Buscar\n"
               "[3] Eliminar\n");
        scanf("%d", &opcion);

        switch (opcion) {
        case 0: // SALIR
            break;
        case 1: // AGREGAR
            printf("Cantidad de ingresos: ");
            scanf("%d", &cantidad);

            for (int i = 0; i <= cantidad; i++) {
                printf("Ingresar el dato (String):\n");
                scanf("%s", dato);
                agregar_d(*lista, dato);
            }

            break;
        case 2: // BUSCAR
            printf("Ingresar el dato (String):\n");
            scanf("%s", dato);
            Nodo_d *n = buscar_d(*lista, dato);
            if (n != NULL) {
                printf("Se encontró %s :D\n", n->valor);
            }
            else {
                printf("No se pudo encontrar %s :/\n", dato);
            }
            n = NULL;
            break;
        case 3: // ELIMINAR
            printf("Ingresar el dato (String):\n");
            scanf("%s", dato);
            if (eliminar_d(*lista, dato) == 1) {
                printf("Se eliminó %s :D\n", dato);
            }
            else {
                printf("No se pudo eliminar %s :/\n", dato);
            }
            break;
        default:
            printf("Opción no esperada :/\n");
            break;
        }

        if (graficar_d(*lista) == 1) {
            printf("Se grafico la lista :D\n");
        }
        else {
            printf("No se pudo graficar la lista :(\n");
        }
    } while (opcion != 0);
}

void listaCircular(Lista_c **lista) {
    int opcion = 0;
    int cantidad = 0;
    char dato[15];

    do {
        printf("Seleccione un operación:\n");
        printf("[0] Salir\n"
               "[1] Agregar\n"
               "[2] Buscar\n"
               "[3] Eliminar\n");
        scanf("%d", &opcion);

        switch (opcion) {
        case 0: // SALIR
            break;
        case 1: // AGREGAR
            printf("Cantidad de ingresos:\n");
            scanf("%d", &cantidad);

            for (int i = 0; i <= cantidad; i++) {
                printf("Ingresar el dato (String):\n");
                scanf("%s", dato);
                agregar_c(*lista, dato);
            }

            break;
        case 2: // BUSCAR
            printf("Ingresar el dato (String):");
            scanf("%s", dato);
            Nodo_c *n = buscar_c(*lista, dato);
            if (n != NULL) {
                printf("Se encontró %s :D\n", n->valor);
            }
            else {
                printf("No se pudo encontrar %s :/\n", dato);
            }
            n = NULL;
            break;
        case 3: // ELIMINAR
            printf("Ingresar el dato (String):");
            scanf("%s", dato);
            if (eliminar_c(*lista, dato) == 1) {
                printf("Se eliminó %s :D\n", dato);
            }
            else {
                printf("No se pudo eliminar %s :/\n", dato);
            }
            break;
        default:
            printf("Opción no esperada :/\n");
            break;
        }

        if (graficar_c(*lista) == 1) {
            printf("Se grafico la lista :D\n");
        }
        else {
            printf("No se pudo graficar la lista :(\n");
        }
    } while (opcion != 0);
}

int main(int argc, char *argv[])
{
    Lista_s *ls = nuevaLista_s();
    Lista_d *ld = nuevaLista_d();
    Lista_c *lc = nuevaLista_c();
    json_value *value = NULL;
    int opcion = 0;

    do {
        printf("Elegir opcion\n");
        printf("[0] Salir\n"
               "[1] Lista Simple\n"
               "[2] Lista Doble\n"
               "[3] Lista circular\n"
               "[4] Cargar JSON\n");
        scanf("%d", &opcion);

        switch (opcion) {
        case 0: // SALIR
            printf("Liberando memoria ;)\n");
            ls = liberarLista_s(ls);
            ld = liberarLista_d(ld);
            lc = liberarLista_c(lc);
            printf("Adios :)\n");
            break;
        case 1: // LISTA SIMPLE
            listaSimple(&ls);
            break;
        case 2: // LISTA DOBLE
            listaDoble(&ld);
            break;
        case 3: // LISTA CIRCULAR
            listaCircular(&lc);
            break;
        case 4: // CARGAR JSON
            value = cargarJSON("/home/marco/Descargas/MOCK_DATA (3).json");
            process_value(value, 0);
            json_value_free(value);
            value = NULL;
            break;
        default:
            printf("Opción no esperada :/");
            break;
        }
    } while (opcion != 0);

    return 0;
}
