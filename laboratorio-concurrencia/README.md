# Laboratorio de programación concurrente y paralela en C++

## Estudiante

Nombre: Raúl Villalobos Vega 
Carné:  C18555

## Descripción

Este laboratorio explora conceptos básicos de programación concurrente y paralela usando C++.

Durante el laboratorio se trabaja con creación de hilos, condiciones de carrera, uso de `std::mutex`, uso de `std::lock_guard`, comparación de tiempos de ejecución, relación entre cantidad de hilos y rendimiento, y un ejemplo simple de deadlock.

## Requisitos

- `g++`
- C++17 o superior
- Sistema operativo Linux, macOS o Windows con soporte para compilación C++
- Soporte para `pthread`

## Compilación y ejecución

### Parte 1

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte1_threads.cpp -o parte1
./parte1
```

### Parte 2

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte2_race_condition.cpp -o parte2
./parte2
```

### Parte 3

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte3_mutex.cpp -o parte3
./parte3
```

### Parte 4

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pthread src/parte4_benchmark.cpp -o parte4
./parte4
```

### Parte 5

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pthread src/parte5_hilos_vs_rendimiento.cpp -o parte5
./parte5
```

### Parte 6

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte6_deadlock.cpp -o parte6
./parte6
```

El programa de la parte 6 está diseñado para producir un deadlock, por lo que puede quedarse bloqueado. En ese caso, se debe detener manualmente con:

```bash
Ctrl + C
```

### Parte 6 corregida

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte6_deadlock_corregido.cpp -o parte6_corregido
./parte6_corregido
```

## Resultados

El análisis de las ejecuciones, las tablas de resultados y las respuestas a las preguntas del laboratorio se encuentran en:

```text
resultados/analisis.md
```

## Conclusiones

Este laboratorio permitió observar que la programación con hilos puede mejorar el rendimiento cuando el trabajo puede dividirse en partes independientes. Sin embargo, también mostró que la concurrencia introduce problemas como condiciones de carrera y deadlocks.

Además, se comprobó que usar más hilos no siempre implica obtener mejor rendimiento, ya que existen costos asociados a la creación, planificación y sincronización de hilos.