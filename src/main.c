#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generacion.h"
#include "ordenamiento.h"
#include "estadistica.h"

#define MAX_MUESTRAS 100000 // Límite definido por el documento

int main(int argc, char *argv[]) {
    double *datos = (double *)malloc(MAX_MUESTRAS * sizeof(double));
    if (datos == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return 1;
    }

    if (argc > 1) {
        // TODO: Lógica para parsear argumentos de terminal (argc/argv)
        printf("Modo línea de comandos activado.\n");
    } else {
        // TODO: Lógica para el menú interactivo con printf/scanf
        printf("Iniciando modo de consola interactiva...\n");
    }

    // Liberar memoria al final
    free(datos);
    return 0;
}