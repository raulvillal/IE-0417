# Análisis de resultados
# Raúl Villalobos Vega C18555

## Laboratorio: Introducción práctica a programación concurrente y paralela en C++

## Parte 1: creación básica de hilos

### Resultados obtenidos

El programa fue compilado y ejecutado 5 veces para observar si el orden de impresión de los hilos se mantiene constante entre ejecuciones.

### Compilación



### Ejecuciones realizadas

```text
Hola desde el hilo 0
Hola desde el hilo 1
Hola desde el hilo 2
Hola desde el hilo 3
Hola desde el hilo 4
Todos los hilos finalizaron.
```

```text
Hola desde el hilo 0
Hola desde el hilo 2
Hola desde el hilo 1
Hola desde el hilo 3
Hola desde el hilo 4
Todos los hilos finalizaron.
```

```text
Hola desde el hilo 0
Hola desde el hilo 1
Hola desde el hilo 2
Hola desde el hilo 3
Hola desde el hilo 4
Todos los hilos finalizaron.
```

```text
Hola desde el hilo 0
Hola desde el hilo 1
Hola desde el hilo 2
Hola desde el hilo 3
Hola desde el hilo 4
Todos los hilos finalizaron.
```

```text
Hola desde el hilo 0
Hola desde el hilo 2
Hola desde el hilo 3
Hola desde el hilo 1
Hola desde el hilo 4
Todos los hilos finalizaron.
```

### Resumen de resultados

| Ejecución | Orden observado |
|---|---|
| 1 | 0, 1, 2, 3, 4 |
| 2 | 0, 2, 1, 3, 4 |
| 3 | 0, 1, 2, 3, 4 |
| 4 | 0, 1, 2, 3, 4 |
| 5 | 0, 2, 3, 1, 4 |


### Análisis

#### 1. ¿Los mensajes aparecen siempre en el mismo orden?

Al ejecutar el programa 5 veces, los mensajes no aparecieron en el mismo orden todas las veces.

#### 2. ¿Por qué podría cambiar el orden de impresión?

El orden puede cambiar porque la ejecución de los hilos depende del planificador del sistema operativo. Una vez creados, los hilos compiten por tiempo de CPU, y el sistema decide cuándo ejecuta cada uno. Por eso, un hilo creado después puede imprimir antes que otro creado previamente.

#### 3. ¿Qué función cumple `join()`?

La función `join()` hace que el hilo principal espere a que cada hilo termine su ejecución antes de continuar. En este caso, garantiza que todos los hilos hayan terminado antes de imprimir el mensaje final.

#### 4. ¿Qué podría pasar si no se llama a `join()`?

Si no se llama a `join()`, el programa principal podría terminar y mostrar el mensaje final antes de que los hilos hayan finalizado. Además, si un objeto std::thread todavía representa un hilo activo cuando se destruye, el programa puede terminar de forma abrupta.

---

## Parte 2: condición de carrera

### Resultados obtenidos

En esta parte, varios hilos incrementan una variable global compartida llamada `contador`. El programa usa 4 hilos, y cada hilo realiza 1 000 000 incrementos, por lo que el valor esperado es 4 000 000.

| Ejecución | Valor esperado | Valor obtenido |
|---|---:|---:|
| 1 | 4000000 | 1188014 |
| 2 | 4000000 | 1931196 |
| 3 | 4000000 | 1325174 |
| 4 | 4000000 | 1251327 |
| 5 | 4000000 | 1304417 |

### Análisis

#### 1. ¿El valor obtenido siempre coincide con el valor esperado?

No. En ninguna de las ejecuciones el valor obtenido coincidió con el valor esperado. Aunque el programa debería llegar a `4000000`, los resultados fueron menores y además variaron entre ejecuciones.

Esto muestra que el resultado no es determinista cuando varios hilos modifican una variable compartida sin sincronización.

#### 2. ¿Por qué se pierden incrementos?

Se pierden incrementos porque varios hilos pueden leer el mismo valor de `contador` al mismo tiempo. Luego cada uno calcula un nuevo valor y lo escribe de vuelta, pero algunas escrituras sobrescriben el resultado de otros hilos.

