# Parte 7: análisis de hilos y condiciones de carrera

## Objetivo

Se analizó un programa multihilo que incrementa una variable global compartida desde dos hilos. El objetivo fue observar una condición de carrera, detectarla con herramientas de análisis y corregirla utilizando `std::mutex`.

## Código original con condición de carrera

```cpp
#include <iostream>
#include <thread>

int contador = 0;

void incrementar() {
    for (int i = 0; i < 100000; i++) {
        contador++;
    }
}

int main() {
    std::thread hilo1(incrementar);
    std::thread hilo2(incrementar);

    hilo1.join();
    hilo2.join();

    std::cout << "Contador final: " << contador << std::endl;

    return 0;
}
```

## Descripción del programa original

El programa define una variable global llamada `contador`. Luego crea dos hilos que ejecutan la misma función `incrementar`.

Cada hilo incrementa el contador varias veces. Como ambos hilos acceden y modifican la misma variable global al mismo tiempo, existe la posibilidad de que se produzca una condición de carrera.

El problema se encuentra en la instrucción:

```cpp
contador++;
```

Aunque parece una operación simple, internamente implica leer el valor actual, incrementarlo y volver a escribirlo. Si dos hilos realizan esta operación al mismo tiempo sin sincronización, uno de los incrementos puede perderse.

## Compilación del programa original

Se compiló el programa con soporte para hilos mediante el siguiente comando:

```bash
g++ -g -pthread -o race_condition codigo/08_race_condition.cpp
```

El comando no mostró errores de compilación.

## Ejecución del programa original

Se ejecutó el programa varias veces:

```bash
./race_condition
./race_condition
./race_condition
```

Se obtuvieron los siguientes resultados:

```bash
Contador final: 164517
Contador final: 200000
Contador final: 200000
```

## Resultado esperado

El resultado esperado era:

```bash
Contador final: 200000
```

Este valor corresponde a que los dos hilos completan todos los incrementos esperados sobre la variable compartida.

## Análisis del resultado

En una de las ejecuciones se obtuvo:

```bash
Contador final: 164517
```

Ese resultado demuestra que hubo incrementos perdidos. Esto ocurre porque ambos hilos acceden a `contador` sin ningún mecanismo de sincronización.

Aunque en otras ejecuciones se obtuvo `200000`, eso no significa que el programa sea correcto. Los errores de concurrencia pueden aparecer de forma intermitente, dependiendo del orden en que el sistema operativo ejecute los hilos.

## Compilación con ThreadSanitizer

Se compiló el programa original con ThreadSanitizer mediante el siguiente comando:

```bash
g++ -g -fsanitize=thread -pthread -o race_condition_tsan codigo/08_race_condition.cpp
```

Luego se ejecutó:

```bash
./race_condition_tsan
```

Se obtuvo la siguiente salida:

```bash
FATAL: ThreadSanitizer: unexpected memory mapping 0x5f89cf6ac000-0x5f89cf6ad000
```

## Observación sobre ThreadSanitizer

ThreadSanitizer no pudo completar el análisis en este ambiente, ya que produjo un error fatal relacionado con el mapeo de memoria. Por esta razón, no se obtuvo un reporte útil de ThreadSanitizer para este caso.

Sin embargo, el análisis se pudo continuar con Helgrind, que sí reportó la condición de carrera en la variable compartida `contador`.

## Análisis con Helgrind

Se ejecutó Helgrind con el siguiente comando:

```bash
valgrind --tool=helgrind ./race_condition
```

Helgrind reportó una posible condición de carrera:

```bash
==67928== Possible data race during read of size 4 at 0x10C154 by thread #3
==67928== Locks held: none
==67928==    at 0x10929A: incrementar() (08_race_condition.cpp:8)
```

También indicó que ese acceso entraba en conflicto con una escritura previa realizada por otro hilo:

```bash
==67928== This conflicts with a previous write of size 4 by thread #2
==67928== Locks held: none
==67928==    at 0x1092A3: incrementar() (08_race_condition.cpp:8)
```

Además, Helgrind identificó que la dirección correspondía a la variable global `contador`:

```bash
==67928==  Address 0x10c154 is 0 bytes inside data symbol "contador"
```

