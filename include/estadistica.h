/**
 * @file estadistica.h
 * @brief Declaraciones de las funciones para el cálculo de medidas estadísticas.
 *
 * Este módulo define las 15 medidas estadísticas requeridas en la Práctica 2,
 * cumpliendo la regla de una función separada por cada medida. Las funciones
 * que operan sobre datos ordenados requieren que el arreglo haya sido previamente
 * ordenado de forma ascendente.
 *
 * @date    Junio 2026
 */

#ifndef ESTADISTICA_H
#define ESTADISTICA_H

/* =========================================================
 * Medidas de posición central
 * ========================================================= */

/**
 * @brief Calcula el valor máximo del arreglo ordenado.
 * @param arreglo Arreglo de doubles ordenado ascendentemente.
 * @param n       Número de elementos (n >= 1).
 * @return        Valor máximo (último elemento).
 */
double calcularMaximo(double *arreglo, int n);

/**
 * @brief Calcula el valor mínimo del arreglo ordenado.
 * @param arreglo Arreglo de doubles ordenado ascendentemente.
 * @param n       Número de elementos (n >= 1).
 * @return        Valor mínimo (primer elemento).
 */
double calcularMinimo(double *arreglo, int n);

/**
 * @brief Calcula la media aritmética del arreglo.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        Media aritmética µ = (Σ xᵢ) / n.
 */
double calcularMedia(double *arreglo, int n);

/**
 * @brief Calcula la media geométrica del arreglo.
 * @param arreglo Arreglo de doubles con todos los valores estrictamente positivos.
 * @param n       Número de elementos (n >= 1).
 * @return        Media geométrica (∏ xᵢ)^(1/n), o NAN si algún valor es <= 0.
 * @note          Usa logaritmos internamente para evitar desbordamiento con n grande.
 */
double calcularMediaGeometrica(double *arreglo, int n);

/**
 * @brief Calcula la mediana del arreglo ordenado.
 * @param arreglo Arreglo de doubles ordenado ascendentemente.
 * @param n       Número de elementos (n >= 1).
 * @return        Elemento central si n es impar; promedio de los dos centrales si n es par.
 */
double calcularMediana(double *arreglo, int n);

/**
 * @brief Calcula la moda del arreglo.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        Valor con mayor frecuencia de repetición, o NAN si todos son únicos.
 */
double calcularModa(double *arreglo, int n);

/* =========================================================
 * Medidas de dispersión
 * ========================================================= */

/**
 * @brief Calcula la varianza poblacional del arreglo.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        Varianza σ² = (Σ (xᵢ - µ)²) / n.
 */
double calcularVarianza(double *arreglo, int n);

/**
 * @brief Calcula la desviación estándar poblacional del arreglo.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        Desviación estándar σ = √(varianza).
 */
double calcularDesviacionEstandar(double *arreglo, int n);

/**
 * @brief Calcula el coeficiente de variación del arreglo.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        CV = σ / |µ|, o NAN si la media es cero.
 */
double calcularCoeficienteVariacion(double *arreglo, int n);

/* =========================================================
 * Cuartiles (requieren arreglo ordenado)
 * ========================================================= */

/**
 * @brief Calcula el primer cuartil Q1 (percentil 25).
 * @param arreglo Arreglo de doubles ordenado ascendentemente.
 * @param n       Número de elementos (n >= 1).
 * @return        Valor de Q1.
 */
double calcularPrimerCuartil(double *arreglo, int n);

/**
 * @brief Calcula el segundo cuartil Q2 (mediana, percentil 50).
 * @param arreglo Arreglo de doubles ordenado ascendentemente.
 * @param n       Número de elementos (n >= 1).
 * @return        Valor de Q2.
 */
double calcularSegundoCuartil(double *arreglo, int n);

/**
 * @brief Calcula el tercer cuartil Q3 (percentil 75).
 * @param arreglo Arreglo de doubles ordenado ascendentemente.
 * @param n       Número de elementos (n >= 1).
 * @return        Valor de Q3.
 */
double calcularTercerCuartil(double *arreglo, int n);

/**
 * @brief Calcula el cuarto cuartil Q4 (máximo, percentil 100).
 * @param arreglo Arreglo de doubles ordenado ascendentemente.
 * @param n       Número de elementos (n >= 1).
 * @return        Valor de Q4 (elemento máximo).
 */
double calcularCuartoCuartil(double *arreglo, int n);

/* =========================================================
 * Deciles y Percentiles (requieren arreglo ordenado)
 * ========================================================= */

