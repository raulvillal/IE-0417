# Parte 6: AddressSanitizer

## Objetivo

Se utilizó AddressSanitizer para detectar un error de uso de memoria después de haber sido liberada. Este tipo de error puede no ser evidente durante una ejecución normal, por lo que se requiere una herramienta de análisis para identificarlo con claridad.

## Código original

```cpp
#include <iostream>

int main() {
    int* numero = new int;
    *numero = 42;

    delete numero;

    std::cout << "Número: " << *numero << std::endl;

    return 0;
}
```

## Descripción del programa

El programa reserva memoria dinámica para un entero, almacena el valor `42`, libera la memoria con `delete` y luego intenta imprimir nuevamente el valor usando el mismo puntero.

El problema es que después de ejecutar:

```cpp
delete numero;
```

la memoria apuntada por `numero` ya no pertenece válidamente al programa. Por lo tanto, esta línea produce un uso inválido de memoria:

```cpp
std::cout << "Número: " << *numero << std::endl;
```

## Compilación sin AddressSanitizer

Se compiló el programa normalmente con el siguiente comando:

```bash
g++ -g -o use_after_free codigo/07_use_after_free.cpp
```

El comando no mostró errores de compilación.

## Ejecución sin AddressSanitizer

Se ejecutó el programa con el siguiente comando:

```bash
./use_after_free
```

Se obtuvo la siguiente salida:

```bash
Número: 1664918909
```

El programa no terminó con un error visible, pero imprimió un valor incorrecto. Esto ocurrió porque se intentó leer memoria que ya había sido liberada. El resultado no es confiable, ya que el programa incurre en comportamiento indefinido.

## Compilación con AddressSanitizer

Se compiló el programa usando AddressSanitizer con el siguiente comando:

```bash
g++ -g -fsanitize=address -o use_after_free_asan codigo/07_use_after_free.cpp
```

El comando no mostró errores de compilación.

## Ejecución con AddressSanitizer

Se ejecutó el programa instrumentado con AddressSanitizer:

```bash
./use_after_free_asan
```

Se obtuvo el siguiente reporte relevante:

```bash
==66873==ERROR: AddressSanitizer: heap-use-after-free on address 0x502000000010 at pc 0x611bd5b0a34e bp 0x7ffd7baa1ff0 sp 0x7ffd7baa1fe0
READ of size 4 at 0x502000000010 thread T0
    #0 0x611bd5b0a34d in main codigo/07_use_after_free.cpp:9
```

El reporte también indicó dónde fue liberada la memoria:

```bash
freed by thread T0 here:
    #0 0x72826daff5e8 in operator delete(void*, unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:164
    #1 0x611bd5b0a2f9 in main codigo/07_use_after_free.cpp:7
```

Además, indicó dónde había sido reservada originalmente:

```bash
previously allocated by thread T0 here:
    #0 0x72826dafe548 in operator new(unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:95
    #1 0x611bd5b0a29e in main codigo/07_use_after_free.cpp:4
```

Finalmente, el resumen indicó el tipo de error y la línea donde ocurrió:

```bash
SUMMARY: AddressSanitizer: heap-use-after-free codigo/07_use_after_free.cpp:9 in main
```

## Explicación del error

AddressSanitizer reportó un error de tipo `heap-use-after-free`. Esto significa que el programa intentó usar memoria del heap después de haberla liberado.

La memoria fue reservada en la línea:

```cpp
int* numero = new int;
```

Luego fue liberada en la línea:

```cpp
delete numero;
```

Después, el programa intentó leer esa misma memoria en la línea:

```cpp
std::cout << "Número: " << *numero << std::endl;
```

Esa lectura ya no era válida, porque el puntero apuntaba a una región de memoria que había sido devuelta al sistema.

## Significado de heap-use-after-free

`heap-use-after-free` significa que se está usando memoria dinámica después de haber sido liberada. Este error es peligroso porque el valor leído puede cambiar, puede parecer correcto por casualidad, puede provocar una falla del programa o puede afectar otras partes de la memoria.

En la ejecución normal se obtuvo un número incorrecto:

```bash
Número: 1664918909
```

Esto demuestra que el programa seguía ejecutándose, pero el resultado no era confiable.

## Corrección realizada

Se corrigió el programa cambiando el orden de las operaciones. Primero se imprime el valor mientras la memoria sigue siendo válida y después se libera la memoria.

También se asignó el puntero a `nullptr` después de liberar la memoria. Esto ayuda a evitar que el puntero siga apuntando a una dirección que ya no debe usarse.

## Código corregido