Por ejemplo, si dos hilos leen el mismo valor antes de que alguno escriba el resultado actualizado, ambos terminan guardando un incremento equivalente, aunque en realidad debieron haberse contado dos incrementos distintos.

#### 3. ¿La operación `contador++` es realmente una sola operación a nivel de CPU?

No. Aunque en C++ se escribe como una sola instrucción, `contador++` implica varias acciones internas: leer el valor actual de la variable, incrementarlo y escribirlo nuevamente en memoria.

Como esas acciones no ocurren de forma atómica, otro hilo puede intervenir entre una acción y otra. Por eso la operación puede producir resultados incorrectos cuando se ejecuta simultáneamente desde varios hilos.

#### 4. ¿Qué problema de concurrencia se está observando?

Se está observando una condición de carrera. El resultado final depende del orden exacto en que los hilos leen, modifican y escriben la variable compartida `contador`.

Como ese orden no está controlado por el programa, el valor obtenido cambia entre ejecuciones y no coincide con el valor esperado.

## Parte 3: corrección usando mutex

### Resultados obtenidos

En esta parte se protegió el incremento de `contador` usando `std::mutex` y `std::lock_guard`.

| Ejecución | Valor esperado | Valor obtenido |
|---|---:|---:|
| 1 | 4000000 | 4000000 |
| 2 | 4000000 | 4000000 |
| 3 | 4000000 | 4000000 |
| 4 | 4000000 | 4000000 |
| 5 | 4000000 | 4000000 |

### Análisis

#### 1. ¿Qué cambió con respecto al programa anterior?

La diferencia principal es que ahora el acceso a la variable compartida `contador` está protegido por un `std::mutex`. Esto evita que varios hilos modifiquen la variable al mismo tiempo y por ende se obtiene el resultado esperado.

#### 2. ¿Qué hace `std::mutex`?

`std::mutex` permite proteger una sección crítica del programa. Cuando un hilo bloquea el mutex, los demás hilos deben esperar hasta que sea liberado antes de poder entrar a esa sección.

#### 3. ¿Qué hace `std::lock_guard`?

`std::lock_guard` bloquea el mutex al crearse y lo libera automáticamente cuando termina su alcance. Esto ayuda a evitar errores como olvidar llamar manualmente a `unlock()`.

#### 4. ¿Por qué ahora el resultado sí debería ser correcto?

Porque el incremento de `contador` queda protegido. Solo un hilo puede ejecutar la operación `contador++` a la vez, evitando que se pierdan actualizaciones.

#### 5. ¿Qué desventaja podría tener proteger cada incremento individual con un mutex?

La principal desventaja es el costo de sincronización. Bloquear y desbloquear el mutex en cada incremento puede hacer que el programa sea más lento, especialmente si la operación protegida es muy pequeña y se repite muchas veces.

---

## Parte 4: mini benchmark secuencial vs. paralelo

### Resultados obtenidos

Se comparó el tiempo de ejecución de una suma secuencial contra una suma paralela usando 4 hilos. En ambos casos, el resultado de la suma fue el mismo: `100000000`.

| Ejecución | Tiempo secuencial | Tiempo paralelo | ¿Cuál fue más rápido? |
|---|---:|---:|---|
| 1 | 27 ms | 11 ms | Paralelo |
| 2 | 36 ms | 10 ms | Paralelo |
| 3 | 27 ms | 9 ms | Paralelo |
| 4 | 28 ms | 10 ms | Paralelo |

### Análisis

#### 1. ¿El resultado secuencial y el paralelo son iguales?

Sí. En todas las ejecuciones, tanto la versión secuencial como la versión paralela produjeron el mismo resultado: `100000000`. Esto indica que ambas versiones realizaron correctamente la suma de todos los elementos del vector.

#### 2. ¿La versión paralela siempre fue más rápida?

Sí, en las ejecuciones realizadas la versión paralela fue más rápida que la versión secuencial. Esto se observa porque los tiempos paralelos fueron menores en todas las pruebas.

