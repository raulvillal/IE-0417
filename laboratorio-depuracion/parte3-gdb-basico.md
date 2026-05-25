# Parte 3: introducción a gdb

## Objetivo

Se utilizó `gdb` para ejecutar un programa paso a paso, detener la ejecución en la función `main` e inspeccionar el valor de algunas variables durante la ejecución.

## Código utilizado

Se trabajó con el archivo `codigo/03_gdb_basico.cpp`, el cual contiene funciones simples para duplicar un número, sumar valores e imprimir los resultados.

```cpp
#include <iostream>

int duplicar(int x) {
    int resultado = x * 2;
    return resultado;
}

int sumar(int a, int b) {
    int resultado = a + b;
    return resultado;
}

int main() {
    int numero = 5;
    int doble = duplicar(numero);
    int total = sumar(doble, 10);

    std::cout << "Número: " << numero << std::endl;
    std::cout << "Doble: " << doble << std::endl;
    std::cout << "Total: " << total << std::endl;

    return 0;
}
```

## Compilación del programa

Se compiló el programa con símbolos de depuración mediante el siguiente comando:

```bash
g++ -g -o gdb_basico codigo/03_gdb_basico.cpp
```

El comando no produjo errores, por lo que la compilación fue exitosa.

## Ejecución normal del programa

Se ejecutó el programa normalmente con el siguiente comando:

```bash
./gdb_basico
```

Se obtuvo la siguiente salida:

```bash
Número: 5
Doble: 10
Total: 20
```

Esto permitió verificar que el programa funcionaba correctamente antes de analizarlo con `gdb`.

## Uso de gdb

Se abrió el programa con `gdb` mediante el siguiente comando:

```bash
gdb ./gdb_basico
```

Se obtuvo el inicio de la sesión de depuración:

```bash
GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
Reading symbols from ./gdb_basico...
```

Luego, dentro de `gdb`, se colocó un breakpoint en la función `main`:

```gdb
break main
```

Se obtuvo la siguiente respuesta:

```gdb
Breakpoint 1 at 0x11cb: file codigo/03_gdb_basico.cpp, line 14.
```

Después, se inició la ejecución del programa:

```gdb
run
```

El programa se detuvo al inicio de la función `main`:

```gdb
Breakpoint 1, main () at codigo/03_gdb_basico.cpp:14
14          int numero = 5;
```

## Ejecución paso a paso

Se avanzó línea por línea con el comando `next`.

Primero, se ejecutó:

```gdb
next
```

Y `gdb` avanzó a la siguiente línea:

```gdb
15          int doble = duplicar(numero);
```

Luego, se ejecutó nuevamente:

```gdb
next
```

Y se avanzó a la línea donde se calcula `total`:

```gdb
16          int total = sumar(doble, 10);
```

## Inspección de variables

Se inspeccionó el valor de la variable `numero` con el comando:

```gdb
print numero
```

Se obtuvo:

```gdb
$1 = 5
```

Después, se avanzó una línea más con:

```gdb
next
```

Y se inspeccionó la variable `doble`:

```gdb
print doble
```

Se obtuvo:

```gdb
$2 = 10
```

Luego, se avanzó otra línea con:

```gdb
next
```

El programa imprimió la primera línea de salida:

```bash
Número: 5
```

Finalmente, se inspeccionó la variable `total`:

```gdb
print total
```

Se obtuvo:

```gdb
$3 = 20
```

## Continuación del programa

Se continuó la ejecución del programa con:

```gdb
continue
```

Se obtuvo la salida restante:

```bash
Doble: 10
Total: 20
[Inferior 1 (process 44878) exited normally]
```

Después, se salió de `gdb` con:

```gdb
quit
```

## Evidencia de terminal

```bash
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -o gdb_basico codigo/03_gdb_basico.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./gdb_basico
Número: 5
Doble: 10
Total: 20
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ gdb ./gdb_basico
GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
Reading symbols from ./gdb_basico...
(gdb) break main
Breakpoint 1 at 0x11cb: file codigo/03_gdb_basico.cpp, line 14.
(gdb) run
Starting program: /home/raulpro/Diseño_Software/IE-0417/laboratorio-depuracion/gdb_basico
Breakpoint 1, main () at codigo/03_gdb_basico.cpp:14
14          int numero = 5;
(gdb) next
15          int doble = duplicar(numero);
(gdb) next
16          int total = sumar(doble, 10);
(gdb) print numero
$1 = 5
(gdb) next
18          std::cout << "Número: " << numero << std::endl;
(gdb) print doble
$2 = 10
(gdb) next
Número: 5
19          std::cout << "Doble: " << doble << std::endl;
(gdb) print total
$3 = 20
(gdb) continue
Continuing.
Doble: 10
Total: 20
[Inferior 1 (process 44878) exited normally]
(gdb) quit
```

## Explicación de comandos utilizados

### Opción `-g`

Se utilizó la opción `-g` al compilar para incluir símbolos de depuración en el ejecutable. Esto permitió que `gdb` mostrara las líneas del código fuente y los nombres de las variables durante la ejecución.

### `break main`

El comando `break main` se utilizó para colocar un breakpoint al inicio de la función `main`. Esto hizo que el programa se detuviera al comenzar la ejecución de dicha función.

### `run`

El comando `run` inició la ejecución del programa dentro de `gdb`.

### `next`

El comando `next` permitió avanzar línea por línea sin entrar dentro de las funciones llamadas. Por eso, al ejecutar las líneas donde se llamaba a `duplicar` y `sumar`, `gdb` ejecutó esas funciones completas sin entrar en sus instrucciones internas.

### `print`

El comando `print` permitió inspeccionar el valor de variables durante la ejecución del programa. En este caso, se usó para observar los valores de `numero`, `doble` y `total`.

### `continue`

El comando `continue` permitió continuar la ejecución normal del programa después de haberlo detenido en el breakpoint y de haber inspeccionado las variables.

## Valores observados

Durante la sesión de depuración se observaron los siguientes valores:

```text
numero = 5
doble = 10
total = 20
```

Estos valores coinciden con la lógica del programa. Primero se asignó `numero = 5`, luego se calculó el doble de ese número y finalmente se sumó `10` al resultado.

## Preguntas de reflexión

### 1. ¿Qué es un breakpoint?

Un breakpoint es un punto de interrupción colocado en una línea o función del programa. Cuando la ejecución llega a ese punto, el programa se detiene temporalmente para que se pueda inspeccionar su estado.

### 2. ¿Qué diferencia hay entre ejecutar el programa normalmente y ejecutarlo dentro de `gdb`?

Al ejecutar el programa normalmente, solamente se observa el resultado final en la terminal. Al ejecutarlo dentro de `gdb`, se puede controlar la ejecución paso a paso, detener el programa en puntos específicos e inspeccionar variables mientras el programa se está ejecutando.

### 3. ¿Qué ventaja tiene inspeccionar variables mientras el programa se ejecuta?

Inspeccionar variables durante la ejecución permite verificar si el programa está calculando y almacenando los valores esperados en cada paso. Esto ayuda a encontrar errores lógicos que no necesariamente producen mensajes de error.

### 4. ¿Por qué `next` no entra dentro de las funciones?

`next` ejecuta la línea actual completa y avanza a la siguiente línea del mismo nivel de ejecución. Si la línea contiene una llamada a función, la función se ejecuta, pero `gdb` no entra a revisar sus instrucciones internas. Para entrar dentro de una función se debe usar el comando `step`.