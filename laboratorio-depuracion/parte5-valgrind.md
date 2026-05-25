# Parte 5: análisis de memoria con valgrind

## Ejercicio 1: pérdida de memoria

## Objetivo

Se utilizó `valgrind` para detectar una pérdida de memoria en un programa que reserva memoria dinámica con `new[]`.

## Código original

```cpp
#include <iostream>

void crear_arreglo() {
    int* datos = new int[10];

    for (int i = 0; i < 10; i++) {
        datos[i] = i * 2;
    }

    std::cout << "Primer elemento: " << datos[0] << std::endl;
}

int main() {
    crear_arreglo();
    return 0;
}
```

## Descripción del programa

El programa define una función llamada `crear_arreglo`, en la cual se reserva memoria dinámica para un arreglo de enteros. Luego se llena el arreglo con valores generados dentro de un ciclo y se imprime el primer elemento.

El problema del código original es que la memoria reservada con `new[]` no se libera antes de que termine la función. Por esta razón, el programa puede finalizar aparentemente bien, pero deja memoria sin liberar.

## Compilación del programa original

Se compiló el programa con símbolos de depuración mediante el siguiente comando:

```bash
g++ -g -o memory_leak codigo/05_memory_leak.cpp
```

El comando no mostró errores, por lo que la compilación fue exitosa.

## Ejecución normal del programa original

Se ejecutó el programa con el siguiente comando:

```bash
./memory_leak
```

Se obtuvo la siguiente salida:

```bash
Primer elemento: 0
```

El programa terminó sin mostrar errores visibles. Sin embargo, esto no garantiza que el uso de memoria sea correcto.

## Análisis con valgrind

Se ejecutó el programa con `valgrind` mediante el siguiente comando:

```bash
valgrind --leak-check=yes ./memory_leak
```

Se obtuvo la siguiente salida relevante:

```bash
==64608== HEAP SUMMARY:
==64608==     in use at exit: 40 bytes in 1 blocks
==64608==   total heap usage: 3 allocs, 2 frees, 74,792 bytes allocated
==64608==
==64608== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==64608==    at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==64608==    by 0x1091BE: crear_arreglo() (05_memory_leak.cpp:4)
==64608==    by 0x10923E: main (05_memory_leak.cpp:15)
==64608==
==64608== LEAK SUMMARY:
==64608==    definitely lost: 40 bytes in 1 blocks
==64608==    indirectly lost: 0 bytes in 0 blocks
==64608==      possibly lost: 0 bytes in 0 blocks
==64608==    still reachable: 0 bytes in 0 blocks
==64608==         suppressed: 0 bytes in 0 blocks
==64608==
==64608== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

También se ejecutó una revisión más detallada con el siguiente comando:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./memory_leak
```

Se obtuvo nuevamente que había memoria definitivamente perdida:

```bash
==64635== HEAP SUMMARY:
==64635==     in use at exit: 40 bytes in 1 blocks
==64635==   total heap usage: 3 allocs, 2 frees, 74,792 bytes allocated
==64635==
==64635== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==64635==    at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==64635==    by 0x1091BE: crear_arreglo() (05_memory_leak.cpp:4)
==64635==    by 0x10923E: main (05_memory_leak.cpp:15)
==64635==
==64635== LEAK SUMMARY:
==64635==    definitely lost: 40 bytes in 1 blocks
==64635==    indirectly lost: 0 bytes in 0 blocks
==64635==      possibly lost: 0 bytes in 0 blocks
==64635==    still reachable: 0 bytes in 0 blocks
==64635==         suppressed: 0 bytes in 0 blocks
==64635==
==64635== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## Explicación del problema

`valgrind` reportó que había memoria marcada como `definitely lost`. Esto significa que el programa reservó memoria dinámica, pero terminó sin liberarla y sin conservar una referencia válida para acceder a ella.

La línea señalada por `valgrind` fue:

```cpp
int* datos = new int[10];
```

En esa línea se reserva memoria dinámica para el arreglo. El problema no está en reservar la memoria, sino en que el programa no ejecutaba una instrucción correspondiente para liberarla.

## Significado de definitely lost

La categoría `definitely lost` indica que existe memoria reservada en el heap que ya no puede ser liberada por el programa, porque se perdió el puntero que permitía acceder a ella.

En este caso, el puntero `datos` era una variable local dentro de la función `crear_arreglo`. Cuando la función terminaba, ese puntero dejaba de existir, pero la memoria reservada con `new[]` seguía ocupada.

## Corrección realizada

Se corrigió el programa agregando la instrucción:

```cpp
delete[] datos;
```

Esta instrucción libera la memoria reservada con `new[]`.

## Código corregido

```cpp
#include <iostream>

