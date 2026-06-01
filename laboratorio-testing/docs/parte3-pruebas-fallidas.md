# Parte 5: pruebas fallidas y corrección de errores

## Objetivo de la parte

En esta quinta parte se trabajó con una prueba fallida provocada de forma intencional.

El objetivo fue observar cómo Google Test permite detectar errores en el código, identificar qué prueba falló, revisar el resultado esperado y el resultado obtenido, corregir la implementación y comprobar nuevamente que todas las pruebas pasaran correctamente.

---

## ¿Qué se hizo?

Se modificó temporalmente la función `is_even()` en el archivo `src/calculator.cpp` para introducir un error intencional.

La función originalmente debía verificar si un número era par. Sin embargo, para esta actividad se cambió la condición de forma incorrecta, con el fin de observar cómo reaccionaban las pruebas unitarias ante un error en la implementación.

---

## Archivo modificado

El archivo modificado fue:

```bash
src/calculator.cpp
```

La función `is_even()` fue cambiada temporalmente a la siguiente versión incorrecta:

```cpp
bool is_even(int number) {
    return number % 2 == 1;
}
```

Esta implementación es incorrecta porque retorna `true` cuando el residuo de dividir el número entre 2 es igual a 1. Es decir, identifica como verdaderos los números impares, aunque la función debería retornar `true` para los números pares.

---

## Comandos ejecutados

Desde la carpeta `build`, se recompiló el proyecto con el comando:

```bash
make
```

Luego se ejecutaron las pruebas unitarias con:

```bash
./run_tests
```

---

## Resultado de la compilación

La compilación finalizó correctamente y se generó el ejecutable de pruebas `run_tests`.

Esto indica que el error introducido no era un error de sintaxis ni de compilación, sino un error lógico en el comportamiento de la función.

---

## Ejecución inicial de pruebas

Al ejecutar las pruebas, Google Test ejecutó 27 pruebas distribuidas en 3 conjuntos de pruebas:

* `CalculatorTest`
* `StringUtilsTest`
* `GradeUtilsTest`

El resultado general mostró que 25 pruebas pasaron correctamente y 2 pruebas fallaron:

```text
[  PASSED  ] 25 tests.
[  FAILED  ] 2 tests, listed below:
[  FAILED  ] CalculatorTest.DetectEvenNumber
[  FAILED  ] CalculatorTest.DetectOddNumber

 2 FAILED TESTS
```

---

## Pruebas que fallaron

Las pruebas fallidas fueron:

```text
CalculatorTest.DetectEvenNumber
CalculatorTest.DetectOddNumber
```

Ambas pruebas están relacionadas con la función `is_even()`.

La primera prueba verifica que un número par sea detectado correctamente. La segunda prueba verifica que un número impar no sea identificado como par.

---

## Mensaje de error mostrado por Google Test

En la prueba `CalculatorTest.DetectEvenNumber`, Google Test mostró que el valor obtenido no coincidía con el valor esperado:

```text
Value of: is_even(8)
  Actual: false
Expected: true
```

Esto significa que la función devolvió `false` al evaluar el número `8`.

Sin embargo, el número `8` es par, por lo que el resultado esperado era `true`.

---

En la prueba `CalculatorTest.DetectOddNumber`, Google Test mostró el caso contrario:

```text
Value of: is_even(7)
  Actual: true
Expected: false
```

Esto significa que la función devolvió `true` al evaluar el número `7`.

Sin embargo, el número `7` es impar, por lo que el resultado esperado era `false`.

---

## Análisis del error

A partir de los mensajes mostrados por Google Test, se identificó que el problema estaba en la lógica de la función `is_even()`.

La implementación incorrecta era:

```cpp
bool is_even(int number) {
    return number % 2 == 1;
}
```

Esta condición evalúa si el residuo de dividir el número entre 2 es igual a 1. Por esa razón, la función retornaba `true` para números impares y `false` para números pares.

El comportamiento esperado era el contrario. La función debía retornar `true` cuando el residuo fuera igual a cero, porque un número es par cuando es divisible entre 2 sin dejar residuo.

---

## ¿Qué esperaba la prueba?

La prueba `CalculatorTest.DetectEvenNumber` esperaba que:

```cpp
is_even(8)
```

retornara:

```text
true
```

porque `8` es un número par.

La prueba `CalculatorTest.DetectOddNumber` esperaba que:

```cpp
is_even(7)
```

retornara:

```text
false
```

porque `7` es un número impar.

---

## ¿Qué obtuvo realmente?

