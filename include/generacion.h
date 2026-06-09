#ifndef GENERACION_H
#define GENERACION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



// Prototipos de funciones accesibles por el main
void aplicarRestriccion(double *datos, int n, double min, double max);
void capturarManual(double *datos, int *n);
void generarUniforme(double *datos, int n, double min, double max);
void generarNormal(double *datos, int n, double mu, double sigma, double min, double max);
void generarLaplace(double *datos, int n, double mu, double b, double min, double max);

/* GENERACION_H */
#endif