void crear_arreglo() {
    int* datos = new int[10];

    for (int i = 0; i < 10; i++) {
        datos[i] = i * 2;
    }

    std::cout << "Primer elemento: " << datos[0] << std::endl;

    delete[] datos;
}

int main() {
    crear_arreglo();
    return 0;
}
```

## Compilación después de corregir

Se volvió a compilar el programa corregido con el siguiente comando:

```bash
g++ -g -o memory_leak codigo/05_memory_leak.cpp
```

El comando no mostró errores.

## Análisis con valgrind después de corregir

Se ejecutó nuevamente `valgrind` con el siguiente comando:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./memory_leak
```

Se obtuvo la siguiente salida relevante:

```bash
==64687== HEAP SUMMARY:
==64687==     in use at exit: 0 bytes in 0 blocks
==64687==   total heap usage: 3 allocs, 3 frees, 74,792 bytes allocated
==64687==
==64687== All heap blocks were freed -- no leaks are possible
==64687==
==64687== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Esto confirmó que la memoria reservada fue liberada correctamente.

## Ejecución final del programa corregido

Se ejecutó el programa corregido de forma normal:

```bash
./memory_leak
```

Se obtuvo:

```bash
Primer elemento: 0
```

El programa produjo la misma salida visible, pero ahora sin pérdida de memoria según el análisis de `valgrind`.

## Evidencia de terminal

```bash
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -o memory_leak codigo/05_memory_leak.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./memory_leak
Primer elemento: 0
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ valgrind --leak-check=yes ./memory_leak
==64608== Memcheck, a memory error detector
==64608== Command: ./memory_leak
==64608==
Primer elemento: 0
==64608==
==64608== HEAP SUMMARY:
==64608==     in use at exit: 40 bytes in 1 blocks
==64608==   total heap usage: 3 allocs, 2 frees, 74,792 bytes allocated
==64608==
==64608== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==64608==    at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==64608==    by 0x1091BE: crear_arreglo() (05_memory_leak.cpp:4)
==64608==    by 0x10923E: main (05_memory_leak.cpp:15)
==64608==
==64608== LEAK SUMMARY:
==64608==    definitely lost: 40 bytes in 1 blocks
==64608==    indirectly lost: 0 bytes in 0 blocks
==64608==      possibly lost: 0 bytes in 0 blocks
==64608==    still reachable: 0 bytes in 0 blocks
==64608==         suppressed: 0 bytes in 0 blocks
==64608==
==64608== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -o memory_leak codigo/05_memory_leak.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ valgrind --leak-check=full --show-leak-kinds=all ./memory_leak
==64687== Memcheck, a memory error detector
==64687== Command: ./memory_leak
==64687==
Primer elemento: 0
==64687==
==64687== HEAP SUMMARY:
==64687==     in use at exit: 0 bytes in 0 blocks
==64687==   total heap usage: 3 allocs, 3 frees, 74,792 bytes allocated
==64687==
==64687== All heap blocks were freed -- no leaks are possible
==64687==
==64687== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./memory_leak
Primer elemento: 0
```

## Reflexión del ejercicio

Este ejercicio mostró que un programa puede ejecutarse y mostrar una salida correcta aunque internamente tenga un problema de memoria. La ejecución normal solamente mostró `Primer elemento: 0`, pero `valgrind` permitió identificar que la memoria reservada con `new[]` no estaba siendo liberada.

La corrección consistió en liberar explícitamente la memoria dinámica con `delete[]`. Después de aplicar esta corrección, `valgrind` confirmó que todos los bloques de memoria fueron liberados y que no quedaban errores reportados.

## Ejercicio 2: 

## Objetivo

Se utilizó `valgrind` para detectar un acceso fuera de los límites de un arreglo reservado dinámicamente.

## Código original

```cpp
#include <iostream>