El resumen final fue:

```bash
==67928== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 1 from 1)
```

## Explicación del problema

El problema ocurrió porque los dos hilos modificaban la variable global `contador` al mismo tiempo, sin usar ningún mecanismo de protección.

La operación:

```cpp
contador++;
```

no es atómica. Esto significa que no se ejecuta como una sola acción indivisible. Internamente puede dividirse en varios pasos: leer el valor, incrementarlo y escribir el nuevo valor.

Si ambos hilos leen el mismo valor antes de que alguno escriba el resultado actualizado, uno de los incrementos se pierde. Por eso el contador final puede ser menor al esperado.

## Qué es una condición de carrera

Una condición de carrera ocurre cuando dos o más hilos acceden a un recurso compartido al mismo tiempo y al menos uno de ellos lo modifica, sin una sincronización adecuada.

En este programa, el recurso compartido era:

```cpp
int contador = 0;
```

Y la operación problemática era:

```cpp
contador++;
```

Como ambos hilos modificaban `contador` sin protección, el resultado dependía del orden de ejecución de los hilos.

## Código corregido

Se corrigió el programa usando `std::mutex` y `std::lock_guard`.

```cpp
#include <iostream>
#include <thread>
#include <mutex>

int contador = 0;
std::mutex mtx;

void incrementar() {
    for (int i = 0; i < 100000; i++) {
        std::lock_guard<std::mutex> lock(mtx);
        contador++;
    }
}

int main() {
    std::thread hilo1(incrementar);
    std::thread hilo2(incrementar);

    hilo1.join();
    hilo2.join();

    std::cout << "Contador final: " << contador << std::endl;

    return 0;
}
```

## Explicación de la corrección

Se agregó un `std::mutex` global:

```cpp
std::mutex mtx;
```

Luego, dentro del ciclo, se protegió la operación sobre `contador` usando:

```cpp
std::lock_guard<std::mutex> lock(mtx);
contador++;
```

Con esta corrección, solo un hilo puede ejecutar la sección protegida a la vez. Esto evita que ambos hilos lean y escriban `contador` simultáneamente.

`std::lock_guard` bloquea el mutex al crearse y lo libera automáticamente cuando termina su alcance. Esto ayuda a evitar errores por olvidar liberar el mutex manualmente.

## Compilación del programa corregido

Se compiló el programa corregido con el siguiente comando:

```bash
g++ -g -pthread -o race_condition_corregido codigo/09_race_condition_corregido.cpp
```

El comando no mostró errores.

## Ejecución del programa corregido

Se ejecutó el programa corregido varias veces:

```bash
./race_condition_corregido
./race_condition_corregido
./race_condition_corregido
```

Se obtuvo:

```bash
Contador final: 200000
Contador final: 200000
Contador final: 200000
```

Esto muestra que, después de usar el mutex, el resultado fue consistente.

## Análisis con Helgrind después de corregir

Se ejecutó Helgrind sobre el programa corregido:

```bash
valgrind --tool=helgrind ./race_condition_corregido
```

Se obtuvo la siguiente salida relevante:

```bash
Contador final: 200000
==68143== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 300005 from 8)
```

Helgrind no reportó errores, por lo que se verificó que la condición de carrera fue corregida.

## ThreadSanitizer después de corregir

También se compiló la versión corregida con ThreadSanitizer:

```bash
g++ -g -fsanitize=thread -pthread -o race_condition_corregido_tsan codigo/09_race_condition_corregido.cpp
```

Luego se ejecutó:

```bash
./race_condition_corregido_tsan
```

Se obtuvo:

```bash
FATAL: ThreadSanitizer: unexpected memory mapping 0x74c7bd672000-0x74c7bdb00000
```

Al igual que con el programa original, ThreadSanitizer no pudo ejecutarse correctamente en este ambiente. Por lo tanto, para la verificación de la corrección se tomó como referencia el resultado de Helgrind.

## Evidencia de terminal