```cpp
#include <iostream>

int main() {
    int* numero = new int;
    *numero = 42;

    std::cout << "Número: " << *numero << std::endl;

    delete numero;
    numero = nullptr;

    return 0;
}
```

## Compilación después de corregir

Se compiló nuevamente el programa corregido sin AddressSanitizer:

```bash
g++ -g -o use_after_free codigo/07_use_after_free.cpp
```

El comando no mostró errores.

## Ejecución después de corregir sin AddressSanitizer

Se ejecutó el programa corregido:

```bash
./use_after_free
```

Se obtuvo:

```bash
Número: 42
```

El programa imprimió el valor esperado.

## Compilación después de corregir con AddressSanitizer

Se volvió a compilar el programa corregido usando AddressSanitizer:

```bash
g++ -g -fsanitize=address -o use_after_free_asan codigo/07_use_after_free.cpp
```

El comando no mostró errores.

## Ejecución después de corregir con AddressSanitizer

Se ejecutó el programa corregido con AddressSanitizer:

```bash
./use_after_free_asan
```

Se obtuvo:

```bash
Número: 42
```

AddressSanitizer no reportó errores, por lo que se verificó que el uso de memoria fue corregido.

## Evidencia de terminal

```bash
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -o use_after_free codigo/07_use_after_free.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./use_after_free
Número: 1664918909
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -fsanitize=address -o use_after_free_asan codigo/07_use_after_free.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./use_after_free_asan
=================================================================
==66873==ERROR: AddressSanitizer: heap-use-after-free on address 0x502000000010 at pc 0x611bd5b0a34e bp 0x7ffd7baa1ff0 sp 0x7ffd7baa1fe0
READ of size 4 at 0x502000000010 thread T0
    #0 0x611bd5b0a34d in main codigo/07_use_after_free.cpp:9
SUMMARY: AddressSanitizer: heap-use-after-free codigo/07_use_after_free.cpp:9 in main
==66873==ABORTING
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -o use_after_free codigo/07_use_after_free.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./use_after_free
Número: 42
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -fsanitize=address -o use_after_free_asan codigo/07_use_after_free.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./use_after_free_asan
Número: 42
```

## Reflexión del ejercicio

Este ejercicio mostró que un programa puede compilar y ejecutarse aunque esté usando memoria de forma incorrecta. En la ejecución sin AddressSanitizer, el programa imprimió un número incorrecto en lugar de fallar directamente.

AddressSanitizer permitió identificar claramente el problema, indicando que se trataba de un `heap-use-after-free`, mostrando la línea donde se intentó leer la memoria liberada, la línea donde se liberó y la línea donde se reservó originalmente.

La corrección consistió en no utilizar el puntero después de liberar la memoria. Primero se imprimió el valor y luego se ejecutó `delete`. Finalmente, se asignó `nullptr` al puntero como buena práctica.

## Preguntas de reflexión

### 1. ¿Qué significa usar memoria después de liberarla?

Usar memoria después de liberarla significa acceder a una región de memoria que ya fue devuelta al sistema mediante `delete` o `delete[]`. Aunque el puntero todavía contenga una dirección, esa dirección ya no debe utilizarse.

### 2. ¿Por qué este error puede ser difícil de detectar sin herramientas?

Puede ser difícil de detectar porque el programa no siempre falla. A veces imprime valores incorrectos, a veces parece funcionar y en otros casos puede fallar de forma inesperada. Esto ocurre porque el comportamiento es indefinido.

### 3. ¿Qué ventaja tiene AddressSanitizer sobre ejecutar el programa normalmente?

AddressSanitizer permite detectar errores de memoria durante la ejecución e informa el tipo de error, la línea donde ocurre, dónde se reservó la memoria y dónde fue liberada. En cambio, una ejecución normal puede no mostrar ningún error claro.

### 4. ¿Qué diferencia observó entre el reporte de `valgrind` y el reporte de AddressSanitizer?

El reporte de AddressSanitizer fue más directo para este caso, porque indicó inmediatamente el error `heap-use-after-free`, la línea exacta de la lectura inválida, la línea donde se liberó la memoria y la línea donde fue reservada. `valgrind` también permite detectar errores de memoria, pero AddressSanitizer se integra desde la compilación mediante `-fsanitize=address`.

### 5. ¿Por qué es buena práctica asignar `nullptr` después de liberar un puntero?

Asignar `nullptr` después de liberar un puntero ayuda a evitar que el puntero siga apuntando a una dirección de memoria inválida. De esta forma, si por error se intenta usar después, es más fácil detectar que ya no apunta a un objeto válido.