int main() {
    int* arreglo = new int[5];

    for (int i = 0; i <= 5; i++) {
        arreglo[i] = i * 10;
    }

    std::cout << "Programa finalizado" << std::endl;

    delete[] arreglo;

    return 0;
}
```

## Descripción del programa

El programa reserva memoria dinámica para un arreglo de cinco enteros. Luego utiliza un ciclo `for` para asignar valores a las posiciones del arreglo y finalmente libera la memoria con `delete[]`.

El problema se encuentra en la condición del ciclo:

```cpp
i <= 5
```

Como el arreglo tiene cinco posiciones, los índices válidos van de `0` a `4`. Sin embargo, el ciclo también intenta acceder a `arreglo[5]`, que está fuera del bloque de memoria reservado.

## Compilación del programa original

Se compiló el programa con símbolos de depuración mediante el siguiente comando:

```bash
g++ -g -o invalid_access codigo/06_invalid_access.cpp
```

El comando no mostró errores de compilación.

## Ejecución normal del programa original

Se ejecutó el programa con el siguiente comando:

```bash
./invalid_access
```

Se obtuvo la siguiente salida:

```bash
Programa finalizado
```

El programa terminó aparentemente bien. Sin embargo, esto no significa que el acceso a memoria haya sido correcto, ya que algunos errores de memoria no siempre producen un fallo visible durante la ejecución normal.

## Análisis con valgrind

Se ejecutó el programa con `valgrind` mediante el siguiente comando:

```bash
valgrind --leak-check=full ./invalid_access
```

Se obtuvo la siguiente salida relevante:

```bash
==65374== Invalid write of size 4
==65374==    at 0x1091ED: main (06_invalid_access.cpp:7)
==65374==  Address 0x4e29094 is 0 bytes after a block of size 20 alloc'd
==65374==    at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==65374==    by 0x1091BE: main (06_invalid_access.cpp:4)
```

También se obtuvo el siguiente resumen:

```bash
==65374== HEAP SUMMARY:
==65374==     in use at exit: 0 bytes in 0 blocks
==65374==   total heap usage: 3 allocs, 3 frees, 74,772 bytes allocated
==65374==
==65374== All heap blocks were freed -- no leaks are possible
==65374==
==65374== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## Explicación del problema

`valgrind` reportó un error de tipo `Invalid write of size 4`. Esto significa que el programa intentó escribir cuatro bytes en una dirección de memoria que no pertenecía válidamente al arreglo.

La línea señalada fue:

```cpp
arreglo[i] = i * 10;
```

El error ocurrió porque el ciclo permitía que `i` llegara hasta `5`:

```cpp
for (int i = 0; i <= 5; i++)
```

Cuando `i` toma el valor `5`, el programa intenta escribir en:

```cpp
arreglo[5]
```

Esa posición no existe dentro del arreglo reservado con:

```cpp
int* arreglo = new int[5];
```

Las posiciones válidas eran únicamente:

```text
arreglo[0], arreglo[1], arreglo[2], arreglo[3], arreglo[4]
```

## Significado de Invalid write

`Invalid write` significa que el programa intentó escribir en una dirección de memoria no válida para el bloque reservado. En este caso, la escritura ocurrió justo después del bloque de memoria del arreglo.

El mensaje de `valgrind` indicó:

```bash
Address 0x4e29094 is 0 bytes after a block of size 20 alloc'd
```

Esto significa que la dirección donde se intentó escribir estaba inmediatamente después del bloque de memoria reservado. Como cada entero ocupa cuatro bytes y se reservaron cinco enteros, el bloque tenía veinte bytes. La escritura inválida ocurrió justo después de esos veinte bytes.

## Corrección realizada

Se corrigió la condición del ciclo para que solo recorra los índices válidos del arreglo.

La condición original era:

```cpp
i <= 5
```

La condición corregida fue:

```cpp
i < 5
```

De esta forma, el ciclo se ejecuta para los valores `0`, `1`, `2`, `3` y `4`, sin intentar acceder a `arreglo[5]`.

## Código corregido

```cpp
#include <iostream>

int main() {
    int* arreglo = new int[5];

    for (int i = 0; i < 5; i++) {
        arreglo[i] = i * 10;
    }

    std::cout << "Programa finalizado" << std::endl;

    delete[] arreglo;

    return 0;
}
```

## Compilación después de corregir

Se volvió a compilar el programa con el siguiente comando:

```bash
g++ -g -o invalid_access codigo/06_invalid_access.cpp
```

El comando no mostró errores de compilación.

## Ejecución después de corregir

Se ejecutó el programa corregido:

```bash
./invalid_access
```

Se obtuvo la siguiente salida:

```bash
Programa finalizado
```

## Análisis con valgrind después de corregir

Se ejecutó nuevamente `valgrind`:

```bash
valgrind --leak-check=full ./invalid_access
```

Se obtuvo la siguiente salida relevante:

