/**
 * @file generacion.c
 * @brief Implementación del motor matemático de generación pseudoaleatoria y captura.
 */

// ---> CORRECCIÓN: Se descomentó la cabecera para enlazar correctamente los prototipos <---
#include "generacion.h"

#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void aplicarRestriccion(double *datos, int n, double min, double max);
void capturarManual(double *datos, int *n);
void generarUniforme(double *datos, int n, double min, double max);
void generarNormal(double *datos, int n, double mu, double sigma, double min, double max);
void generarLaplace(double *datos, int n, double mu, double b, double min, double max);

/**
 * @brief Conversión base: transforma rand() en una uniforme continua (0, 1)
 * Evita valores exactamente 0 o 1 para proteger operaciones como log().
 */

static double uniforme01(){
    return (rand() + 1.0)/(RAND_MAX + 2.0);
}

void capturarManual(double *datos, int *n){
    printf("Numero de datos: ");
    scanf("%d", n);

   if(*n <= 0 || *n > 100000){
        printf("Cantidad invalida.\n");
        return;
    }

    for(int i = 0; i < *n; i++){
        printf("Dato[%d]: ", i);
        scanf("%lf", &datos[i]);
    }

    printf("\nDatos capturados correctamente.\n");
}


void generarUniforme(double *datos, int n, double min, double max){
    for(int i = 0; i < n; i++)
    {
        double u;
        u = uniforme01();

        datos[i] = min + (max - min) * u;
    }

}

void generarNormal(double *datos, int n, double mu, double sigma, double min, double max){
    double u1, u2, z;
    for(int i = 0; i < n; i++)
    {
        u1 = uniforme01();
        u2 = uniforme01();
        z = sqrt(-2.0 * log(u1))*cos(2.0 * M_PI * u2);

        datos[i] = mu + sigma * z;
    }

    aplicarRestriccion(datos, n, min, max);
}

void generarLaplace(double *datos, int n, double mu, double b, double min, double max){
    double u, signo;
    for(int i = 0; i < n; i++)
    {
        u = uniforme01();
        signo = (u >= 0.5) ? 1.0 : -1.0;

        datos[i] = mu - b * signo * log(1.0 - 2.0 * fabs(u - 0.5));
    }

    aplicarRestriccion(datos, n, min, max);
}

void aplicarRestriccion(double *datos, int n, double min, double max){
    for(int i = 0; i < n; i++) {
        if(datos[i] < min)
            datos[i] = min;

        if(datos[i] > max)
            datos[i] = max;
    }
}