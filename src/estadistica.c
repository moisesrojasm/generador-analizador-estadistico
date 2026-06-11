/**
 * @file estadistica.c
 * @brief Funciones para calcular las medidas estadisticas de la Practica 2.
 *
 * Cada medida estadistica tiene su propia funcion separada.
 * Las funciones que necesitan el arreglo ordenado (mediana, cuartiles,
 * deciles, percentiles) asumen que ya fue ordenado antes de llamarlas.
 *
 * @date    Junio 2026
 */

#include "estadistica.h"
#include <math.h>

/* ----------------------------------------------------------
 * Medidas de posicion central
 * ---------------------------------------------------------- */

double calcularMaximo(double *arreglo, int n) {
    double maximo = arreglo[0];
    for (int i = 1; i < n; i++) {
        if (arreglo[i] > maximo) {
            maximo = arreglo[i];
        }
    }
    return maximo;
}

double calcularMinimo(double *arreglo, int n) {
    double minimo = arreglo[0];
    for (int i = 1; i < n; i++) {
        if (arreglo[i] < minimo) {
            minimo = arreglo[i];
        }
    }
    return minimo;
}

double calcularMedia(double *arreglo, int n) {
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        suma += arreglo[i];
    }
    return suma / n;
}

double calcularMediaGeometrica(double *arreglo, int n) {
    /*
     * Se usa log y exp en vez de multiplicar todos los valores
     * porque con n grande el producto se desbordaria.
     * Es equivalente a sacar la raiz n-esima del producto.
     */
    double sumaLog = 0.0;
    for (int i = 0; i < n; i++) {
        if (arreglo[i] <= 0.0) {
            return NAN;  /* no esta definida para valores <= 0 */
        }
        sumaLog += log(arreglo[i]);
    }
    return exp(sumaLog / n);
}

double calcularMediana(double *arreglo, int n) {
    /* el arreglo debe estar ordenado antes de llamar esta funcion */
    if (n % 2 == 0) {
        /* si n es par se promedian los dos del centro */
        return (arreglo[n / 2 - 1] + arreglo[n / 2]) / 2.0;
    } else {
        /* si n es impar se toma el del centro */
        return arreglo[n / 2];
    }
}

double calcularModa(double *arreglo, int n) {
    int    frecuenciaMaxima = 0;
    double moda = NAN;

    for (int i = 0; i < n; i++) {
        int frecuencia = 1;
        for (int j = i + 1; j < n; j++) {
            if (arreglo[i] == arreglo[j]) {
                frecuencia++;
            }
        }
        /* solo se actualiza si supera la frecuencia maxima anterior */
        if (frecuencia > frecuenciaMaxima && frecuencia > 1) {
            frecuenciaMaxima = frecuencia;
            moda = arreglo[i];
        }
    }
    return moda;
}

/* ----------------------------------------------------------
 * Medidas de dispersion
 * ---------------------------------------------------------- */

double calcularVarianza(double *arreglo, int n) {
    double media = calcularMedia(arreglo, n);
    double suma  = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = arreglo[i] - media;
        suma += diff * diff;
    }
    return suma / n;
}

double calcularDesviacionEstandar(double *arreglo, int n) {
    double media = calcularMedia(arreglo, n);
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = arreglo[i] - media;
        suma += diff * diff;
    }
    return sqrt(suma / n);
}

double calcularCoeficienteVariacion(double *arreglo, int n) {
    double media = calcularMedia(arreglo, n);
    if (media == 0.0) {
        return NAN;  /* no se puede dividir entre cero */
    }
    /* CV = sigma / |media|, segun la formula del PDF */
    return calcularDesviacionEstandar(arreglo, n) / fabs(media);
}

/* ----------------------------------------------------------
 * Cuartiles (el arreglo debe estar ordenado)
 * ---------------------------------------------------------- */

double calcularPrimerCuartil(double *arreglo, int n) {
    /* Q1 es la mediana de la mitad inferior */
    int mitad = n / 2;
    if (mitad % 2 == 0) {
        return (arreglo[mitad / 2 - 1] + arreglo[mitad / 2]) / 2.0;
    } else {
        return arreglo[mitad / 2];
    }
}

double calcularSegundoCuartil(double *arreglo, int n) {
    /* Q2 es igual a la mediana */
    return calcularMediana(arreglo, n);
}

double calcularTercerCuartil(double *arreglo, int n) {
    /* Q3 es la mediana de la mitad superior */
    int inicio = (n % 2 == 0) ? n / 2 : n / 2 + 1;
    int tam    = n - inicio;
    if (tam % 2 == 0) {
        return (arreglo[inicio + tam / 2 - 1] +
                arreglo[inicio + tam / 2]) / 2.0;
    } else {
        return arreglo[inicio + tam / 2];
    }
}

double calcularCuartoCuartil(double *arreglo, int n) {
    /* Q4 es el maximo, el ultimo elemento del arreglo ordenado */
    return arreglo[n - 1];
}

/* ----------------------------------------------------------
 * Deciles y Percentiles (el arreglo debe estar ordenado)
 * ---------------------------------------------------------- */

