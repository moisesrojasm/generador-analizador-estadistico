/**
 * @file main.c
 * @brief Punto de entrada principal. Coordina la lectura por CLI e interfaz interactiva.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// ---> CORRECCIÓN: Se descomentaron las cabeceras para que el compilador las detecte <---
#include "generacion.h"
/* #include "ordenamiento.h" */ // Descomentar cuando agregues tus algoritmos
/* #include "estadistica.h" */  // Descomentar cuando conecten el archivo de JP

#define MaxMuestras 100000

// Variables Globales compartidas
double datos[MaxMuestras]; /* Máximo de muestras para el programa */
int N; /* Variable tipo n Global */

// Prototipo de funciones
int main(int argc, char *argv[]);
void manual();
void aleatorio();
void menuOrd();

int main(int argc, char *argv[])
{
    int op;
    double min, max, mu, sigma, b;

    /* Modo linea de comandos */
    if(argc > 1){
        printf("Modo linea de comandos activado.\n");

        if(argc != 6){
            printf("Uso:\n");
            printf("./programa distribucion N min max semilla\n");

            printf("\nEjemplo:\n");
            printf("./programa uniforme 1000 0 100 12345\n");

            return 1;
        }

        /* Puntero que guarda la direccion del primer argumento pasado al programa */
        char *dist = argv[1];

        /* atoi: pasa el argumento que inicialmente es un texto (por ejemplo, "100"),
        y usa la función atoi (ASCII to Integer) para convertirlo en un número entero,
        guardándolo en la variable N*/
        /* atof: (ASCII to Float), y lo convierte en un número decimal de punto flotante.
        Se guarda en la variable min*/
        N = atoi(argv[2]);
        min = atof(argv[3]);
        max = atof(argv[4]);

        if(N > MaxMuestras)
        {
            printf("Se excedio el limite de muestras.\n");
            return 1;
        }

        unsigned int semilla = (unsigned int)atoi(argv[5]);
        srand(semilla);

        if(strcmp(dist, "uniforme") == 0){
            generarUniforme(datos, N, min, max);
        }
        else if(strcmp(dist, "normal") == 0){
            mu = (min + max) / 2.0;
            sigma = (max - min) / 6.0;

            generarNormal(datos, N, mu, sigma, min, max);
        }
        else if(strcmp(dist, "laplace") == 0){
            mu = (min + max) / 2.0;

            b = (max - min) / (6.0 * sqrt(2.0));

            generarLaplace(datos, N, mu, b, min,max);
        }
        else{
            printf("Distribucion invalida.\n");
            return 1;
        }

        printf("\nPrimeros 10 datos:\n");

        for(int i = 0; i < 10 && i < N; i++){
            printf("%.4lf\n", datos[i]);
        }

        // Después de generar por CLI, enviamos directamente al menú de ordenamiento
        menuOrd();
        return 0;
    }

    /* Menu Interactivo por consola */
    printf(" BIENVENIDO AL GENERADOR Y ANALIZADOR ESTADISTICO\n");
    printf("-------------------------------------------------\n");

    do
    {
        printf("\nMENU\n");
        printf("Selecciona el tipo de dato:\n");
        printf("1. Ingresar datos manualmente\n");
        printf("2. Generar datos aleatoriamente\n");
        printf("3. Salir\n");
        printf("Opcion: ");

        if (scanf("%d", &op) != 1){
            printf("Numero invalido... Por favor, ingrese un numero entero.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            op = 0;
            continue;
        }

        switch(op){
            case 1:
                manual();
                break;

            case 2:
                aleatorio();
                break;

            case 3:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion invalida.\n");
                printf("Ingrese una opcion valida...\n");
        }

    } while(op != 3);

    return 0;
}

void menuOrd(){
// ---> CORRECCIÓN: Se eliminó 'datos_copia' de aquí para que no choque con el puntero <---
int op;
double tiempo_ordenamiento;
clock_t inicio, fin; // Declaración de variables para el cronometro

do{
    printf("\n1. Bubble Sort\n");
    printf("2. Odd-Even Sort\n");
    printf("3. Selection Sort\n");
    printf("4. Insertion Sort\n");
    printf("5. Bucket Sort\n");
    printf("6. Cocktail Sort\n");
    printf("7. Shell Sort\n");
    printf("8. Counting Sort\n");
    printf("9. Salir\n");
    printf("Ingresa una opcion: ");

    if (scanf("%d", &op) != 1) {
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            op = 0;
            continue;
        }

    // ---> CORRECCIÓN: Se arreglaron las llaves de este if para englobar toda la lógica de ordenamiento <---
    if (op >= 1 && op <= 8) {
        // Creamos una copia de los datos para no arruinar el arreglo original
        // si queremos probar diferentes algoritmos con el mismo conjunto de datos
        double *datos_copia = (double *)malloc(N * sizeof(double));

        if (datos_copia == NULL){
            printf("Error de memoria al crear la copia para ordenar.\n");
            continue;
        }

        memcpy(datos_copia, datos, N * sizeof(double)); //copiar un bloque de memoria

        printf("\nOrdenando %d datos...", N);

        // Inicia el cronometro de forma global antes de entrar al switch
        inicio = clock();

        /* Switch para seleccionar opción de tipo de algoritmo de ordenamiento */
        switch(op){
            case 1:
                printf("Algoritmo Bubble Sort seleccionado.\n");
                // bubbleSort(datos_copia, N); // Nota: Cuando agregues tus algoritmos, pásales 'datos_copia'
                break;

            case 2:
                printf("Algoritmo Odd Even Sort seleccionado.\n");
                // oddEvenSort(datos_copia, N);
                break;

            case 3:
                printf("Algoritmo Selection Sort seleccionado.\n");
                // selectionSort(datos_copia, N);
                break;

            case 4:
                printf("Algoritmo Insertion Sort seleccionado.\n");
                // insertionSort(datos_copia, N);
                break;

            case 5:
                printf("Algoritmo Bucket Sort seleccionado.\n");
                // bucketSort(datos_copia, N);
                break;

            case 6:
                printf("Algoritmo Cocktail Sort seleccionado.\n");
                // cocktailSort(datos_copia, N);
                break;

            case 7:
                printf("Algoritmo Shell Sort seleccionado.\n");
                // shellSort(datos_copia, N);
                break;

            case 8:
                printf("Algoritmo Counting Sort seleccionado.\n");
                // countingSort(datos_copia, N);
                break;
        }

        // Finaliza el cronometro
        fin = clock();
        tiempo_ordenamiento = ((double)(fin - inicio)) / CLOCKS_PER_SEC;

        printf("Ordenamiento finalizado...\n");
        printf("Tiempo de ejecucion del ordenamiento: %.6f segundos.\n", tiempo_ordenamiento);

        // Calcular las 15 medidas
        printf("Calculando medidas estadisticas sobre datos ordenados...\n");
        // AnalisisEstadistico(datos_copia, N); // Descomentar cuando integren JP

        free(datos_copia); // ---> CORRECCIÓN: Liberamos la memoria de la copia dentro del IF <---

    } else if (op == 9) {
        printf("Regresando al menu...\n");
    } else {
        printf("Ingrese una opción válida...\n");
    }

    } while(op != 9);
}

void aleatorio() {

    int distribucion, modo;
    double min, max, media, varianza, mu, sigma, b;
    unsigned int semilla;

    printf("\nGENERACION ALEATORIA\n");

    printf("Numero de datos: ");
    scanf("%d",&N);

    if(N > MaxMuestras){
    printf("Se excedio el limite.\n");
    return;}

    printf("Semilla: ");
    scanf("%u",&semilla);

    srand(semilla);

    printf("\n¿Qué tipo de distribución quieres?\n");
    printf("1. Uniforme\n");
    printf("2. Normal\n");
    printf("3. Laplace\n");

    scanf("%d",&distribucion);

    printf("\nModo de los datos: \n");
    printf("1. Rango\n");
    printf("2. Parametros\n");

    scanf("%d",&modo);

    if(modo == 1)
    {
        printf("Minimo: ");
        scanf("%lf",&min);

        printf("Maximo: ");
        scanf("%lf",&max);

        switch(distribucion)
        {
            case 1:
                generarUniforme(datos, N, min, max);
                break;

            case 2:{
                mu = (min + max) / 2.0;
                sigma = (max - min) / 6.0;
                generarNormal(datos, N, mu, sigma, min, max);
                break;
            }

            case 3:{
                mu = (min + max) / 2.0;
                b = (max - min) / (6.0 * sqrt(2.0));
                generarLaplace(datos, N, mu, b, min, max);
                break;
            }
        }
    }

    /* Si el usuario da los parámetros de los datos */
    else{
        printf("Media: ");
        scanf("%lf",&media);

        printf("Varianza: ");
        scanf("%lf",&varianza);

        switch(distribucion){
            case 1:{
                min =  media - sqrt(3.0 * varianza);
                max = media + sqrt(3.0 * varianza);

                generarUniforme(datos, N, min, max);
                break;
            }

            case 2:{
                sigma = sqrt(varianza);
                min = media - 3.0 * sigma;
                max = media + 3.0 * sigma;
                // ---> CORRECCIÓN: Se cambió 'mu' por 'media' y se pasaron los límites correctos 'min, max' <---
                generarNormal(datos, N, media, sigma, min, max);
                break;
            }

            case 3:{
                b = sqrt(varianza / 2.0);
                min = media - 3.0 * sqrt(2.0) * b;
                max = media + 3.0 * sqrt(2.0) * b;
                generarLaplace(datos, N, media, b, min, max); // Usar la "media" como mu
                break;
            }
        }
    }

    printf("\nPrimeros 10 datos generados:\n");

    for(int i=0;i<10 && i<N;i++)
    {
        printf("%.4lf\n",datos[i]);
    }

    // Pasamos automáticamente el control al flujo de ordenamiento exigido
    menuOrd();
}

void manual(){

    printf("\nGENERACION MANUAL\n");
    capturarManual(datos, &N);
    menuOrd();

}