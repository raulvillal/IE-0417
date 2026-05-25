# Parte 8: mini reto y reflexión final

## Mini reto de depuración

## Objetivo

Se aplicaron varias herramientas de depuración para analizar un programa con errores de memoria y errores lógicos. Se utilizaron ejecución normal, `valgrind`, AddressSanitizer y `gdb` para identificar los problemas y verificar las correcciones.

## Código original

```cpp
#include <iostream>

int obtener_mayor(int* datos, int tamano) {
    int mayor = 0;

    for (int i = 0; i <= tamano; i++) {
        if (datos[i] > mayor) {
            mayor = datos[i];
        }
    }

    return mayor;
}

double calcular_promedio(int* datos, int tamano) {
    int suma = 0;

    for (int i = 0; i < tamano; i++) {
        suma += datos[i];
    }

    return suma;
}

int main() {
    int tamano = 5;
    int* datos = new int[tamano];

    datos[0] = -10;
    datos[1] = -20;
    datos[2] = -5;
    datos[3] = -30;
    datos[4] = -15;

    int mayor = obtener_mayor(datos, tamano);
    double promedio = calcular_promedio(datos, tamano);

    std::cout << "Mayor: " << mayor << std::endl;
    std::cout << "Promedio: " << promedio << std::endl;

    return 0;
}
```

## Resultado inicial del programa

Se compiló el programa original con el siguiente comando:

```bash
g++ -g -o reto codigo/10_reto.cpp
```

Luego se ejecutó:

```bash
./reto
```

Se obtuvo la siguiente salida:

```bash
Mayor: 0
Promedio: -80
```

El resultado era incorrecto. El mayor no debía ser `0`, porque todos los valores del arreglo eran negativos y el mayor real era `-5`. Además, el promedio no debía ser `-80`, porque ese valor correspondía a la suma total, no al promedio.

## Análisis con valgrind

Se ejecutó el programa con `valgrind`:

```bash
valgrind --leak-check=full ./reto
```

Se obtuvo un error de lectura inválida:

```bash
==70142== Invalid read of size 4
==70142==    at 0x10921C: obtener_mayor(int*, int) (10_reto.cpp:7)
==70142==    by 0x10932C: main (10_reto.cpp:35)
==70142==  Address 0x4e29094 is 0 bytes after a block of size 20 alloc'd
```

Además, `valgrind` reportó una pérdida de memoria:

```bash
==70142== HEAP SUMMARY:
==70142==     in use at exit: 20 bytes in 1 blocks
==70142==   total heap usage: 3 allocs, 2 frees, 74,772 bytes allocated
==70142==
==70142== 20 bytes in 1 blocks are definitely lost in loss record 1 of 1
```

El resumen final indicó:

```bash
==70142== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

## Errores encontrados con valgrind

`valgrind` permitió identificar dos problemas:

1. Se estaba leyendo fuera de los límites del arreglo.
2. La memoria dinámica reservada con `new[]` no estaba siendo liberada.

El acceso fuera de límites se debía a esta condición:

```cpp
for (int i = 0; i <= tamano; i++)
```

Como el arreglo tenía cinco elementos, los índices válidos iban de `0` a `4`. Sin embargo, el ciclo permitía que `i` llegara a `5`, lo cual provocaba una lectura inválida.

La pérdida de memoria se debía a que el programa reservaba memoria con:

```cpp
int* datos = new int[tamano];
```

pero no ejecutaba:

```cpp
delete[] datos;
```

antes de terminar.

## Análisis con AddressSanitizer

Se compiló el programa con AddressSanitizer:

```bash
g++ -g -fsanitize=address -o reto_asan codigo/10_reto.cpp
```

Luego se ejecutó:

```bash
./reto_asan
```

AddressSanitizer reportó el siguiente error:

```bash
==70204==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x503000000054
READ of size 4 at 0x503000000054 thread T0
    #0 0x571388d7333a in obtener_mayor(int*, int) codigo/10_reto.cpp:7
    #1 0x571388d735db in main codigo/10_reto.cpp:35
