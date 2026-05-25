# Parte 4: step, next y backtrace

## Objetivo

Se utilizó `gdb` para analizar un error de tiempo de ejecución producido por una división entre cero. Además, se practicó la diferencia entre avanzar con `next`, entrar a funciones con `step` y revisar la pila de llamadas con `backtrace`.

## Código original

```cpp
#include <iostream>

int dividir(int a, int b) {
    int resultado = a / b;
    return resultado;
}

int calcular(int x) {
    int divisor = x - 5;
    int resultado = dividir(100, divisor);
    return resultado;
}

int main() {
    int valor = 5;
    int respuesta = calcular(valor);

    std::cout << "Respuesta: " << respuesta << std::endl;

    return 0;
}
```

## Compilación del programa original

Se compiló el programa con símbolos de depuración mediante el siguiente comando:

```bash
g++ -g -o gdb_funciones codigo/04_gdb_funciones.cpp
```

El comando no mostró errores de compilación.

## Ejecución normal del programa original

Se ejecutó el programa con el siguiente comando:

```bash
./gdb_funciones
```

Se obtuvo la siguiente salida:

```bash
Floating point exception (core dumped)
```

El programa compiló correctamente, pero falló durante la ejecución. Esto indica que no se trataba de un error de sintaxis, sino de un error de tiempo de ejecución.

## Análisis con gdb

Se abrió el programa con `gdb` usando el siguiente comando:

```bash
gdb ./gdb_funciones
```

Dentro de `gdb`, se colocó un breakpoint en la función `main`:

```gdb
break main
```

Se obtuvo:

```gdb
Breakpoint 1 at 0x11e1: file codigo/04_gdb_funciones.cpp, line 15.
```

Luego se inició la ejecución:

```gdb
run
```

El programa se detuvo en la función `main`:

```gdb
Breakpoint 1, main () at codigo/04_gdb_funciones.cpp:15
15          int valor = 5;
```

Después se utilizó `step` para avanzar y entrar a la función `calcular`:

```gdb
step
```

Se llegó a la línea donde se llama a `calcular(valor)`:

```gdb
16          int respuesta = calcular(valor);
```

Luego se ejecutó nuevamente:

```gdb
step
```

Y se entró a la función `calcular`:

```gdb
calcular (x=5) at codigo/04_gdb_funciones.cpp:9
9           int divisor = x - 5;
```

Se inspeccionó el valor de `x`:

```gdb
print x
```

Se obtuvo:

```gdb
$1 = 5
```

En este punto se observó que la función `calcular` recibió el valor `5`.

## Identificación del problema

La línea problemática dentro de `calcular` era:

```cpp
int divisor = x - 5;
```

Como `x` tenía el valor `5`, el cálculo realizado fue:

```text
divisor = 5 - 5
```

Por lo tanto, el valor de `divisor` era `0`.

Luego, ese valor se pasaba a la función `dividir`:

```cpp
int resultado = dividir(100, divisor);
```

Esto provocaba que la función intentara realizar la operación:

```cpp
100 / 0
```

La división entre cero no es válida y por eso el programa terminaba con el error:

```bash
Floating point exception (core dumped)
```

## Observación sobre la inspección de variables

Durante la sesión de `gdb`, se imprimió el valor de `divisor` antes de que la línea donde se asigna su valor terminara de ejecutarse. Por eso apareció un valor extraño:

```gdb
print divisor
$2 = 1600677166
```

Ese valor no representa el valor lógico final de la variable, sino un valor observado antes de que la asignación se completara. Después de ejecutar la línea `int divisor = x - 5;`, el valor correcto de `divisor` sería `0`.

También se intentó imprimir `a` y `b` antes de entrar completamente a la función `dividir`. Por esa razón, esos valores no fueron útiles para el análisis principal. La causa del error se identificó correctamente a partir de que `x = 5` produce `divisor = 0`.

## Uso de backtrace

Se ejecutó el comando:

```gdb
backtrace
```

Se obtuvo la siguiente salida:

```gdb
#0  calcular (x=5) at codigo/04_gdb_funciones.cpp:10
#1  0x00005555555551f2 in main () at codigo/04_gdb_funciones.cpp:16
```

El `backtrace` mostró la pila de llamadas del programa. Se observó que la ejecución estaba dentro de `calcular`, llamada desde `main`.

Esto permitió confirmar el camino de ejecución:

```text
main -> calcular
```

El error se producía porque `main` enviaba el valor `5` a `calcular`, y dentro de `calcular` ese valor generaba un divisor igual a cero.

## Evidencia de terminal antes de corregir