/**
 * @brief Calcula el k-ésimo decil del arreglo ordenado.
 * @param arreglo Arreglo de doubles ordenado ascendentemente.
 * @param n       Número de elementos (n >= 1).
 * @param k       Índice del decil (1 <= k <= 10).
 * @return        Valor del decil Dₖ, o NAN si k está fuera de rango.
 */
double calcularDecil(double *arreglo, int n, int k);

/**
 * @brief Calcula el k-ésimo percentil del arreglo ordenado.
 * @param arreglo Arreglo de doubles ordenado ascendentemente.
 * @param n       Número de elementos (n >= 1).
 * @param k       Índice del percentil (1 <= k <= 99).
 * @return        Valor del percentil Pₖ, o NAN si k está fuera de rango.
 */
double calcularPercentil(double *arreglo, int n, int k);

/* =========================================================
 * Momentos no centrados (orden 0 a 4)
 * ========================================================= */

/**
 * @brief Calcula el momento no centrado de orden 0.
 * @param arreglo Arreglo de doubles (no utilizado, por definición α₀ = 1).
 * @param n       Número de elementos.
 * @return        1.0 (por definición).
 */
double calcularMomento0(double *arreglo, int n);

/**
 * @brief Calcula el momento no centrado de orden 1 (media aritmética).
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        α₁ = µ = (Σ xᵢ) / n.
 */
double calcularMomento1(double *arreglo, int n);

/**
 * @brief Calcula el momento no centrado de orden 2.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        α₂ = (Σ xᵢ²) / n.
 */
double calcularMomento2(double *arreglo, int n);

/**
 * @brief Calcula el momento no centrado de orden 3.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        α₃ = (Σ xᵢ³) / n.
 */
double calcularMomento3(double *arreglo, int n);

/**
 * @brief Calcula el momento no centrado de orden 4.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        α₄ = (Σ xᵢ⁴) / n.
 */
double calcularMomento4(double *arreglo, int n);

/* =========================================================
 * Momentos centrados (orden 0 a 4)
 * ========================================================= */

/**
 * @brief Calcula el momento centrado de orden 0.
 * @param arreglo Arreglo de doubles (no utilizado, por definición µ₀ = 1).
 * @param n       Número de elementos.
 * @return        1.0 (por definición).
 */
double calcularMomentoCentrado0(double *arreglo, int n);

/**
 * @brief Calcula el momento centrado de orden 1.
 * @param arreglo Arreglo de doubles (no utilizado, por definición µ₁ = 0).
 * @param n       Número de elementos.
 * @return        0.0 (por definición, la desviación respecto a la media es cero).
 */
double calcularMomentoCentrado1(double *arreglo, int n);

/**
 * @brief Calcula el momento centrado de orden 2 (varianza).
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        µ₂ = σ² = (Σ (xᵢ - µ)²) / n.
 */
double calcularMomentoCentrado2(double *arreglo, int n);

/**
 * @brief Calcula el momento centrado de orden 3 (asimetría no normalizada).
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        µ₃ = (Σ (xᵢ - µ)³) / n.
 */
double calcularMomentoCentrado3(double *arreglo, int n);

/**
 * @brief Calcula el momento centrado de orden 4.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        µ₄ = (Σ (xᵢ - µ)⁴) / n.
 */
double calcularMomentoCentrado4(double *arreglo, int n);

/* =========================================================
 * Momentos estándar (orden 2, 3 y 4)
 * ========================================================= */

/**
 * @brief Calcula el momento estándar de orden 2.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        µ₂/σ² = 1.0 (por definición), o NAN si σ = 0.
 */
double calcularMomentoEstandar2(double *arreglo, int n);

/**
 * @brief Calcula el momento estándar de orden 3 (coeficiente de asimetría).
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        µ₃/σ³ (skewness), o NAN si σ = 0.
 */
double calcularMomentoEstandar3(double *arreglo, int n);

/**
 * @brief Calcula el momento estándar de orden 4 (curtosis).
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        µ₄/σ⁴, o NAN si σ = 0.
 */
double calcularMomentoEstandar4(double *arreglo, int n);

/* =========================================================
 * Curtosis
 * ========================================================= */

/**
 * @brief Calcula la curtosis (b₂) del arreglo.
 * @param arreglo Arreglo de doubles.
 * @param n       Número de elementos (n >= 1).
 * @return        b₂ = µ₄/σ⁴ = momento estándar de orden 4, o NAN si σ = 0.
 * @note          b₂ = 3 para una distribución normal. Valores > 3 indican
 *                leptocurtosis; valores < 3 indican platicurtosis.
 */
double calcularCurtosis(double *arreglo, int n);

#endif /* ESTADISTICA_H */