```

El resumen indicó:

```bash
SUMMARY: AddressSanitizer: heap-buffer-overflow codigo/10_reto.cpp:7 in obtener_mayor(int*, int)
```

## Error encontrado con AddressSanitizer

AddressSanitizer confirmó que había un `heap-buffer-overflow`. Esto significa que el programa intentó leer memoria fuera del bloque reservado dinámicamente para el arreglo.

El error se encontraba en la función `obtener_mayor`, específicamente en el acceso a `datos[i]` cuando el ciclo permitía que `i` tomara el valor `tamano`.

## Análisis con gdb

Se abrió el programa con `gdb`:

```bash
gdb ./reto
```

Dentro de `gdb`, se colocó un breakpoint en `main`:

```gdb
break main
```

Luego se ejecutó el programa:

```gdb
run
```

Después se colocó un breakpoint en la función `obtener_mayor`:

```gdb
break obtener_mayor
```

Se continuó la ejecución:

```gdb
continue
```

El programa se detuvo en la función `obtener_mayor`:

```gdb
Breakpoint 2, obtener_mayor (datos=0x55555556b2b0, tamano=5) at codigo/10_reto.cpp:4
4           int mayor = 0;
```

Se inspeccionó el valor de `tamano`:

```gdb
print tamano
```

Se obtuvo:

```gdb
$1 = 5
```

Luego se observó la condición incorrecta del ciclo:

```gdb
6           for (int i = 0; i <= tamano; i++)
```

También se intentó inspeccionar `datos[i]` cuando `i` tenía un valor no válido en ese punto de la depuración:

```gdb
print datos[i]
Cannot access memory at address 0x55555558b2ac
```

Finalmente, se revisó la pila de llamadas:

```gdb
backtrace
```

Se obtuvo:

```gdb
#0  obtener_mayor (datos=0x55555556b2b0, tamano=5) at codigo/10_reto.cpp:6
#1  0x000055555555532d in main () at codigo/10_reto.cpp:35
```

## Errores encontrados

Se encontraron cuatro errores principales:

### 1. Error de memoria en el ciclo de `obtener_mayor`

El ciclo original era:

```cpp
for (int i = 0; i <= tamano; i++)
```

Esto era incorrecto porque permitía acceder a `datos[tamano]`, una posición fuera del arreglo.

La corrección fue:

```cpp
for (int i = 1; i < tamano; i++)
```

### 2. Error lógico en el cálculo del mayor

La variable `mayor` se inicializaba en `0`:

```cpp
int mayor = 0;
```

Esto era incorrecto para un arreglo donde todos los valores eran negativos. Como ningún número negativo es mayor que `0`, la función devolvía incorrectamente `0`.

La corrección fue inicializar `mayor` con el primer elemento del arreglo:

```cpp
int mayor = datos[0];
```

De esta forma, el algoritmo funciona aunque todos los valores sean negativos.

### 3. Error lógico en el cálculo del promedio

La función `calcular_promedio` devolvía solamente la suma:

```cpp
return suma;
```

Esto era incorrecto porque el promedio se obtiene dividiendo la suma entre la cantidad de elementos.

La corrección fue:

```cpp
return suma / tamano;
```

### 4. Pérdida de memoria

El programa reservaba memoria dinámica con:

```cpp
int* datos = new int[tamano];
```

pero no la liberaba.

La corrección fue agregar:

```cpp
delete[] datos;
```

antes de finalizar `main`.

## Código corregido

```cpp
#include <iostream>

int obtener_mayor(int* datos, int tamano) {
    int mayor = datos[0];

    for (int i = 1; i < tamano; i++) {
        if (datos[i] > mayor) {
            mayor = datos[i];
        }
    }

    return mayor;
}

double calcular_promedio(int* datos, int tamano) {
    int suma = 0;

    for (int i = 0; i < tamano; i++) {
        suma += datos[i];
    }

    return static_cast<double>(suma) / tamano;
}

