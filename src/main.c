/**
 * @file main.c
 * @brief Punto de entrada principal. Coordina la lectura por CLI e interfaz interactiva.
 *
 * Flujo general:
 *   1. El usuario elige un caso (1-20) o ingresa datos manualmente.
 *   2. Se elige la distribucion y el algoritmo de ordenamiento.
 *   3. Se mide el tiempo de ordenamiento y el de calculo de medidas por separado.
 *   4. Se guarda una fila en resultados.txt con todos los datos del caso.
 *
 * @author  Equipo Practica 2
 * @date    Junio 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "generacion.h"
#include "ordenamiento.h"
#include "estadistica.h"

#define MAX_MUESTRAS 100000

/* Arreglo global compartido por todos los modulos */
double datos[MAX_MUESTRAS];
int N;

/* Tabla de los 20 casos segun el PDF de la practica */
typedef struct {
    int    caso;
    int    n;
    double max;
    double min;
} CasoSimulacion;

static CasoSimulacion casos[20] = {
    { 1,   100,    -1,    1},
    { 2,  1000,     5,   -5},
    { 3,  1000,    20,  -10},
    { 4,  1000,     0,  -50},
    { 5,  1000,     1,   -1},
    { 6,  2000,    30,   10},
    { 7,  2000,    30,  -30},
    { 8,  2000,   -10,  -50},
    { 9,  2000,   150, -100},
    {10,  2000,     1,   -1},
    {11,  4000,     1,   -1},
    {12,  5000,     1,   -1},
    {13,  6000,     1,   -1},
    {14,  7000,     1,   -1},
    {15,  8000,     1,   -1},
    {16,  9000,     1,   -1},
    {17, 10000,     1,   -1},
    {18, 20000,     1,   -1},
    {19, 30000,     1,   -1},
    {20, 50000,     1,   -1}
};

/* Prototipos */
void menuPrincipal();
void flujoManual();
void flujoSimulacion();
void menuOrdenamiento(int caso, const char *distribucion);
void guardarResultados(int caso, const char *distribucion, const char *algoritmo,
                       double *arreglo, int n,
                       double tiempo_ord, double tiempo_med);
void imprimirMedidas(double *arreglo, int n);

/* =========================================================
 * Main
 * ========================================================= */

int main(int argc, char *argv[]) {

    /* --- Modo linea de comandos --- */
    if (argc > 1) {

        /*
         * Modo rango  : ./practica2 dist N min max semilla
         * Modo params : ./practica2 dist N params p1 p2 semilla
         *   Normal  -> p1=mu  p2=sigma
         *   Laplace -> p1=mu  p2=b
         *   Uniforme-> p1=mu  p2=varianza (se convierte a min/max)
         */
        if (argc != 6 && argc != 7) {
            printf("Uso (modo rango)  : ./practica2 dist N min max semilla\n");
            printf("Uso (modo params) : ./practica2 dist N params p1 p2 semilla\n");
            printf("Distribuciones validas: uniforme, normal, laplace\n");
            printf("\nEjemplos:\n");
            printf("  ./practica2 uniforme 1000 -1 1 42\n");
            printf("  ./practica2 normal   2000 -5 5 42\n");
            printf("  ./practica2 normal   2000 params 0 1.0 42\n");
            printf("  ./practica2 laplace  1000 params 0 0.5 42\n");
            return 1;
        }

        char *dist = argv[1];
        N          = atoi(argv[2]);

        if (N <= 0 || N > MAX_MUESTRAS) {
            printf("Error: N debe estar entre 1 y %d.\n", MAX_MUESTRAS);
            return 1;
        }

        /* Detectar si es modo params o modo rango */
        int modo_params = (argc == 7 && strcmp(argv[3], "params") == 0);

        double min, max;
        unsigned int semilla;

        if (modo_params) {
            double p1    = atof(argv[4]);   /* mu */
            double p2    = atof(argv[5]);   /* sigma, b, o varianza */
            semilla      = (unsigned int)atoi(argv[6]);
            srand(semilla);
            printf("Semilla usada: %u\n", semilla);
            printf("Modo: parametros propios  |  p1=%.4f  p2=%.4f\n", p1, p2);

            if (strcmp(dist, "uniforme") == 0) {
                /* mu y varianza -> min/max */
                min = p1 - sqrt(3.0 * p2);
                max = p1 + sqrt(3.0 * p2);
                printf("Rango calculado: [%.4f, %.4f]\n", min, max);
                generarUniforme(datos, N, min, max);

            } else if (strcmp(dist, "normal") == 0) {
                /* p1=mu, p2=sigma */
                double sigma = p2;
                min = p1 - 3.0 * sigma;
                max = p1 + 3.0 * sigma;
                printf("Rango calculado: [%.4f, %.4f]\n", min, max);
                generarNormal(datos, N, p1, sigma, min, max);

            } else if (strcmp(dist, "laplace") == 0) {
                /* p1=mu, p2=b */
                double b = p2;
                min = p1 - 3.0 * sqrt(2.0) * b;
                max = p1 + 3.0 * sqrt(2.0) * b;
                printf("Rango calculado: [%.4f, %.4f]\n", min, max);
                generarLaplace(datos, N, p1, b, min, max);

            } else {
                printf("Distribucion invalida: %s\n", dist);
                return 1;
            }

        } else {
            /* Modo rango normal */
            min    = atof(argv[3]);
            max    = atof(argv[4]);
            semilla = (unsigned int)atoi(argv[5]);

            if (min >= max) {
                printf("Error: min debe ser menor que max.\n");
                return 1;
            }

            srand(semilla);
            printf("Semilla usada: %u\n", semilla);
            printf("Modo: rango  |  [%.4f, %.4f]\n", min, max);

            if (strcmp(dist, "uniforme") == 0) {
                generarUniforme(datos, N, min, max);
            } else if (strcmp(dist, "normal") == 0) {
                double mu    = (min + max) / 2.0;
                double sigma = (max - min) / 6.0;
                generarNormal(datos, N, mu, sigma, min, max);
            } else if (strcmp(dist, "laplace") == 0) {
                double mu = (min + max) / 2.0;
                double b  = (max - min) / (6.0 * sqrt(2.0));
                generarLaplace(datos, N, mu, b, min, max);
            } else {
                printf("Distribucion invalida: %s\n", dist);
                return 1;
            }
        }

        printf("Datos generados: %d\n", N);
        menuOrdenamiento(0, dist);
        return 0;
    }

    /* --- Modo interactivo --- */
    menuPrincipal();
    return 0;
}