Sin embargo, esto no significa que una versión paralela siempre será más rápida en cualquier caso. En este laboratorio funcionó mejor porque el vector es suficientemente grande y el trabajo pudo dividirse entre varios hilos.

#### 3. ¿Por qué dividir el vector en bloques permite paralelizar el trabajo?

Dividir el vector en bloques permite que cada hilo trabaje sobre una sección distinta del vector. Como la suma de cada bloque no depende directamente de los otros bloques, los hilos pueden calcular sumas parciales al mismo tiempo.

Luego, el programa principal junta esas sumas parciales para obtener el resultado total.

#### 4. ¿Qué costos adicionales tiene la versión paralela?

La versión paralela tiene costos adicionales como la creación de hilos, la distribución del trabajo, la espera con `join()` y la combinación final de los resultados parciales.

Aun así, en este caso esos costos fueron menores que el beneficio obtenido al dividir el trabajo entre varios hilos.

#### 5. ¿Qué podría pasar si el vector fuera muy pequeño?

Si el vector fuera muy pequeño, la versión paralela podría no ser más rápida. Esto se debe a que el costo de crear y coordinar hilos podría ser mayor que el tiempo ahorrado al dividir la suma.

En ese caso, una versión secuencial podría ser igual o incluso más eficiente.

---

## Parte 5: cantidad de hilos vs. rendimiento

### Resultados obtenidos

Se ejecutó la suma paralela usando diferentes cantidades de hilos. En todos los casos, el resultado obtenido fue `100000000`, por lo que la suma se realizó correctamente.

También se consultó la cantidad de procesadores lógicos disponibles usando:

```bash
nproc
```

El resultado fue:

```text
16
```

### Primera ejecución

| Cantidad de hilos | Resultado | Tiempo obtenido |
|---:|---:|---:|
| 1 | 100000000 | 30 ms |
| 2 | 100000000 | 15 ms |
| 4 | 100000000 | 10 ms |
| 8 | 100000000 | 8 ms |
| 16 | 100000000 | 10 ms |

### Segunda ejecución

| Cantidad de hilos | Resultado | Tiempo obtenido |
|---:|---:|---:|
| 1 | 100000000 | 76 ms |
| 2 | 100000000 | 33 ms |
| 4 | 100000000 | 27 ms |
| 8 | 100000000 | 10 ms |
| 16 | 100000000 | 8 ms |

### Análisis

#### 1. ¿Cuál cantidad de hilos produjo el mejor tiempo?

En la primera ejecución, el mejor tiempo se obtuvo usando **8 hilos**, con un tiempo de `8 ms`.

En la segunda ejecución, el mejor tiempo se obtuvo usando **16 hilos**, también con un tiempo de `8 ms`.

Esto muestra que el mejor resultado puede variar entre ejecuciones, incluso usando el mismo programa y la misma computadora.

#### 2. ¿El tiempo mejoró siempre al aumentar los hilos?

No. En la primera ejecución, el tiempo mejoró hasta llegar a 8 hilos, pero al usar 16 hilos el tiempo aumentó de `8 ms` a `10 ms`.

En la segunda ejecución, sí se obtuvo el mejor tiempo con 16 hilos. Sin embargo, al comparar ambas ejecuciones, se observa que usar más hilos no garantiza siempre el mejor rendimiento.

#### 3. ¿Cuántos núcleos tiene la computadora donde se ejecutó el programa?

El comando `nproc` reportó `16` procesadores lógicos disponibles.

#### 4. ¿Qué ocurre cuando se usan más hilos que núcleos disponibles?

Cuando se usan más hilos que núcleos disponibles, no todos los hilos pueden ejecutarse realmente al mismo tiempo. El sistema operativo debe repartir el tiempo de CPU entre ellos.

En este caso, como el sistema reporta 16 procesadores lógicos, usar 16 hilos no necesariamente excede la cantidad de procesadores lógicos disponibles. Aun así, eso no garantiza que 16 hilos siempre produzcan el mejor tiempo, porque también influyen otros factores como la carga del sistema, el acceso a memoria y la sobrecarga de administrar hilos.

