cmake_minimum_required(VERSION 4.2)
project(generador_analizador_estadistico C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(generador_analizador_estadistico
        include/estadistica.h
        include/generacion.h
        include/ordenamiento.h
        src/estadistica.c
        src/generacion.c
        src/main.c
        src/ordenamiento.c)

target_link_libraries(generador_analizador_estadistico m)