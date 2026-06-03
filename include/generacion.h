#ifndef GENERACION_H
#define GENERACION_H

// TODO: Implementar conversión base de rand() a U(0,1)

void generarUniforme(double *arreglo, int n, double min, double max);
void generarNormal(double *arreglo, int n, double mu, double sigma);
void generarLaplace(double *arreglo, int n, double mu, double b);

// Función para restringir al intervalo [min, max] mediante recorte o rechazo
void aplicarRestriccion(double *arreglo, int n, double min, double max);

#endif // GENERACION_H