double calcularDecil(double *arreglo, int n, int k) {
    if (k < 1 || k > 10) {
        return NAN;
    }

    double posicion = (k * (n + 1)) / 10.0;
    int    inferior = (int)floor(posicion);
    double fraccion = posicion - inferior;

    /* proteccion para no salirse del arreglo */
    if (inferior <= 0) return arreglo[0];
    if (inferior >= n) return arreglo[n - 1];

    if (fraccion == 0.0) {
        return arreglo[inferior - 1];
    }

    /* interpolacion entre los dos valores mas cercanos */
    return arreglo[inferior - 1] +
           fraccion * (arreglo[inferior] - arreglo[inferior - 1]);
}

double calcularPercentil(double *arreglo, int n, int k) {
    if (k < 1 || k > 99) {
        return NAN;
    }

    double posicion = (k * (n + 1)) / 100.0;
    int    inferior = (int)floor(posicion);
    double fraccion = posicion - inferior;

    /* proteccion para no salirse del arreglo */
    if (inferior <= 0) return arreglo[0];
    if (inferior >= n) return arreglo[n - 1];

    if (fraccion == 0.0) {
        return arreglo[inferior - 1];
    }

    /* interpolacion entre los dos valores mas cercanos */
    return arreglo[inferior - 1] +
           fraccion * (arreglo[inferior] - arreglo[inferior - 1]);
}

/* ----------------------------------------------------------
 * Momentos no centrados (orden 0 al 4)
 * ---------------------------------------------------------- */

double calcularMomento0(double *arreglo, int n) {
    /* por definicion el momento de orden 0 siempre es 1 */
    (void)arreglo;
    (void)n;
    return 1.0;
}

double calcularMomento1(double *arreglo, int n) {
    /* el momento de orden 1 es la media */
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        suma += arreglo[i];
    }
    return suma / n;
}

double calcularMomento2(double *arreglo, int n) {
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        suma += arreglo[i] * arreglo[i];
    }
    return suma / n;
}

double calcularMomento3(double *arreglo, int n) {
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        suma += arreglo[i] * arreglo[i] * arreglo[i];
    }
    return suma / n;
}

double calcularMomento4(double *arreglo, int n) {
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        double x2 = arreglo[i] * arreglo[i];
        suma += x2 * x2;
    }
    return suma / n;
}

/* ----------------------------------------------------------
 * Momentos centrados (orden 0 al 4)
 * ---------------------------------------------------------- */

double calcularMomentoCentrado0(double *arreglo, int n) {
    /* por definicion el momento centrado de orden 0 es 1 */
    (void)arreglo;
    (void)n;
    return 1.0;
}

double calcularMomentoCentrado1(double *arreglo, int n) {
    /* por definicion el momento centrado de orden 1 es 0 */
    (void)arreglo;
    (void)n;
    return 0.0;
}

double calcularMomentoCentrado2(double *arreglo, int n) {
    /* el momento centrado de orden 2 es la varianza */
    double media = calcularMedia(arreglo, n);
    double suma  = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = arreglo[i] - media;
        suma += diff * diff;
    }
    return suma / n;
}

double calcularMomentoCentrado3(double *arreglo, int n) {
    double media = calcularMedia(arreglo, n);
    double suma  = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = arreglo[i] - media;
        suma += diff * diff * diff;
    }
    return suma / n;
}

double calcularMomentoCentrado4(double *arreglo, int n) {
    double media = calcularMedia(arreglo, n);
    double suma  = 0.0;
    for (int i = 0; i < n; i++) {
        double diff  = arreglo[i] - media;
        double diff2 = diff * diff;
        suma += diff2 * diff2;
    }
    return suma / n;
}

/* ----------------------------------------------------------
 * Momentos estandar (orden 2, 3 y 4)
 * ---------------------------------------------------------- */

double calcularMomentoEstandar2(double *arreglo, int n) {
    /* momento estandar de orden 2 = varianza / sigma^2 = 1 por definicion */
    double desv = calcularDesviacionEstandar(arreglo, n);
    if (desv == 0.0) {
        return NAN;
    }
    return 1.0;
}

double calcularMomentoEstandar3(double *arreglo, int n) {
    double media = calcularMedia(arreglo, n);
    double desv  = calcularDesviacionEstandar(arreglo, n);
    if (desv == 0.0) {
        return NAN;
    }
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        double z = (arreglo[i] - media) / desv;
        suma += z * z * z;
    }
    return suma / n;
}

double calcularMomentoEstandar4(double *arreglo, int n) {
    double media = calcularMedia(arreglo, n);
    double desv  = calcularDesviacionEstandar(arreglo, n);
    if (desv == 0.0) {
        return NAN;
    }
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        double z  = (arreglo[i] - media) / desv;
        double z2 = z * z;
        suma += z2 * z2;
    }
    return suma / n;
}

/* ----------------------------------------------------------
 * Curtosis
 * ---------------------------------------------------------- */

double calcularCurtosis(double *arreglo, int n) {
    /* la curtosis es el momento estandar de orden 4 */
    return calcularMomentoEstandar4(arreglo, n);
}