```bash
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -pthread -o race_condition codigo/08_race_condition.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./race_condition
Contador final: 164517
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./race_condition
Contador final: 200000
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./race_condition
Contador final: 200000
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -fsanitize=thread -pthread -o race_condition_tsan codigo/08_race_condition.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./race_condition_tsan
FATAL: ThreadSanitizer: unexpected memory mapping 0x5f89cf6ac000-0x5f89cf6ad000
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ valgrind --tool=helgrind ./race_condition
==67928== Helgrind, a thread error detector
==67928== Command: ./race_condition
==67928==
==67928== Possible data race during read of size 4 at 0x10C154 by thread #3
==67928== Locks held: none
==67928==    at 0x10929A: incrementar() (08_race_condition.cpp:8)
==67928==
==67928== This conflicts with a previous write of size 4 by thread #2
==67928== Locks held: none
==67928==    at 0x1092A3: incrementar() (08_race_condition.cpp:8)
==67928==  Address 0x10c154 is 0 bytes inside data symbol "contador"
==67928==
Contador final: 200000
==67928== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 1 from 1)
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -pthread -o race_condition_corregido codigo/09_race_condition_corregido.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./race_condition_corregido
Contador final: 200000
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./race_condition_corregido
Contador final: 200000
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./race_condition_corregido
Contador final: 200000
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ valgrind --tool=helgrind ./race_condition_corregido
==68143== Helgrind, a thread error detector
==68143== Command: ./race_condition_corregido
==68143==
Contador final: 200000
==68143== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 300005 from 8)
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ g++ -g -fsanitize=thread -pthread -o race_condition_corregido_tsan codigo/09_race_condition_corregido.cpp
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-depuracion$ ./race_condition_corregido_tsan
FATAL: ThreadSanitizer: unexpected memory mapping 0x74c7bd672000-0x74c7bdb00000
```

## Reflexión del ejercicio

Este ejercicio mostró que los errores de concurrencia pueden ser difíciles de observar porque no siempre aparecen en todas las ejecuciones. En una ejecución el contador fue menor al esperado, mientras que en otras ejecuciones sí se obtuvo el resultado esperado.

Helgrind permitió confirmar que existía una condición de carrera en la variable global `contador`. La causa fue que ambos hilos leían y escribían la misma variable sin ninguna protección.

La corrección con `std::mutex` hizo que el acceso a `contador` estuviera sincronizado. Después de corregir el programa, las ejecuciones produjeron el resultado esperado y Helgrind reportó cero errores.

## Preguntas de reflexión

### 1. ¿Por qué `contador++` no es una operación segura entre varios hilos?

`contador++` no es segura entre varios hilos porque no es una operación atómica. Puede dividirse en leer el valor actual, incrementarlo y escribir el nuevo valor. Si dos hilos hacen esto al mismo tiempo, uno de los incrementos puede perderse.

### 2. ¿Qué significa que dos hilos accedan a la misma variable compartida?

Significa que ambos hilos usan la misma variable en memoria. Si al menos uno de ellos modifica esa variable y no existe sincronización, el resultado puede depender del orden en que se ejecuten los hilos.

### 3. ¿Qué problema resuelve `std::mutex`?

`std::mutex` resuelve el problema de acceso simultáneo a una sección crítica. Permite que solo un hilo a la vez ejecute el código protegido, evitando que varios hilos modifiquen la misma variable al mismo tiempo.

### 4. ¿Qué hace `std::lock_guard`?

`std::lock_guard` administra automáticamente el bloqueo y desbloqueo de un `std::mutex`. Al crearse, bloquea el mutex. Al salir de su alcance, lo libera automáticamente.

### 5. ¿Por qué los errores de concurrencia pueden ser difíciles de reproducir?

Son difíciles de reproducir porque dependen del orden de ejecución de los hilos, y ese orden puede cambiar entre ejecuciones. Por eso un programa con una condición de carrera puede fallar una vez y parecer correcto en otra ejecución.

### 6. ¿Cuál herramienta pareció más clara para analizar este caso: ThreadSanitizer o Helgrind?

En este ambiente, Helgrind fue la herramienta más útil porque sí produjo un reporte claro de la condición de carrera. ThreadSanitizer no pudo completar el análisis debido al error fatal de mapeo de memoria, por lo que no permitió diagnosticar el problema en esta ejecución.