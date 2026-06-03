# Análisis Estadístico y Generación Aleatoria

## Descripción del Proyecto
Este proyecto es un programa modular desarrollado en C que permite obtener automáticamente el análisis estadístico de conjuntos de datos numéricos de hasta 100,000 muestras. Fue diseñado para generar escenarios de simulación y comparar la eficiencia de múltiples algoritmos de ordenamiento frente a diferentes distribuciones probabilísticas.

El programa está estructurado bajo los más altos estándares de ingeniería de software, contando con modularidad estricta, rutinas de evaluación de rendimiento temporal y documentación autogenerada mediante Doxygen.

## Estructura del Proyecto

```plaintext
generador-analizador-estadistico/
├── .gitignore   
├── .gitattributes        
├── Makefile          
├── README.md
├── bin/
├── build/
├── docs/
│   ├── html/
│   ├── Reporte_Practica2.pdf
│   └── Doxyfile
├── include/
│   ├── estadistica.h
│   ├── generacion.h
│   └── ordenamiento.h
└── src/
    ├── estadistica.c
    ├── generacion.c
    ├── main.c
    └── ordenamiento.c
```

* `src/`: Contiene el código fuente (`.c`), dividido en los módulos principales (`main.c`, `generacion.c`, `ordenamiento.c` y `estadistica.c`).
* `include/`: Contiene los archivos de cabecera (`.h`) con los prototipos de las funciones de cada módulo.
* `bin/`: Directorio de salida donde se aloja el ejecutable final tras la compilación.
* `docs/`: Documentación del proyecto, incluyendo el reporte final en PDF y la documentación en HTML generada por Doxygen.

## Características Principales

* **Generador Aleatorio:** Generación automática de datos usando las distribuciones Uniforme, Normal (Gaussiana) y Laplace (doble exponencial)
* **Modos de Parametrización:** Las distribuciones pueden configurarse por modo de rango (ingresando el mínimo y máximo) o modo por parámetros (ingresando propiedades de la distribución, como la media y la varianza)
* **Motor de Ordenamiento:** Implementación modular de 8 algoritmos de ordenamiento para evaluar su complejidad temporal y espacial: Burbuja, Pares y nones, Selección, Inserción, Casilleros (Bucket Sort), Burbuja bidireccional (Cocktail Sort), Shell y Conteo (Counting Sort).
* **Análisis Estadístico:** Cálculo de 15 medidas estadísticas independientes, incluyendo media, mediana, moda, varianza, percentiles, cuartiles, momentos centrados, momentos no centrados y curtosis
* **Doble Interfaz:** El programa puede operarse de forma manual mediante un menú interactivo en consola (`printf`/`scanf`) o automatizarse a través de argumentos de línea de comandos (`argc`/`argv`).

