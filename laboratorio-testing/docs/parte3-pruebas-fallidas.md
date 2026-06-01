# Parte 5: Ejecución de pruebas y corrección de errores

## Objetivo

Ejecutar las pruebas unitarias del proyecto, identificar posibles fallos en la implementación y corregir el código hasta que las pruebas definidas pasen correctamente.

## Compilación inicial

Desde el directorio `build`, se ejecutó el comando:

```bash
make
```

La compilación finalizó correctamente y se generó el ejecutable de pruebas `run_tests`.

## Ejecución inicial de pruebas

Luego se ejecutaron las pruebas unitarias con:

```bash
./run_tests
```

GoogleTest ejecutó 27 pruebas distribuidas en 3 conjuntos de pruebas:

* `CalculatorTest`
* `StringUtilsTest`
* `GradeUtilsTest`

El resultado inicial fue el siguiente:

```text
[  PASSED  ] 25 tests.
[  FAILED  ] 2 tests, listed below:
[  FAILED  ] CalculatorTest.DetectEvenNumber
[  FAILED  ] CalculatorTest.DetectOddNumber

 2 FAILED TESTS
```

## Análisis del error

Las pruebas fallidas correspondían a la función `is_even()`.

En la prueba `CalculatorTest.DetectEvenNumber`, el resultado fue:

```text
Value of: is_even(8)
  Actual: false
Expected: true
```

Esto indica que la función devolvía `false` al evaluar el número `8`, aunque `8` es un número par y el resultado esperado era `true`.

En la prueba `CalculatorTest.DetectOddNumber`, el resultado fue:

```text
Value of: is_even(7)
  Actual: true
Expected: false
```

Esto indica que la función devolvía `true` al evaluar el número `7`, aunque `7` es un número impar y el resultado esperado era `false`.

A partir de estos resultados, se identificó que la lógica de la función `is_even()` estaba invertida.

## Corrección aplicada

La función debía retornar `true` cuando el residuo de dividir el número entre 2 fuera igual a cero. Por lo tanto, la implementación correcta es:

```cpp
bool is_even(int number) {
    return number % 2 == 0;
}
```

Esta condición verifica correctamente si un número entero es par.

## Recompilación

Después de corregir la función, se volvió a compilar el proyecto:

```bash
make
```

La compilación volvió a completarse correctamente.

## Ejecución final de pruebas

Luego se ejecutaron nuevamente las pruebas unitarias:

```bash
./run_tests
```

Esta vez, las 27 pruebas pasaron correctamente:

```text
[  PASSED  ] 27 tests.
```

## Preguntas de reflexión

### ¿Qué error fue detectado por las pruebas?

Las pruebas detectaron un error en la función `is_even()`. La lógica implementada estaba invertida, por lo que la función devolvía `false` para números pares y `true` para números impares, produciendo resultados contrarios a los esperados.

### ¿Cómo ayudaron las pruebas unitarias a identificar el problema?

Las pruebas unitarias señalaron exactamente qué casos estaban fallando y mostraron los valores esperados y obtenidos. Esto permitió localizar rápidamente la función responsable del error y comprender que el problema estaba en la condición utilizada para determinar si un número era par.

### ¿Qué se hizo para corregir el error?

Se modificó la implementación de la función `is_even()` para que devolviera `true` cuando el residuo de dividir el número entre 2 fuera igual a cero:

```cpp
bool is_even(int number) {
    return number % 2 == 0;
}
```

Después de realizar este cambio, el proyecto fue recompilado y las pruebas se ejecutaron nuevamente.

### ¿Qué demuestra que todas las pruebas hayan pasado?

Que todas las pruebas hayan pasado demuestra que la implementación actual cumple con los casos de prueba definidos y que el error detectado fue corregido correctamente. Sin embargo, esto no garantiza que el programa esté completamente libre de errores, ya que podrían existir situaciones no contempladas por las pruebas unitarias existentes.