#### 5. ¿Qué relación tiene esto con el `context switching`?

El `context switching` ocurre cuando el sistema operativo pausa un hilo y cambia a otro. Este proceso tiene un costo, porque se debe guardar el estado del hilo anterior y restaurar el estado del nuevo.

Si hay muchos hilos compitiendo por recursos, puede aumentar la sobrecarga de administración. Esto puede afectar el rendimiento, especialmente cuando la mejora obtenida por paralelizar ya no compensa el costo de manejar más hilos.

#### 6. ¿Por qué la versión con 16 hilos podría no ser la mejor?

La versión con 16 hilos podría no ser la mejor porque agregar más hilos también agrega sobrecarga. Además, la suma de un vector grande depende bastante del acceso a memoria, no solo de la cantidad de hilos.

En la primera ejecución, 16 hilos no fue la mejor opción, ya que fue más lenta que 8 hilos. En la segunda ejecución, 16 hilos sí produjo el mejor tiempo. Esto confirma que el rendimiento paralelo puede variar entre ejecuciones y que no basta con asumir que más hilos siempre será mejor.

### Conclusión breve

Los resultados muestran que aumentar la cantidad de hilos puede mejorar el rendimiento, pero solo hasta cierto punto y no de manera completamente predecible. En una ejecución, 8 hilos produjo el mejor tiempo; en otra, 16 hilos fue la mejor opción. Esto demuestra que el rendimiento depende tanto de la cantidad de hilos como de factores del sistema, como la planificación del sistema operativo, la carga de la computadora, el acceso a memoria y la sobrecarga asociada al manejo de hilos.

---

## Parte 6: ejemplo simple de deadlock

### Resultados observados

Al ejecutar el programa, se observó que los dos hilos intentan tomar recursos en orden distinto. El programa no terminó normalmente y tuvo que detenerse manualmente con `Ctrl + C`.

Primera ejecución:

```text
Hilo A intentando tomar recurso 1...Hilo B intentando tomar recurso 2...

Hilo B intentando tomar recurso 1...
Hilo A intentando tomar recurso 2...
^C
```

Segunda ejecución:

```text
Hilo A intentando tomar recurso 1...Hilo B intentando tomar recurso 2...

Hilo A intentando tomar recurso 2...
Hilo B intentando tomar recurso 1...
^C
```

En ambas ejecuciones se observa que el programa queda bloqueado después de que cada hilo intenta tomar el segundo recurso.

### Análisis

#### 1. ¿El programa termina normalmente?

No. El programa no termina normalmente. En ambas ejecuciones quedó bloqueado y fue necesario detenerlo manualmente con `Ctrl + C`.

Esto confirma que ocurrió un deadlock.

#### 2. ¿Qué recurso tomó primero el hilo A?

El hilo A tomó primero `recurso1`.

Esto se observa en el mensaje:

```text
Hilo A intentando tomar recurso 1...
```

#### 3. ¿Qué recurso tomó primero el hilo B?

El hilo B tomó primero `recurso2`.

Esto se observa en el mensaje:

```text
Hilo B intentando tomar recurso 2...
```

#### 4. ¿Por qué ninguno de los dos hilos puede continuar?

Ninguno puede continuar porque cada hilo conserva un recurso que el otro necesita.

El hilo A tomó `recurso1` y luego intenta tomar `recurso2`. Al mismo tiempo, el hilo B tomó `recurso2` y luego intenta tomar `recurso1`.

Entonces, el hilo A espera a que el hilo B libere `recurso2`, mientras que el hilo B espera a que el hilo A libere `recurso1`. Como ninguno de los dos puede avanzar hasta obtener el segundo recurso, ambos quedan bloqueados indefinidamente.

#### 5. ¿Qué significa espera circular?

La espera circular ocurre cuando un conjunto de hilos queda atrapado en una cadena de dependencias. Cada hilo espera por un recurso que está siendo usado por otro hilo del mismo conjunto.

En este caso, el hilo A espera un recurso que tiene el hilo B, y el hilo B espera un recurso que tiene el hilo A.

