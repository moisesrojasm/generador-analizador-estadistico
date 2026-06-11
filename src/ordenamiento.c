/**
 * @file ordenamiento.c
 * @brief Implementación de 8 algoritmos de ordenamiento adaptados para arreglos double.
 */

#include "ordenamiento.h"
#include <stdlib.h>
#include <stdio.h>

/* =========================================================
 * 1. Bubble Sort
 * ========================================================= */
void bubbleSort(double *arreglo, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arreglo[j] > arreglo[j + 1]) {
                double temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
            }
        }
    }
}

/* =========================================================
 * 2. Odd-Even Sort (Pares y Nones)
 * ========================================================= */
void oddEvenSort(double *arreglo, int n) {
    int ordenado = 0;
    while (!ordenado) {
        ordenado = 1;
        /* Fase impar */
        for (int i = 1; i <= n - 2; i += 2) {
            if (arreglo[i] > arreglo[i + 1]) {
                double temp = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = temp;
                ordenado = 0;
            }
        }
        /* Fase par */
        for (int i = 0; i <= n - 2; i += 2) {
            if (arreglo[i] > arreglo[i + 1]) {
                double temp = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = temp;
                ordenado = 0;
            }
        }
    }
}

/* =========================================================
 * 3. Selection Sort
 * ========================================================= */
void selectionSort(double *arreglo, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arreglo[j] < arreglo[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            double temp = arreglo[min_idx];
            arreglo[min_idx] = arreglo[i];
            arreglo[i] = temp;
        }
    }
}

/* =========================================================
 * 4. Insertion Sort
 * ========================================================= */
void insertionSort(double *arreglo, int n) {
    for (int i = 1; i < n; i++) {
        double key = arreglo[i];
        int j = i - 1;
        while (j >= 0 && arreglo[j] > key) {
            arreglo[j + 1] = arreglo[j];
            j = j - 1;
        }
        arreglo[j + 1] = key;
    }
}

/* =========================================================
 * 5. Cocktail Sort
 * ========================================================= */
void cocktailSort(double *arreglo, int n) {
    int intercambiado = 1;
    int inicio = 0;
    int fin = n - 1;

    while (intercambiado) {
        intercambiado = 0;
        for (int i = inicio; i < fin; ++i) {
            if (arreglo[i] > arreglo[i + 1]) {
                double temp = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = temp;
                intercambiado = 1;
            }
        }
        if (!intercambiado) break;
        intercambiado = 0;
        --fin;
        for (int i = fin - 1; i >= inicio; --i) {
            if (arreglo[i] > arreglo[i + 1]) {
                double temp = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = temp;
                intercambiado = 1;
            }
        }
        ++inicio;
    }
}

/* =========================================================
 * 6. Shell Sort
 * ========================================================= */
void shellSort(double *arreglo, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            double temp = arreglo[i];
            int j;
            for (j = i; j >= gap && arreglo[j - gap] > temp; j -= gap) {
                arreglo[j] = arreglo[j - gap];
            }
            arreglo[j] = temp;
        }
    }
}

/* =========================================================
 * 7. Bucket Sort (Adaptado para doubles continuos y negativos)
 * ========================================================= */
/* Estructura para la lista ligada de cada cubeta */
typedef struct NodoBucket {
    double valor;
    struct NodoBucket *siguiente;
} NodoBucket;

void bucketSort(double *arreglo, int n) {
    if (n <= 1) return;

    double min = arreglo[0], max = arreglo[0];
    for (int i = 1; i < n; i++) {
        if (arreglo[i] < min) min = arreglo[i];
        if (arreglo[i] > max) max = arreglo[i];
    }

    if (max == min) return; /* Todos los elementos son iguales */

    int num_cubetas = n;
    NodoBucket **cubetas = (NodoBucket **)calloc(num_cubetas, sizeof(NodoBucket *));

    /* Distribuir los datos en las cubetas */
    for (int i = 0; i < n; i++) {
        /* Formula para mapear un double a un indice entero de cubeta */
        int indice = (int)(((arreglo[i] - min) / (max - min)) * (num_cubetas - 1));

        NodoBucket *nuevo = (NodoBucket *)malloc(sizeof(NodoBucket));
        nuevo->valor = arreglo[i];
        nuevo->siguiente = NULL;

        /* Insertar ordenado dentro de la cubeta (Insertion Sort en lista) */
        if (cubetas[indice] == NULL || cubetas[indice]->valor >= arreglo[i]) {
            nuevo->siguiente = cubetas[indice];
            cubetas[indice] = nuevo;
        } else {
            NodoBucket *actual = cubetas[indice];
            while (actual->siguiente != NULL && actual->siguiente->valor < arreglo[i]) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }

    /* Reconstruir el arreglo original */
    int idx = 0;
    for (int i = 0; i < num_cubetas; i++) {
        NodoBucket *actual = cubetas[i];
        while (actual != NULL) {
            arreglo[idx++] = actual->valor;
            NodoBucket *temp = actual;
            actual = actual->siguiente;
            free(temp); /* Liberar memoria de la cubeta */
        }
    }
    free(cubetas);
}

/* =========================================================
 * 8. Counting Sort (Adaptado con factor de escala)
 * ========================================================= */
void countingSort(double *arreglo, int n) {
    if (n <= 1) return;

    /* Factor para convertir doubles a enteros (mantiene 3 decimales) */
    double factor = 1000.0;
    int *enteros = (int *)malloc(n * sizeof(int));

    int min_val = (int)(arreglo[0] * factor);
    int max_val = min_val;

    for (int i = 0; i < n; i++) {
        enteros[i] = (int)(arreglo[i] * factor);
        if (enteros[i] < min_val) min_val = enteros[i];
        if (enteros[i] > max_val) max_val = enteros[i];
    }

    int rango = max_val - min_val + 1;

    /* Proteccion de memoria RAM: si la dispersion es gigante, usar fallback */
    if (rango > 50000000) {
        free(enteros);
        shellSort(arreglo, n); /* Salvavidas */
        return;
    }

    int *conteo = (int *)calloc(rango, sizeof(int));
    if (conteo == NULL) {
        free(enteros);
        shellSort(arreglo, n);
        return;
    }

    /* Contar frecuencias */
    for (int i = 0; i < n; i++) {
        conteo[enteros[i] - min_val]++;
    }

    /* Reconstruir (aqui es donde ocurre la perdida de precision matematica) */
    int idx = 0;
    for (int i = 0; i < rango; i++) {
        while (conteo[i] > 0) {
            arreglo[idx++] = (double)(i + min_val) / factor;
            conteo[i]--;
        }
    }

    free(conteo);
    free(enteros);
}