int main() {
    int tamano = 5;
    int* datos = new int[tamano];

    datos[0] = -10;
    datos[1] = -20;
    datos[2] = -5;
    datos[3] = -30;
    datos[4] = -15;

    int mayor = obtener_mayor(datos, tamano);
    double promedio = calcular_promedio(datos, tamano);

    std::cout << "Mayor: " << mayor << std::endl;
    std::cout << "Promedio: " << promedio << std::endl;

    delete[] datos;

    return 0;
}
```

## Resultado final corregido

Después de aplicar la corrección completa, se ejecutó el programa:

```bash
./reto
```

Se obtuvo la siguiente salida:

```bash
Mayor: -5
Promedio: -16
```

Este resultado es correcto porque el mayor valor del arreglo es `-5` y el promedio de los valores es `-16`.

## Herramienta más útil

La herramienta más útil para este caso fue AddressSanitizer para detectar rápidamente el acceso fuera de límites, porque reportó directamente el `heap-buffer-overflow` y señaló la función donde ocurría el problema.

Sin embargo, `valgrind` también fue muy útil porque detectó tanto el acceso inválido como la pérdida de memoria. `gdb` ayudó a observar el flujo del programa y confirmar que el problema estaba dentro de `obtener_mayor`.

## Reflexión del mini reto

Este ejercicio mostró que un programa puede tener varios tipos de errores al mismo tiempo. Algunos eran errores de memoria, como el acceso fuera de límites y la pérdida de memoria. Otros eran errores lógicos, como inicializar el mayor en `0` y devolver la suma en lugar del promedio.

También se observó que corregir solo los errores de memoria no garantiza que el resultado lógico sea correcto. Por ejemplo, el programa podía dejar de reportar errores en `valgrind`, pero aún devolver `Mayor: 0` si la inicialización de `mayor` seguía siendo incorrecta.

Por eso, la depuración debe combinar herramientas automáticas con revisión lógica del resultado esperado.

## Reflexión final

### 1. ¿Qué entiende ahora por depuración?

Ahora entiendo la depuración como un proceso ordenado para encontrar, analizar y corregir errores en un programa. No consiste únicamente en cambiar código hasta que funcione, sino en observar el problema, reproducirlo, usar herramientas adecuadas y verificar que la corrección realmente solucione la causa del error.

### 2. ¿Por qué no basta con que un programa compile?

No basta con que un programa compile porque la compilación solo indica que el código cumple con las reglas sintácticas del lenguaje. Un programa puede compilar correctamente y aun así producir resultados incorrectos, fallar durante la ejecución, tener pérdidas de memoria o presentar errores de concurrencia.

### 3. ¿Cuál fue la diferencia entre un error de sintaxis y un error lógico?

La diferencia es que un error de sintaxis impide que el programa compile, mientras que un error lógico permite que el programa compile y se ejecute, pero produce un resultado incorrecto. El error de sintaxis fue señalado por el compilador, mientras que el error lógico tuvo que identificarse comparando el resultado obtenido con el resultado esperado.

### 4. ¿Qué ventaja tiene usar `gdb`?

La ventaja de usar `gdb` es que permite observar el programa mientras se ejecuta. Con esta herramienta puedo detener la ejecución en puntos específicos, avanzar línea por línea, inspeccionar variables y revisar la pila de llamadas para entender mejor dónde se produce un error.

### 5. ¿Qué ventaja tiene usar `valgrind`?

La ventaja de usar `valgrind` es que permite detectar problemas de memoria que no siempre se observan durante una ejecución normal. Por ejemplo, ayuda a encontrar pérdidas de memoria, accesos inválidos y lecturas o escrituras fuera de los límites de un arreglo.

### 6. ¿Qué ventaja tiene usar AddressSanitizer?

La ventaja de usar AddressSanitizer es que permite detectar errores de memoria durante la ejecución del programa compilado con sanitización. En este laboratorio fue útil porque mostró errores como `heap-use-after-free` y `heap-buffer-overflow`, indicando la línea donde ocurrió el problema.

### 7. ¿Qué aprendió sobre errores de memoria?

Aprendí que los errores de memoria pueden existir aunque el programa parezca funcionar correctamente. Un programa puede imprimir una salida esperada o finalizar sin fallar, pero aun así estar accediendo a memoria inválida o dejando memoria sin liberar.

### 8. ¿Qué aprendió sobre errores de concurrencia?

Aprendí que los errores de concurrencia pueden ser difíciles de detectar porque no siempre aparecen en todas las ejecuciones. Una condición de carrera puede producir un resultado incorrecto en una ejecución y parecer funcionar bien en otra, dependiendo del orden en que se ejecuten los hilos.

### 9. ¿Cuál fue el error más fácil de encontrar?

El error más fácil de encontrar fue el error de sintaxis, porque el compilador indicó directamente que faltaba un punto y coma antes de `return`.

### 10. ¿Cuál fue el error más difícil de entender?

El error más difícil de entender fue la condición de carrera, porque el programa podía producir resultados distintos en diferentes ejecuciones. Esto hizo que el error fuera menos evidente que los errores de sintaxis o de memoria.

### 11. ¿Qué herramienta usaría primero si un programa produce un resultado incorrecto?

Si un programa produce un resultado incorrecto, primero revisaría la ejecución normal y compararía el resultado obtenido con el resultado esperado. Luego usaría `gdb` para inspeccionar variables y seguir el flujo del programa paso a paso.

### 12. ¿Qué herramienta usaría primero si un programa falla con segmentation fault?

Si un programa falla con `segmentation fault`, usaría primero `gdb` para identificar en qué línea ocurre el fallo. También podría usar AddressSanitizer si sospecho que el problema está relacionado con un acceso inválido a memoria.

### 13. ¿Qué herramienta usaría primero si sospecha una pérdida de memoria?

Si sospecho una pérdida de memoria, usaría primero `valgrind`, porque permite identificar memoria reservada que no fue liberada correctamente.

### 14. ¿Qué herramienta usaría primero si sospecha un problema con hilos?

Si sospecho un problema con hilos, usaría primero Helgrind o ThreadSanitizer. En este laboratorio, Helgrind fue más útil porque sí logró reportar la condición de carrera, mientras que ThreadSanitizer no pudo ejecutarse correctamente en el ambiente utilizado.

### 15. ¿Cómo aplicaría estas herramientas en proyectos futuros?

Aplicaría estas herramientas de forma ordenada según el tipo de problema. Si el programa produce un resultado incorrecto, usaría pruebas y `gdb`; si sospecho errores de memoria, usaría `valgrind` o AddressSanitizer; y si sospecho problemas de hilos, usaría Helgrind o ThreadSanitizer. Esto me permitiría corregir errores con mayor claridad y no solamente cambiar código sin entender la causa del problema.