#### 6. ¿Cómo se podría evitar este problema?

Una forma de evitar este problema es hacer que todos los hilos tomen los recursos en el mismo orden. Por ejemplo, ambos hilos podrían tomar primero `recurso1` y luego `recurso2`.

Otra forma más segura es usar `std::scoped_lock`, que permite bloquear varios mutex al mismo tiempo usando un mecanismo diseñado para evitar deadlocks.

### Versión corregida usando `std::scoped_lock`

Después de ejecutar la versión original y observar el deadlock, se realizó una segunda versión corregida usando `std::scoped_lock`.

Esta versión se compiló con el siguiente comando:

```bash
g++ -std=c++17 -Wall -Wextra -pthread parte6_deadlock_corregido.cpp -o parte6_corregido
```

Luego se ejecutó con:

```bash
./parte6_corregido
```

Salida observada:

```text
raulpro@PCdeRaul:~/Diseño_Software/IE-0417/laboratorio-concurrencia/src$ ./parte6_corregido
Hilo A obtuvo ambos recursos de forma segura.
Hilo B obtuvo ambos recursos de forma segura.
```

A diferencia del programa anterior, esta versión sí termina normalmente. Ambos hilos logran obtener los recursos de forma segura y luego finalizan su ejecución.

#### 7. Explique por qué `std::scoped_lock` ayuda a evitar este deadlock.

`std::scoped_lock` ayuda a evitar el deadlock porque permite bloquear varios mutex de forma conjunta y segura. En lugar de que un hilo tome primero un recurso y luego intente tomar otro manualmente, `std::scoped_lock` administra la adquisición de ambos mutex.

En la versión original, el problema ocurría porque el hilo A tomaba primero `recurso1` y luego esperaba `recurso2`, mientras que el hilo B tomaba primero `recurso2` y luego esperaba `recurso1`. Esto producía una espera circular.

Con `std::scoped_lock`, ambos mutex se bloquean usando un mecanismo diseñado para evitar ese tipo de bloqueo entre hilos. Además, los mutex se liberan automáticamente cuando el objeto `lock` sale de su alcance, lo cual evita errores asociados a llamar manualmente a `unlock()`.

Por eso, la versión corregida elimina la espera circular y permite que el programa termine correctamente.

---

# Parte 7: reflexión final

## 1. ¿Cuál fue la diferencia más clara que observó entre ejecución secuencial y ejecución con hilos?

La diferencia más clara fue que en la ejecución secuencial el programa sigue un único flujo de instrucciones, mientras que en la ejecución con hilos varias tareas pueden avanzar de forma concurrente.

En la parte 4 se observó que la versión paralela de la suma fue más rápida que la versión secuencial en las ejecuciones realizadas. Esto muestra que, cuando el problema puede dividirse en partes independientes y el tamaño del trabajo es suficientemente grande, usar hilos puede mejorar el tiempo de ejecución.

Sin embargo, también se observó que la ejecución con hilos introduce nuevos problemas, como el orden no garantizado de ejecución, las condiciones de carrera y la necesidad de sincronización.

## 2. ¿Qué es una condición de carrera?

Una condición de carrera ocurre cuando dos o más hilos acceden al mismo recurso compartido al mismo tiempo, y al menos uno de ellos modifica ese recurso.

El problema es que el resultado final depende del orden exacto en que los hilos ejecutan sus instrucciones. Como ese orden no está completamente controlado por el programa, el resultado puede variar entre ejecuciones.

En la parte 2, la condición de carrera se observó cuando varios hilos incrementaron la variable global `contador` sin ningún mecanismo de protección.

## 3. ¿Por qué `contador++` puede fallar cuando muchos hilos lo ejecutan al mismo tiempo?

`contador++` puede fallar porque no es una operación atómica. Aunque en el código parece una sola instrucción, internamente implica varios pasos: leer el valor actual de `contador`, incrementarlo y escribir el nuevo valor en memoria.

Si varios hilos hacen esos pasos al mismo tiempo, pueden leer el mismo valor antes de que alguno escriba el resultado actualizado. Como consecuencia, algunos incrementos se pierden.

