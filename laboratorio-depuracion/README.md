# Laboratorio: depuración con gdb, valgrind y sanitizers

## Información general

**Estudiante** Raúl Villalobos Vega - C18555
**Curso:** IE0417 - Diseño de software para ingeniería  
**Tema:** Depuración, análisis de memoria y análisis de hilos  
**Lenguaje:** C++  
**Herramientas utilizadas:** `g++`, `gdb`, `valgrind`, AddressSanitizer, ThreadSanitizer y Helgrind  

## Descripción

Este repositorio contiene el desarrollo del laboratorio de depuración en C++. Se trabajaron errores de sintaxis, errores lógicos, errores de tiempo de ejecución, errores de memoria y problemas de concurrencia.

Durante el laboratorio se utilizaron herramientas de depuración y análisis para observar el comportamiento de los programas, encontrar la causa de los errores y verificar que las correcciones aplicadas funcionaran correctamente.

## Objetivos del laboratorio

- Compilar programas de C++ con símbolos de depuración.
- Usar `gdb` para ejecutar programas paso a paso.
- Crear breakpoints e inspeccionar variables.
- Revisar la pila de llamadas con `backtrace`.
- Detectar pérdidas de memoria con `valgrind`.
- Detectar accesos inválidos a memoria.
- Usar AddressSanitizer para identificar errores de memoria.
- Analizar condiciones de carrera en programas multihilo.
- Corregir errores encontrados en los programas.
- Documentar el proceso de depuración de forma clara.

## Estructura del repositorio

```text
laboratorio-depuracion/
├── README.md
├── parte1-instalacion.md
├── parte2-tipos-errores.md
├── parte3-gdb-basico.md
├── parte4-gdb-funciones.md
├── parte5-valgrind.md
├── parte6-asan.md
├── parte7-hilos.md
├── parte8-reto-y-reflexion.md
└── codigo/
    ├── prueba.cpp
    ├── 01_error_sintaxis.cpp
    ├── 02_error_logico.cpp
    ├── 03_gdb_basico.cpp
    ├── 04_gdb_funciones.cpp
    ├── 05_memory_leak.cpp
    ├── 06_invalid_access.cpp
    ├── 07_use_after_free.cpp
    ├── 08_race_condition.cpp
    ├── 09_race_condition_corregido.cpp
    └── 10_reto.cpp
```

## Índice de documentación

### Parte 1: instalación y verificación del ambiente

Archivo: [`parte1-instalacion.md`](parte1-instalacion.md)

En esta parte se verificó la instalación de las herramientas necesarias para el laboratorio. Se documentaron las versiones de `g++`, `gdb` y `valgrind`, además de la compilación y ejecución de un programa de prueba.

### Parte 2: tipos de errores

Archivo: [`parte2-tipos-errores.md`](parte2-tipos-errores.md)

En esta parte se analizaron errores de sintaxis y errores lógicos. Se observó cómo el compilador detecta errores de sintaxis y cómo un error lógico puede producir resultados incorrectos aunque el programa compile correctamente.

### Parte 3: introducción a gdb

Archivo: [`parte3-gdb-basico.md`](parte3-gdb-basico.md)

En esta parte se utilizó `gdb` para ejecutar un programa paso a paso, colocar un breakpoint en `main`, avanzar con `next` e inspeccionar variables con `print`.

### Parte 4: step, next y backtrace

Archivo: [`parte4-gdb-funciones.md`](parte4-gdb-funciones.md)

En esta parte se analizó un error de tiempo de ejecución causado por una división entre cero. Se utilizó `gdb` para entrar a funciones con `step`, revisar valores y observar la pila de llamadas con `backtrace`.

### Parte 5: análisis de memoria con valgrind

Archivo: [`parte5-valgrind.md`](parte5-valgrind.md)

En esta parte se utilizó `valgrind` para detectar una pérdida de memoria y un acceso fuera de los límites de un arreglo. Se documentó la salida antes y después de corregir los programas.

### Parte 6: AddressSanitizer

Archivo: [`parte6-asan.md`](parte6-asan.md)

En esta parte se utilizó AddressSanitizer para detectar un error de uso de memoria después de haber sido liberada. Se corrigió el programa para evitar el acceso a memoria inválida.

### Parte 7: análisis de hilos y condiciones de carrera

Archivo: [`parte7-hilos.md`](parte7-hilos.md)

En esta parte se analizó un programa multihilo con una condición de carrera. Se utilizó Helgrind para detectar el problema y se corrigió usando `std::mutex` y `std::lock_guard`.

### Parte 8: mini reto y reflexión final

Archivo: [`parte8-reto-y-reflexion.md`](parte8-reto-y-reflexion.md)

En esta parte se resolvió un programa con varios errores pequeños. Se utilizaron herramientas como ejecución normal, `gdb`, `valgrind` y AddressSanitizer. Además, se incluyó una reflexión final sobre lo aprendido durante el laboratorio.

## Compilación general

Los programas se compilaron individualmente según la parte correspondiente del laboratorio. En general, se utilizó la opción `-g` para incluir símbolos de depuración.

Ejemplo:

```bash
g++ -g -o programa codigo/archivo.cpp
```

Para programas con hilos se utilizó la opción `-pthread`:

```bash
g++ -g -pthread -o programa codigo/archivo.cpp
```

Para usar AddressSanitizer se utilizó:

```bash
g++ -g -fsanitize=address -o programa_asan codigo/archivo.cpp
```

Para usar ThreadSanitizer se utilizó:

```bash
g++ -g -fsanitize=thread -pthread -o programa_tsan codigo/archivo.cpp
```


