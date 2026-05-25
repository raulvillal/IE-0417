# Parte 1: instalación y verificación del ambiente

## Sistema operativo utilizado

Se utilizó WSL2 de Windows para realizar todo lo solicitado.

## Verificación de herramientas instaladas

Se realizó la verificación de las herramientas necesarias para compilar, ejecutar y depurar programas en C++.

### Versión de g++

Se ejecutó el siguiente comando:

```bash
g++ --version
```

Se obtuvo la siguiente salida:

```bash
g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
Copyright (C) 2023 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

Por lo tanto, se verificó que el compilador `g++` está instalado correctamente.

### Versión de gdb

Se ejecutó el siguiente comando:

```bash
gdb --version
```

Se obtuvo la siguiente salida:

```bash
GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
Copyright (C) 2024 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

Por lo tanto, se verificó que `gdb` está instalado correctamente.

### Versión de valgrind

Se ejecutó el siguiente comando:

```bash
valgrind --version
```

Se obtuvo la siguiente salida:

```bash
valgrind-3.22.0
```

Por lo tanto, se verificó que `valgrind` está instalado correctamente.

## Programa de prueba

Se creó el archivo `codigo/prueba.cpp` con un programa sencillo para comprobar que el ambiente permite compilar y ejecutar código en C++.

El programa utilizado fue:

```cpp
#include <iostream>

int main() {
    std::cout << "Ambiente listo para depuración" << std::endl;
    return 0;
}
```

## Compilación del programa de prueba

Se compiló el programa usando símbolos de depuración con el siguiente comando:

```bash
g++ -g -o prueba codigo/prueba.cpp
```

El comando se ejecutó sin mostrar errores en la terminal. Esto indica que el archivo fuente fue compilado correctamente.

## Ejecución del programa de prueba

Se ejecutó el programa compilado con el siguiente comando:

```bash
./prueba
```

Se obtuvo la siguiente salida:

```bash
Ambiente listo para depuración
```

Por lo tanto, se comprobó que el ambiente de trabajo permite compilar y ejecutar programas en C++ correctamente.

## Explicación de las herramientas

### g++

`g++` es el compilador utilizado para traducir programas escritos en C++ a archivos ejecutables. En este laboratorio se utiliza para compilar los programas fuente antes de ejecutarlos o analizarlos con herramientas de depuración.

### gdb

`gdb` es una herramienta de depuración que permite ejecutar un programa paso a paso, detenerlo en puntos específicos, inspeccionar variables y revisar la pila de llamadas. Se utiliza para observar el comportamiento interno del programa mientras se ejecuta.

### valgrind

`valgrind` es una herramienta de análisis que permite detectar errores relacionados con memoria, como pérdidas de memoria, accesos inválidos o uso incorrecto de memoria dinámica. En este laboratorio se usará principalmente para analizar programas con errores de memoria.

### Opción -g

La opción `-g` se utiliza al compilar para incluir símbolos de depuración en el ejecutable. Estos símbolos permiten que herramientas como `gdb` relacionen el programa ejecutable con el código fuente original, mostrando nombres de variables, funciones y líneas de código.

## Preguntas de reflexión

### 1. ¿Para qué sirve `g++`?

`g++` sirve para compilar programas escritos en C++. Esta herramienta toma el código fuente y genera un archivo ejecutable que puede ser ejecutado desde la terminal.

### 2. ¿Para qué sirve `gdb`?

`gdb` sirve para depurar programas. Permite ejecutar el programa de forma controlada, detenerlo en ciertas líneas o funciones, inspeccionar variables y analizar el estado del programa cuando ocurre un error.

### 3. ¿Para qué sirve `valgrind`?

`valgrind` sirve para analizar el uso de memoria de un programa. Permite detectar errores como pérdidas de memoria, accesos fuera de límites y uso incorrecto de memoria dinámica.

### 4. ¿Por qué se recomienda compilar con `-g` al depurar?

Se recomienda compilar con `-g` porque esta opción agrega información de depuración al ejecutable. Gracias a esto, herramientas como `gdb` pueden mostrar líneas de código, nombres de variables y funciones durante la ejecución del programa.

### 5. ¿Qué diferencia hay entre compilar un programa y depurarlo?

Compilar un programa consiste en transformar el código fuente en un archivo ejecutable. Depurar un programa consiste en analizar su comportamiento durante la ejecución para encontrar errores, entender sus causas y corregirlos.