Por eso, en la parte 2 el valor obtenido fue mucho menor que el valor esperado de `4000000`.

## 4. ¿Qué problema resuelve un mutex?

Un mutex resuelve el problema de acceso simultáneo a una sección crítica. Permite que solo un hilo a la vez pueda entrar a una parte del código donde se usa un recurso compartido.

En la parte 3, el mutex protegió el incremento de `contador`, evitando que varios hilos modificaran la variable al mismo tiempo. Gracias a eso, el resultado esperado y el resultado obtenido coincidieron.

## 5. ¿Qué ventaja tiene `std::lock_guard` sobre llamar manualmente a `lock()` y `unlock()`?

La ventaja principal de `std::lock_guard` es que administra el mutex automáticamente. Cuando se crea el `lock_guard`, bloquea el mutex; cuando termina su alcance, lo libera.

Esto hace que el código sea más seguro, porque reduce el riesgo de olvidar llamar a `unlock()`. También ayuda en casos donde una función termina antes de lo esperado, ya que el desbloqueo ocurre automáticamente al salir del bloque.

## 6. ¿Por qué más hilos no siempre significan mejor rendimiento?

Más hilos no siempre significan mejor rendimiento porque los hilos también tienen costos. Crear hilos, planificarlos, esperar su finalización y coordinar sus resultados consume tiempo.

En la parte 5 se observó que aumentar la cantidad de hilos mejoró el rendimiento hasta cierto punto, pero no de forma perfectamente constante. En una ejecución, 8 hilos produjeron el mejor tiempo; en otra, 16 hilos fueron mejores.

Esto muestra que el rendimiento depende de varios factores, como la cantidad de procesadores lógicos disponibles, la carga del sistema, el acceso a memoria y el costo de administrar los hilos.

## 7. ¿Qué es un deadlock?

Un deadlock es una situación en la que dos o más hilos quedan bloqueados indefinidamente porque cada uno espera un recurso que otro hilo posee.

En la parte 6, el hilo A tomó primero `recurso1` y luego intentó tomar `recurso2`. Al mismo tiempo, el hilo B tomó primero `recurso2` y luego intentó tomar `recurso1`.

Como cada hilo esperaba el recurso que tenía el otro, ninguno pudo continuar y el programa tuvo que detenerse manualmente con `Ctrl + C`.

## 8. ¿Qué buenas prácticas aplicaría al programar con hilos?

Al programar con hilos aplicaría varias buenas prácticas. Primero, identificar claramente cuáles recursos son compartidos entre hilos. Segundo, proteger las secciones críticas usando mecanismos como `std::mutex`, `std::lock_guard` o `std::scoped_lock`.

También evitaría mantener bloqueos durante más tiempo del necesario, porque eso puede reducir el rendimiento. Además, si se necesitan varios mutex, procuraría adquirirlos siempre en el mismo orden o usar `std::scoped_lock` para reducir el riesgo de deadlocks.

Finalmente, no asumiría que usar más hilos siempre mejora el rendimiento. Es necesario medir los tiempos reales del programa.

## 9. ¿En qué tipo de programas reales podría ser útil la programación concurrente?

La programación concurrente puede ser útil en programas que deben atender varias tareas al mismo tiempo. Por ejemplo, servidores web, aplicaciones con interfaz gráfica, videojuegos, sistemas de comunicación, programas que manejan múltiples conexiones de red o aplicaciones que deben seguir respondiendo mientras realizan operaciones de entrada y salida.

En estos casos, la concurrencia ayuda a que el programa no quede detenido esperando una sola tarea.

## 10. ¿En qué tipo de programas reales podría ser útil la programación paralela?

La programación paralela puede ser útil en programas donde un trabajo grande puede dividirse en partes independientes. Por ejemplo, simulaciones físicas, procesamiento de imágenes, análisis de grandes volúmenes de datos, entrenamiento de modelos de inteligencia artificial, renderizado, cálculo científico y procesamiento de señales.

En estos casos, dividir el trabajo entre varios hilos o núcleos puede reducir el tiempo total de ejecución.