```bash
==65547== HEAP SUMMARY:
==65547==     in use at exit: 0 bytes in 0 blocks
==65547==   total heap usage: 3 allocs, 3 frees, 74,772 bytes allocated
==65547==
==65547== All heap blocks were freed -- no leaks are possible
==65547==
==65547== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Esto confirmó que el acceso fuera de límites fue corregido correctamente.

## Evidencia de terminal

```bash
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -o invalid_access codigo/06_invalid_access.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./invalid_access
Programa finalizado
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ valgrind --leak-check=full ./invalid_access
==65374== Memcheck, a memory error detector
==65374== Command: ./invalid_access
==65374==
==65374== Invalid write of size 4
==65374==    at 0x1091ED: main (06_invalid_access.cpp:7)
==65374==  Address 0x4e29094 is 0 bytes after a block of size 20 alloc'd
==65374==    at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==65374==    by 0x1091BE: main (06_invalid_access.cpp:4)
==65374==
Programa finalizado
==65374==
==65374== HEAP SUMMARY:
==65374==     in use at exit: 0 bytes in 0 blocks
==65374==   total heap usage: 3 allocs, 3 frees, 74,772 bytes allocated
==65374==
==65374== All heap blocks were freed -- no leaks are possible
==65374==
==65374== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -o invalid_access codigo/06_invalid_access.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./invalid_access
Programa finalizado
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ valgrind --leak-check=full ./invalid_access
==65547== Memcheck, a memory error detector
==65547== Command: ./invalid_access
==65547==
Programa finalizado
==65547==
==65547== HEAP SUMMARY:
==65547==     in use at exit: 0 bytes in 0 blocks
==65547==   total heap usage: 3 allocs, 3 frees, 74,772 bytes allocated
==65547==
==65547== All heap blocks were freed -- no leaks are possible
==65547==
==65547== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Reflexión del ejercicio

Este ejercicio mostró que un programa puede acceder fuera de los límites de un arreglo sin fallar visiblemente. Aunque la ejecución normal mostró `Programa finalizado`, `valgrind` detectó que el programa estaba escribiendo en una dirección de memoria inválida.

La corrección consistió en ajustar la condición del ciclo para que solo se usaran índices válidos. Después de corregir el código, `valgrind` reportó cero errores.

## Preguntas de reflexión

### 1. ¿Qué es una pérdida de memoria?

Una pérdida de memoria ocurre cuando un programa reserva memoria dinámica, pero no la libera cuando ya no la necesita. Como resultado, esa memoria queda ocupada hasta que el programa termina.

### 2. ¿Por qué el programa puede terminar aparentemente bien aunque tenga una pérdida de memoria?

El programa puede terminar aparentemente bien porque una pérdida de memoria no siempre provoca un error visible de inmediato. En programas pequeños puede parecer que no ocurre nada grave, pero en programas grandes o de larga duración puede causar consumo excesivo de memoria.

### 3. ¿Qué significa liberar memoria dinámica?

Liberar memoria dinámica significa devolver al sistema la memoria que fue reservada durante la ejecución del programa. En C++, si se reserva memoria con `new[]`, debe liberarse con `delete[]`.

### 4. ¿Por qué se usa `delete[]` y no solo `delete`?

Se usa `delete[]` porque la memoria fue reservada como un arreglo mediante `new[]`. Usar `delete` en lugar de `delete[]` no corresponde con la forma en que se reservó la memoria.

### 5. ¿Qué tipo de problemas podrían aparecer en programas grandes si no se libera memoria?

En programas grandes podrían aparecer problemas como aumento progresivo del consumo de memoria, reducción del rendimiento, fallos inesperados o incluso la finalización del programa por falta de memoria disponible.

### 6. ¿Por qué el programa podría no fallar aunque acceda fuera del arreglo?

El programa podría no fallar porque el acceso fuera del arreglo puede caer en una zona de memoria cercana que no causa una interrupción inmediata. Sin embargo, sigue siendo un comportamiento incorrecto e indefinido.

### 7. ¿Qué significa escribir fuera de los límites de un arreglo?

Escribir fuera de los límites de un arreglo significa acceder a una posición que no pertenece al bloque de memoria reservado para ese arreglo. En este caso, el arreglo tenía posiciones válidas de `0` a `4`, pero el programa intentaba escribir en la posición `5`.

### 8. ¿Por qué este tipo de error es peligroso?

Es peligroso porque puede modificar memoria que pertenece a otros datos del programa. Esto puede causar resultados incorrectos, fallos difíciles de reproducir o vulnerabilidades de seguridad.

### 9. ¿Qué diferencia hay entre un error visible y un comportamiento indefinido?

Un error visible produce un fallo claro o un mensaje evidente durante la ejecución. Un comportamiento indefinido puede no mostrar ningún fallo inmediato, pero el programa deja de tener un comportamiento confiable. En este caso, el programa imprimía `Programa finalizado`, aunque internamente estaba escribiendo fuera del arreglo.