```bash
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -o gdb_funciones codigo/04_gdb_funciones.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./gdb_funciones
Floating point exception (core dumped)
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ gdb ./gdb_funciones
GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
Reading symbols from ./gdb_funciones...
(gdb) break main
Breakpoint 1 at 0x11e1: file codigo/04_gdb_funciones.cpp, line 15.
(gdb) run
Starting program: /home/raulpro/Diseño_Software/IE-0417/laboratorio-depuracion/gdb_funciones
Breakpoint 1, main () at codigo/04_gdb_funciones.cpp:15
15          int valor = 5;
(gdb) step
16          int respuesta = calcular(valor);
(gdb) step
calcular (x=5) at codigo/04_gdb_funciones.cpp:9
9           int divisor = x - 5;
(gdb) print x
$1 = 5
(gdb) print divisor
$2 = 1600677166
(gdb) step
10          int resultado = dividir(100, divisor);
(gdb) backtrace
#0  calcular (x=5) at codigo/04_gdb_funciones.cpp:10
#1  0x00005555555551f2 in main () at codigo/04_gdb_funciones.cpp:16
(gdb) quit
A debugging session is active.

        Inferior 1 [process 45655] will be killed.

Quit anyway? (y or n) y
```

## Corrección realizada

Se corrigió el programa agregando una validación dentro de la función `dividir`. Antes de realizar la división, se verifica si el divisor `b` es igual a cero.

Si `b` es cero, se muestra un mensaje de error y se retorna `0`. De esta forma, se evita ejecutar una división inválida.

## Código corregido

```cpp
#include <iostream>

int dividir(int a, int b) {
    if (b == 0) {
        std::cout << "Error: no se puede dividir entre cero." << std::endl;
        return 0;
    }
    int resultado = a / b;
    return resultado;
}

int calcular(int x) {
    int divisor = x - 5;
    int resultado = dividir(100, divisor);
    return resultado;
}

int main() {
    int valor = 5;
    int respuesta = calcular(valor);

    std::cout << "Respuesta: " << respuesta << std::endl;

    return 0;
}
```

## Compilación después de corregir

Se volvió a compilar el programa con el siguiente comando:

```bash
g++ -g -o gdb_funciones codigo/04_gdb_funciones.cpp
```

El comando no mostró errores, por lo que la compilación fue exitosa.

## Ejecución después de corregir

Se ejecutó el programa corregido:

```bash
./gdb_funciones
```

Se obtuvo la siguiente salida:

```bash
Error: no se puede dividir entre cero.
Respuesta: 0
```

Esto demuestra que el programa ya no termina abruptamente con `Floating point exception`. Ahora detecta el caso problemático y lo maneja de forma controlada.

## Evidencia de terminal después de corregir

```bash
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -o gdb_funciones codigo/04_gdb_funciones.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./gdb_funciones
Error: no se puede dividir entre cero.
Respuesta: 0
```

## Diferencia entre next y step

El comando `next` ejecuta la línea actual y avanza a la siguiente línea sin entrar dentro de las funciones llamadas. Es útil cuando se quiere avanzar rápidamente sin revisar los detalles internos de cada función.

El comando `step` también avanza la ejecución, pero si la línea actual contiene una llamada a función, entra dentro de esa función. Esto permite revisar paso a paso lo que ocurre internamente.

En este ejercicio se utilizó `step` porque era necesario entrar a la función `calcular` para observar el valor de `x` y analizar cómo se obtenía el divisor.

## Para qué sirve backtrace

`backtrace` sirve para mostrar la pila de llamadas del programa en un momento determinado. Permite ver qué funciones fueron llamadas para llegar al punto actual de ejecución.

En este caso, `backtrace` mostró que la ejecución estaba dentro de `calcular`, la cual había sido llamada desde `main`.

## Preguntas de reflexión

### 1. ¿Qué diferencia observó entre `next` y `step`?

Se observó que `next` permite avanzar sin entrar dentro de las funciones, mientras que `step` permite entrar a las funciones llamadas. En este ejercicio, `step` fue útil porque permitió ingresar a `calcular` y revisar el valor recibido por la función.

### 2. ¿Para qué sirve `backtrace`?

`backtrace` sirve para revisar la pila de llamadas. Permite identificar desde qué funciones se llegó al punto actual de ejecución. Esto ayuda a entender el camino que siguió el programa antes de llegar al error.

### 3. ¿Cuál fue la causa del error?

La causa del error fue una división entre cero. La variable `valor` tenía el valor `5`, por lo que en la función `calcular` se obtuvo `divisor = x - 5`, es decir, `divisor = 0`. Luego ese divisor se usó en la operación `100 / divisor`.

### 4. ¿Por qué este error es de tiempo de ejecución?

Este error es de tiempo de ejecución porque el código sí cumple con las reglas del lenguaje y compila correctamente. El problema aparece cuando el programa se ejecuta y llega a una operación inválida: dividir entre cero.

### 5. ¿Cómo podría prevenirse este tipo de error desde el diseño del programa?

Este tipo de error podría prevenirse validando los datos antes de realizar operaciones riesgosas. En este caso, la función `dividir` debe verificar que el divisor no sea cero antes de ejecutar la división. También se podría diseñar el programa para manejar errores con mensajes claros o mecanismos de control como excepciones.