/* =========================================================
 * Menu principal
 * ========================================================= */

void menuPrincipal() {
    int op;

    printf("=============================================\n");
    printf("  ANALIZADOR ESTADISTICO  -  Proyecto 2\n");
    printf("=============================================\n");

    do {
        printf("\nMENU PRINCIPAL\n");
        printf("1. Correr caso de simulacion\n");
        printf("2. Ingresar datos manualmente\n");
        printf("3. Salir\n");
        printf("Opcion: ");

        if (scanf("%d", &op) != 1) {
            printf("Entrada invalida, ingrese un numero.\n");
            while (getchar() != '\n');
            op = 0;
            continue;
        }

        switch (op) {
            case 1: flujoSimulacion(); break;
            case 2: flujoManual();     break;
            case 3: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }

    } while (op != 3);
}

/* =========================================================
 * Flujo: casos de simulacion de la tabla del PDF
 * ========================================================= */

void flujoSimulacion() {

    int opCaso, opDist, opModo;
    unsigned int semilla;

    printf("\n--- CASOS DE SIMULACION ---\n");
    printf("%-5s %-8s %-8s %-8s\n", "Caso", "n", "Max", "Min");
    printf("----------------------------------\n");
    for (int i = 0; i < 20; i++) {
        /* Mostrar siempre el mayor como Max y el menor como Min */
        double dmin = casos[i].min < casos[i].max ? casos[i].min : casos[i].max;
        double dmax = casos[i].min < casos[i].max ? casos[i].max : casos[i].min;
        printf("%-5d %-8d %-8.0f %-8.0f\n", casos[i].caso, casos[i].n, dmax, dmin);
    }

    printf("\nElige el caso (1-20): ");
    if (scanf("%d", &opCaso) != 1 || opCaso < 1 || opCaso > 20) {
        printf("Caso invalido.\n");
        while (getchar() != '\n');
        return;
    }

    printf("\nDistribucion:\n");
    printf("1. Uniforme\n");
    printf("2. Normal\n");
    printf("3. Laplace\n");
    printf("Opcion: ");
    if (scanf("%d", &opDist) != 1 || opDist < 1 || opDist > 3) {
        printf("Distribucion invalida.\n");
        while (getchar() != '\n');
        return;
    }

    printf("\nModo de parametros:\n");
    printf("1. Modo rango (usa min/max del caso)\n");
    printf("2. Modo parametros propios (ingresa mu y sigma/b)\n");
    printf("Opcion: ");
    if (scanf("%d", &opModo) != 1 || opModo < 1 || opModo > 2) {
        printf("Modo invalido.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Semilla (entero): ");
    scanf("%u", &semilla);
    srand(semilla);
    printf("Semilla usada: %u\n", semilla);

    /* Tomar los parametros del caso elegido y corregir si vienen al reves */
    CasoSimulacion c = casos[opCaso - 1];
    N = c.n;

    if (c.min > c.max) {
        double tmp = c.min;
        c.min = c.max;
        c.max = tmp;
    }

    const char *nombreDist = "";

    if (opModo == 1) {
        /* --- Modo rango: usa min/max del caso --- */
        switch (opDist) {
            case 1:
                nombreDist = "Uniforme";
                generarUniforme(datos, N, c.min, c.max);
                break;
            case 2: {
                nombreDist   = "Normal";
                double mu    = (c.min + c.max) / 2.0;
                double sigma = (c.max - c.min) / 6.0;
                generarNormal(datos, N, mu, sigma, c.min, c.max);
                break;
            }
            case 3: {
                nombreDist = "Laplace";
                double mu  = (c.min + c.max) / 2.0;
                double b   = (c.max - c.min) / (6.0 * sqrt(2.0));
                generarLaplace(datos, N, mu, b, c.min, c.max);
                break;
            }
        }
        printf("Modo rango: [%.2f, %.2f]\n", c.min, c.max);

    } else {
        /* --- Modo parametros propios --- */
        double p1, p2;
        double rmin, rmax;

        switch (opDist) {
            case 1:
                nombreDist = "Uniforme";
                printf("Media (mu): ");       scanf("%lf", &p1);
                printf("Varianza:   ");       scanf("%lf", &p2);
                rmin = p1 - sqrt(3.0 * p2);
                rmax = p1 + sqrt(3.0 * p2);
                printf("Rango calculado: [%.4f, %.4f]\n", rmin, rmax);
                generarUniforme(datos, N, rmin, rmax);
                break;
            case 2:
                nombreDist = "Normal";
                printf("Media (mu):          "); scanf("%lf", &p1);
                printf("Desv. estandar (sigma): "); scanf("%lf", &p2);
                rmin = p1 - 3.0 * p2;
                rmax = p1 + 3.0 * p2;
                printf("Rango calculado: [%.4f, %.4f]\n", rmin, rmax);
                generarNormal(datos, N, p1, p2, rmin, rmax);
                break;
            case 3:
                nombreDist = "Laplace";
                printf("Ubicacion (mu):  "); scanf("%lf", &p1);
                printf("Escala (b):      "); scanf("%lf", &p2);
                rmin = p1 - 3.0 * sqrt(2.0) * p2;
                rmax = p1 + 3.0 * sqrt(2.0) * p2;
                printf("Rango calculado: [%.4f, %.4f]\n", rmin, rmax);
                generarLaplace(datos, N, p1, p2, rmin, rmax);
                break;
        }
    }

    printf("Caso %d generado: n=%d\n", opCaso, N);
    menuOrdenamiento(opCaso, nombreDist);
}

/* =========================================================
 * Flujo: ingreso manual
 * ========================================================= */

void flujoManual() {
    printf("\n--- INGRESO MANUAL ---\n");
    capturarManual(datos, &N);
    menuOrdenamiento(0, "Manual");
}

/* =========================================================
 * Menu de ordenamiento + medicion de tiempos + guardado
 * ========================================================= */

void menuOrdenamiento(int caso, const char *distribucion) {

    int op;
    clock_t inicio, fin;
    double tiempo_ord, tiempo_med;

    const char *nombresAlg[] = {
        "", "BubbleSort", "OddEvenSort", "SelectionSort", "InsertionSort",
        "BucketSort", "CocktailSort", "ShellSort", "CountingSort"
    };

    do {
        printf("\n--- ORDENAMIENTO ---\n");
        printf("1. Bubble Sort\n");
        printf("2. Odd-Even Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Insertion Sort\n");
        printf("5. Bucket Sort\n");
        printf("6. Cocktail Sort\n");
        printf("7. Shell Sort\n");
        printf("8. Counting Sort\n");
        printf("9. Volver al menu principal\n");
        printf("Opcion: ");

        if (scanf("%d", &op) != 1) {
            printf("Entrada invalida.\n");
            while (getchar() != '\n');
            op = 0;
            continue;
        }

        if (op == 9) {
            printf("Volviendo al menu...\n");
            break;
        }

        if (op < 1 || op > 8) {
            printf("Opcion invalida.\n");
            continue;
        }

        /* Copia para no modificar el arreglo original */
        double *copia = (double *)malloc(N * sizeof(double));
        if (copia == NULL) {
            printf("Error: no se pudo reservar memoria.\n");
            continue;
        }
        memcpy(copia, datos, N * sizeof(double));

        printf("\nOrdenando %d datos...\n", N);

        /* Medir solo el ordenamiento */
        inicio = clock();
        switch (op) {
            case 1: bubbleSort(copia, N);    break;
            case 2: oddEvenSort(copia, N);   break;
            case 3: selectionSort(copia, N); break;
            case 4: insertionSort(copia, N); break;
            case 5: bucketSort(copia, N);    break;
            case 6: cocktailSort(copia, N);  break;
            case 7: shellSort(copia, N);     break;
            case 8: countingSort(copia, N);  break;
        }
        fin = clock();
        tiempo_ord = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo de ordenamiento: %.6f segundos\n", tiempo_ord);

        /* Medir solo el calculo de medidas */
        printf("\nCalculando medidas estadisticas...\n");
        inicio = clock();
        imprimirMedidas(copia, N);
        fin = clock();
        tiempo_med = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo de calculo de medidas: %.6f segundos\n", tiempo_med);

        /* Guardar fila en resultados.txt */
        guardarResultados(caso, distribucion, nombresAlg[op],
                          copia, N, tiempo_ord, tiempo_med);

        free(copia);

    } while (op != 9);
}

/* =========================================================
 * Guarda una fila de resultados en resultados.txt
 * ========================================================= */

void guardarResultados(int caso, const char *distribucion, const char *algoritmo,
                       double *arreglo, int n,
                       double tiempo_ord, double tiempo_med) {

    FILE *f = fopen("resultados.csv", "a");
    if (f == NULL) {
        printf("Error: no se pudo abrir resultados.csv\n");
        return;
    }

    /* Escribir encabezado si el archivo esta vacio */
    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    if (tam == 0) {
        fprintf(f, "Caso,Distribucion,Algoritmo,n,"
                   "Maximo,Minimo,Media,MediaGeom,Mediana,Moda,"
                   "Varianza,DesvEst,CoefVar,"
                   "Q1,Q2,Q3,Q4,"
                   "D1,D2,D3,D4,D5,D6,D7,D8,D9,D10,"
                   "P10,P20,P25,P30,P40,P50,P60,P70,P75,P80,P90,P100,"
                   "Alpha0,Alpha1,Alpha2,Alpha3,Alpha4,"
                   "Mu0,Mu1,Mu2,Mu3,Mu4,"
                   "MomEst2,MomEst3,MomEst4,"
                   "Curtosis,"
                   "T_Ord_s,T_Med_s\n");
    }

    /* Datos basicos */
    fprintf(f, "%d,%s,%s,%d,", caso, distribucion, algoritmo, n);

    /* Medidas principales */
    fprintf(f, "%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,",
            calcularMaximo(arreglo, n),
            calcularMinimo(arreglo, n),
            calcularMedia(arreglo, n),
            calcularMediaGeometrica(arreglo, n),
            calcularMediana(arreglo, n),
            calcularModa(arreglo, n));

    fprintf(f, "%.6f,%.6f,%.6f,",
            calcularVarianza(arreglo, n),
            calcularDesviacionEstandar(arreglo, n),
            calcularCoeficienteVariacion(arreglo, n));

    /* Cuartiles */
    fprintf(f, "%.6f,%.6f,%.6f,%.6f,",
            calcularPrimerCuartil(arreglo, n),
            calcularSegundoCuartil(arreglo, n),
            calcularTercerCuartil(arreglo, n),
            calcularCuartoCuartil(arreglo, n));

    /* Deciles D1-D10 */
    for (int k = 1; k <= 10; k++)
        fprintf(f, "%.6f,", calcularDecil(arreglo, n, k));

    /* Percentiles P10,P20,P25,P30,P40,P50,P60,P70,P75,P80,P90,P100 */
    int ps[] = {10, 20, 25, 30, 40, 50, 60, 70, 75, 80, 90, 100};
    for (int i = 0; i < 12; i++)
        fprintf(f, "%.6f,", calcularPercentil(arreglo, n, ps[i]));

    /* Momentos no centrados */
    fprintf(f, "%.6f,%.6f,%.6f,%.6f,%.6f,",
            calcularMomento0(arreglo, n),
            calcularMomento1(arreglo, n),
            calcularMomento2(arreglo, n),
            calcularMomento3(arreglo, n),
            calcularMomento4(arreglo, n));

    /* Momentos centrados */
    fprintf(f, "%.6f,%.6f,%.6f,%.6f,%.6f,",
            calcularMomentoCentrado0(arreglo, n),
            calcularMomentoCentrado1(arreglo, n),
            calcularMomentoCentrado2(arreglo, n),
            calcularMomentoCentrado3(arreglo, n),
            calcularMomentoCentrado4(arreglo, n));

    /* Momentos estandar y curtosis */
    fprintf(f, "%.6f,%.6f,%.6f,",
            calcularMomentoEstandar2(arreglo, n),
            calcularMomentoEstandar3(arreglo, n),
            calcularMomentoEstandar4(arreglo, n));

    fprintf(f, "%.6f,", calcularCurtosis(arreglo, n));

    /* Tiempos */
    fprintf(f, "%.6f,%.6f\n", tiempo_ord, tiempo_med);

    fclose(f);
    printf("Fila guardada en resultados.csv\n");
}

/* =========================================================
 * Imprime las medidas en consola
 * ========================================================= */

void imprimirMedidas(double *arreglo, int n) {

    printf("\n============================================================\n");
    printf("  RESULTADOS ESTADISTICOS  (n = %d)\n", n);
    printf("============================================================\n");

    printf("\n--- Posicion central ---\n");
    printf("  Maximo              : %12.6f\n", calcularMaximo(arreglo, n));
    printf("  Minimo              : %12.6f\n", calcularMinimo(arreglo, n));
    printf("  Media aritmetica    : %12.6f\n", calcularMedia(arreglo, n));
    printf("  Media geometrica    : %12.6f\n", calcularMediaGeometrica(arreglo, n));
    printf("  Mediana             : %12.6f\n", calcularMediana(arreglo, n));
    printf("  Moda                : %12.6f\n", calcularModa(arreglo, n));

    printf("\n--- Dispersion ---\n");
    printf("  Varianza            : %12.6f\n", calcularVarianza(arreglo, n));
    printf("  Desv. estandar      : %12.6f\n", calcularDesviacionEstandar(arreglo, n));
    printf("  Coef. variacion     : %12.6f\n", calcularCoeficienteVariacion(arreglo, n));

    printf("\n--- Cuartiles ---\n");
    printf("  Q1                  : %12.6f\n", calcularPrimerCuartil(arreglo, n));
    printf("  Q2                  : %12.6f\n", calcularSegundoCuartil(arreglo, n));
    printf("  Q3                  : %12.6f\n", calcularTercerCuartil(arreglo, n));
    printf("  Q4                  : %12.6f\n", calcularCuartoCuartil(arreglo, n));

    printf("\n--- Deciles ---\n");
    for (int k = 1; k <= 10; k++) {
        printf("  D%-2d                 : %12.6f\n", k, calcularDecil(arreglo, n, k));
    }

    printf("\n--- Percentiles (P10, P25, P50, P75, P90) ---\n");
    int ps[] = {10, 25, 50, 75, 90};
    for (int i = 0; i < 5; i++) {
        printf("  P%-2d                 : %12.6f\n", ps[i], calcularPercentil(arreglo, n, ps[i]));
    }

    printf("\n--- Momentos no centrados ---\n");
    printf("  Alpha 0             : %12.6f\n", calcularMomento0(arreglo, n));
    printf("  Alpha 1             : %12.6f\n", calcularMomento1(arreglo, n));
    printf("  Alpha 2             : %12.6f\n", calcularMomento2(arreglo, n));
    printf("  Alpha 3             : %12.6f\n", calcularMomento3(arreglo, n));
    printf("  Alpha 4             : %12.6f\n", calcularMomento4(arreglo, n));

    printf("\n--- Momentos centrados ---\n");
    printf("  Mu 0                : %12.6f\n", calcularMomentoCentrado0(arreglo, n));
    printf("  Mu 1                : %12.6f\n", calcularMomentoCentrado1(arreglo, n));
    printf("  Mu 2                : %12.6f\n", calcularMomentoCentrado2(arreglo, n));
    printf("  Mu 3                : %12.6f\n", calcularMomentoCentrado3(arreglo, n));
    printf("  Mu 4                : %12.6f\n", calcularMomentoCentrado4(arreglo, n));

    printf("\n--- Momentos estandar ---\n");
    printf("  Momento estandar 2  : %12.6f\n", calcularMomentoEstandar2(arreglo, n));
    printf("  Momento estandar 3  : %12.6f\n", calcularMomentoEstandar3(arreglo, n));
    printf("  Momento estandar 4  : %12.6f\n", calcularMomentoEstandar4(arreglo, n));

    printf("\n--- Curtosis ---\n");
    printf("  Curtosis            : %12.6f\n", calcularCurtosis(arreglo, n));

    printf("\n============================================================\n");
}