La prueba `CalculatorTest.DetectEvenNumber` obtuvo:

```text
false
```

aunque se esperaba `true`.

La prueba `CalculatorTest.DetectOddNumber` obtuvo:

```text
true
```

aunque se esperaba `false`.

Esto confirmó que la lógica de la función estaba invertida.

---

## Corrección realizada

Para corregir el error, se modificó nuevamente la función `is_even()` en el archivo `src/calculator.cpp`.

La implementación corregida fue:

```cpp
bool is_even(int number) {
    return number % 2 == 0;
}
```

Esta versión verifica correctamente si el residuo de dividir el número entre 2 es igual a cero.

Si el residuo es cero, el número es par y la función retorna `true`. Si el residuo no es cero, el número no es par y la función retorna `false`.

---

## Recompilación del proyecto

Después de corregir la función, se volvió a compilar el proyecto desde la carpeta `build`:

```bash
make
```

La compilación volvió a completarse correctamente.

---

## Ejecución final de pruebas

Luego se ejecutaron nuevamente las pruebas unitarias:

```bash
./run_tests
```

Esta vez, todas las pruebas pasaron correctamente:

```text
[==========] 27 tests from 3 test suites ran.
[  PASSED  ] 27 tests.
```

---

## Resultado final

El resultado final fue exitoso, ya que las 27 pruebas pasaron después de corregir la función `is_even()`.

Esto demuestra que el error lógico introducido de forma intencional fue detectado por las pruebas unitarias y corregido correctamente.

---

## Errores encontrados

El error encontrado fue un error lógico en la función `is_even()`.

La función estaba implementada de forma invertida, porque retornaba `true` para números impares y `false` para números pares.

El error no impidió la compilación del proyecto, pero sí fue detectado al ejecutar las pruebas unitarias.

---

## ¿Cómo se corrigió el error?

El error se corrigió cambiando la condición:

```cpp
return number % 2 == 1;
```

por:

```cpp
return number % 2 == 0;
```

Con este cambio, la función volvió a cumplir su propósito original: identificar correctamente si un número entero es par.

---

## ¿Qué se aprendió?

Se aprendió que una prueba automatizada puede detectar errores lógicos aunque el programa compile correctamente.

También se observó que Google Test muestra información útil cuando una prueba falla, ya que indica cuál prueba falló, cuál era el valor esperado y cuál fue el valor obtenido.

Además, se comprendió la importancia de ejecutar las pruebas después de modificar el código, porque un cambio pequeño en una función puede alterar el comportamiento esperado del programa.

---

## Preguntas de reflexión

### 1. ¿Cómo ayudó Google Test a identificar el error?

Google Test ayudó a identificar el error mostrando exactamente cuáles pruebas fallaron.

En este caso, las pruebas fallidas fueron `CalculatorTest.DetectEvenNumber` y `CalculatorTest.DetectOddNumber`, ambas relacionadas con la función `is_even()`.

Además, Google Test mostró el valor esperado y el valor obtenido en cada caso. Esto permitió identificar que la función estaba devolviendo resultados contrarios a los esperados.

---

### 2. ¿Qué información útil muestra una prueba fallida?

Una prueba fallida muestra el nombre de la prueba que no pasó, el valor esperado y el valor obtenido.

Esta información es útil porque permite localizar el problema con mayor rapidez. En este caso, los mensajes indicaron que `is_even(8)` devolvía `false` cuando debía devolver `true`, y que `is_even(7)` devolvía `true` cuando debía devolver `false`.

Gracias a esta información, se pudo concluir que la lógica de la función estaba invertida.

---

### 3. ¿Por qué es importante ejecutar pruebas después de modificar código?

Es importante ejecutar pruebas después de modificar código porque cualquier cambio puede introducir errores nuevos, incluso si el programa sigue compilando correctamente.

En esta parte del laboratorio, el código compilaba sin errores, pero las pruebas demostraron que la función `is_even()` no estaba funcionando como debía.

Por eso, ejecutar pruebas después de cada modificación ayuda a confirmar que el comportamiento esperado del programa se mantiene.

---

### 4. ¿Qué riesgo existe si se cambia código y no se ejecutan las pruebas?

Si se cambia código y no se ejecutan las pruebas, existe el riesgo de dejar errores lógicos sin detectar.

El programa podría compilar correctamente, pero producir resultados incorrectos durante su uso. Esto puede afectar otras partes del proyecto y dificultar la detección del problema más adelante.

Ejecutar las pruebas reduce ese riesgo, porque permite detectar fallos rápidamente después de realizar cambios en el código.

---
