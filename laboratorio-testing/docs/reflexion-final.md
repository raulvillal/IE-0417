## Mini reto de testing
# Parte 12: mini reto de testing

## Mini reto de testing

## Objetivo de la parte

En esta parte se agregó una nueva funcionalidad al módulo de notas y se diseñaron pruebas unitarias para verificar su comportamiento.

El objetivo fue aplicar lo aprendido durante el laboratorio mediante la implementación de una función nueva y la creación de casos de prueba normales, inválidos y de borde.

---

## Función implementada

La función implementada fue:

```cpp
bool is_valid_grade(int grade);
```

Esta función permite verificar si una nota numérica se encuentra dentro del rango válido de `0` a `100`.

---

## Archivo de encabezado modificado

Se modificó el archivo:

```bash
include/grade_utils.h
```

En este archivo se agregó la declaración de la nueva función:

```cpp
bool is_valid_grade(int grade);
```

Con esta declaración, la función puede ser utilizada desde otros archivos del proyecto, incluyendo las pruebas unitarias.

---

## Archivo de implementación modificado

También se modificó el archivo:

```bash
src/grade_utils.cpp
```

En este archivo se agregó la implementación de la función:

```cpp
bool is_valid_grade(int grade) {
    return grade >= 0 && grade <= 100;
}
```

Esta implementación retorna `true` cuando la nota está dentro del rango permitido, incluyendo los límites `0` y `100`.

Si la nota es menor que `0` o mayor que `100`, la función retorna `false`.

---

## Archivo de pruebas modificado

El archivo de pruebas modificado fue:

```bash
tests/test_grade_utils.cpp
```

En este archivo se agregaron seis pruebas unitarias para verificar la nueva función `is_valid_grade()`.

---

## Casos de prueba diseñados

Se diseñaron seis casos de prueba:

| Caso                      | Entrada | Resultado esperado | Tipo de caso    |
| ------------------------- | ------: | ------------------ | --------------- |
| Valor válido normal       |      85 | `true`             | Normal válido   |
| Valor inválido normal     |     150 | `false`            | Normal inválido |
| Borde inferior válido     |       0 | `true`             | Borde           |
| Borde superior válido     |     100 | `true`             | Borde           |
| Debajo del borde inferior |      -1 | `false`            | Inválido        |
| Encima del borde superior |     101 | `false`            | Inválido        |

Estos casos permiten verificar el comportamiento de la función tanto dentro como fuera del rango permitido.

---

## Pruebas agregadas

Las pruebas agregadas fueron:

```cpp
TEST(GradeUtilsTest, ValidGradeNormalValue) {
    EXPECT_TRUE(is_valid_grade(85));
}

TEST(GradeUtilsTest, InvalidGradeNormalValue) {
    EXPECT_FALSE(is_valid_grade(150));
}

TEST(GradeUtilsTest, ValidGradeLowerBoundary) {
    EXPECT_TRUE(is_valid_grade(0));
}

TEST(GradeUtilsTest, ValidGradeUpperBoundary) {
    EXPECT_TRUE(is_valid_grade(100));
}

TEST(GradeUtilsTest, InvalidGradeBelowLowerBoundary) {
    EXPECT_FALSE(is_valid_grade(-1));
}

TEST(GradeUtilsTest, InvalidGradeAboveUpperBoundary) {
    EXPECT_FALSE(is_valid_grade(101));
}
```

---

## ¿Por qué se escogieron estos casos?

Se escogió el valor `85` como caso normal válido porque representa una nota común dentro del rango permitido.

Se escogió el valor `150` como caso normal inválido porque está claramente por encima del rango permitido.

También se probaron los valores `0` y `100` porque son los límites exactos del rango válido. Estos casos son importantes porque permiten verificar si la función incluye correctamente ambos extremos.

Además, se probaron los valores `-1` y `101` porque están justo fuera del rango permitido. Estos casos ayudan a comprobar que la función rechaza correctamente los valores inmediatamente anteriores o posteriores a los límites válidos.

---

## Comandos ejecutados

Desde la carpeta `build`, se compiló el proyecto con:

```bash
make
```

Luego se ejecutaron las pruebas unitarias con:

```bash
./run_tests
```

---

## Resultado de la compilación

La compilación finalizó correctamente.

La salida mostró que se construyeron los objetivos principales del proyecto.

El proceso finalizó en el 100%, por lo que el ejecutable `run_tests` fue generado correctamente.

---

## Resultado de las pruebas

Al ejecutar `./run_tests`, Google Test ejecutó 48 pruebas distribuidas en 3 conjuntos de pruebas:

```text
[==========] Running 48 tests from 3 test suites.
```

Los conjuntos ejecutados fueron:

```text
CalculatorTest
StringUtilsTest
GradeUtilsTest
```

En `CalculatorTest` se ejecutaron 14 pruebas.

En `StringUtilsTest` se ejecutaron 10 pruebas.

En `GradeUtilsTest` se ejecutaron 24 pruebas.

Las nuevas pruebas de `is_valid_grade()` pasaron correctamente:

```text
[ RUN      ] GradeUtilsTest.ValidGradeNormalValue
[       OK ] GradeUtilsTest.ValidGradeNormalValue (0 ms)
[ RUN      ] GradeUtilsTest.InvalidGradeNormalValue
[       OK ] GradeUtilsTest.InvalidGradeNormalValue (0 ms)
[ RUN      ] GradeUtilsTest.ValidGradeLowerBoundary
[       OK ] GradeUtilsTest.ValidGradeLowerBoundary (0 ms)
[ RUN      ] GradeUtilsTest.ValidGradeUpperBoundary
[       OK ] GradeUtilsTest.ValidGradeUpperBoundary (0 ms)
[ RUN      ] GradeUtilsTest.InvalidGradeBelowLowerBoundary
[       OK ] GradeUtilsTest.InvalidGradeBelowLowerBoundary (0 ms)
[ RUN      ] GradeUtilsTest.InvalidGradeAboveUpperBoundary
[       OK ] GradeUtilsTest.InvalidGradeAboveUpperBoundary (0 ms)
```

El resultado final fue exitoso:

```text
[==========] 48 tests from 3 test suites ran. (11 ms total)
[  PASSED  ] 48 tests.
```

Esto indica que todas las pruebas pasaron correctamente.

---

## Resultado obtenido

El resultado obtenido fue exitoso.

La función `is_valid_grade()` fue implementada y sus seis pruebas pasaron correctamente.

Después de agregar esta nueva funcionalidad, el proyecto ejecutó 48 pruebas en total y todas finalizaron con resultado exitoso.

---


## ¿Qué se aprendió?

Se aprendió a implementar una función nueva y a diseñar pruebas unitarias para distintos tipos de entrada.

También se reforzó la importancia de probar valores normales, valores inválidos y valores justo en los límites.

Además, se observó que agregar una función al código fuente requiere actualizar tanto el archivo de encabezado como el archivo de implementación y el archivo de pruebas.

---

## Preguntas de reflexión

### 1. ¿Cuál fue el caso más obvio de probar?

El caso más obvio fue probar una nota válida normal, como `85`.

Este valor está claramente dentro del rango permitido, por lo que la función debía retornar `true`.

---

### 2. ¿Cuál fue el caso borde más importante?

Los casos borde más importantes fueron `0` y `100`.

Estos valores representan los límites exactos del rango válido. Si la función estuviera mal implementada con condiciones como `grade > 0` o `grade < 100`, estos valores podrían clasificarse incorrectamente.

---

### 3. ¿Qué error podría aparecer si no se prueban los valores `0` y `100`?

Si no se prueban los valores `0` y `100`, podría pasar desapercibido un error en las condiciones de comparación.

Por ejemplo, la función podría aceptar solo notas mayores que `0` y menores que `100`, dejando por fuera valores que realmente son válidos.

---

### 4. ¿Qué diferencia hay entre probar un valor como `50` y probar valores como `-1`, `0`, `100` y `101`?

Probar un valor como `50` permite verificar un caso normal dentro del rango permitido.

En cambio, probar `-1`, `0`, `100` y `101` permite revisar los límites y los valores inmediatamente fuera del rango válido.

Estos casos son más útiles para detectar errores en las condiciones que definen si una nota es válida o inválida.

---

### 5. ¿Qué aprendió sobre diseñar pruebas?

Se aprendió que diseñar pruebas no consiste solamente en escoger valores al azar.

Es necesario pensar en casos normales, casos inválidos y casos borde.

También se comprendió que los valores cercanos a los límites son especialmente importantes, porque permiten detectar errores que podrían no aparecer con entradas comunes.

---


# Parte 13: reflexión final

## Reflexión final

### 1. ¿Qué es software testing?

El software testing es el proceso de revisar y comprobar que un programa funciona de acuerdo con lo esperado.

Consiste en ejecutar pruebas sobre el código para detectar errores, comportamientos incorrectos o casos que no fueron considerados durante la implementación.

En este laboratorio, el testing se aplicó mediante pruebas unitarias, pruebas funcionales, casos borde, pruebas fallidas intencionales, cobertura de código e integración continua con GitHub Actions.

---

### 2. ¿Por qué el testing mejora la calidad del software?

El testing mejora la calidad del software porque permite encontrar errores antes de que el programa sea utilizado o entregado.

También ayuda a confirmar que los cambios realizados no rompen funciones que ya estaban funcionando correctamente.

Además, las pruebas sirven como una forma de documentación, porque muestran qué comportamiento se espera de cada función.

---

### 3. ¿Cuál es la diferencia entre verificación y validación?

La verificación responde a la pregunta de si el producto fue construido correctamente.

Es decir, comprueba que el código cumple con lo que se diseñó o especificó.

La validación responde a la pregunta de si se construyó el producto correcto.

Es decir, revisa si el software realmente satisface la necesidad o requisito esperado por el usuario o el sistema.

---

### 4. ¿Qué es una prueba unitaria?

Una prueba unitaria es una prueba que verifica una parte pequeña del programa de forma aislada.

Normalmente evalúa una función específica, como `add()`, `divide()`, `letter_grade()` o `is_valid_grade()`.

En este laboratorio, las pruebas unitarias se implementaron con Google Test y permitieron revisar funciones individuales de los módulos `calculator`, `string_utils` y `grade_utils`.

---

### 5. ¿Qué es una prueba funcional?

Una prueba funcional es una prueba que verifica si el programa cumple con un comportamiento esperado a partir de un requisito.

A diferencia de una prueba que se enfoca solo en la implementación interna, una prueba funcional se centra en lo que el sistema debe hacer.

Por ejemplo, verificar que una nota de `95` se convierta en `A` y que una nota inválida como `101` sea rechazada corresponde a una prueba funcional, porque se relaciona directamente con un requisito del sistema.

---

### 6. ¿Qué diferencia hay entre `EXPECT_` y `ASSERT_`?

La diferencia principal es que `EXPECT_` permite que la prueba continúe aunque una verificación falle, mientras que `ASSERT_` detiene inmediatamente la prueba actual si la condición no se cumple.

`EXPECT_` es útil cuando se quieren revisar varias condiciones dentro de una misma prueba.

`ASSERT_` es útil cuando una condición es necesaria para que el resto de la prueba tenga sentido.

Por ejemplo, antes de dividir, es adecuado verificar con `ASSERT_NE` que el divisor no sea cero, porque si esa condición falla no tendría sentido continuar con la división.

---

### 7. ¿Por qué las pruebas deben ser deterministas?

Las pruebas deben ser deterministas porque deben producir el mismo resultado cada vez que se ejecutan bajo las mismas condiciones.

Si una prueba pasa algunas veces y falla otras sin que el código cambie, se vuelve difícil confiar en ella.

Las pruebas deterministas facilitan la depuración, permiten repetir errores y ayudan a mantener un proceso de desarrollo más confiable.

---

### 8. ¿Por qué puede ser útil una semilla en pruebas con valores aleatorios?

Una semilla es útil porque permite controlar la secuencia de valores pseudoaleatorios generados durante una prueba.

Aunque los valores parezcan aleatorios, al usar la misma semilla se obtiene la misma secuencia en cada ejecución.

Esto facilita reproducir errores. Si una prueba falla con una semilla específica, se puede volver a ejecutar con esa misma semilla para analizar el problema.

---

### 9. ¿Qué es cobertura de código?

La cobertura de código es una métrica que indica qué partes del programa fueron ejecutadas durante las pruebas.

Puede medir líneas, funciones o ramas ejecutadas.

En este laboratorio se utilizó `lcov` y `genhtml` para generar un reporte de cobertura. El reporte permitió observar qué archivos fuente fueron cubiertos por las pruebas.

---

### 10. ¿Por qué una cobertura alta no garantiza ausencia de errores?

Una cobertura alta no garantiza que el programa no tenga errores porque la cobertura solo indica que el código fue ejecutado.

Una línea puede ejecutarse durante una prueba, pero eso no significa que se hayan comprobado todos los resultados posibles.

Por ejemplo, una función puede ser llamada por una prueba, pero si no se revisan suficientes entradas o casos borde, todavía pueden existir errores ocultos.

---

### 11. ¿Qué ventaja tiene ejecutar pruebas en GitHub Actions?

Ejecutar pruebas en GitHub Actions permite verificar automáticamente el proyecto cada vez que se suben cambios al repositorio.

Esto ayuda a detectar errores en un ambiente externo y limpio, no solo en la computadora local.

También permite saber si el código compila y si las pruebas pasan antes de integrar cambios a una rama principal.

---

### 12. ¿Qué parte del laboratorio le pareció más útil?

La parte más útil fue la integración de pruebas automatizadas con GitHub Actions.

Esta parte permitió comprender cómo las pruebas pueden formar parte del flujo real de desarrollo y no quedarse únicamente como una ejecución local.

También fue útil observar que GitHub Actions detecta fallos cuando una prueba falla y que puede confirmar automáticamente cuando el proyecto vuelve a estar correcto.

---

### 13. ¿Qué parte le pareció más difícil?

La parte más difícil fue la configuración de cobertura y GitHub Actions.

En la cobertura aparecieron errores relacionados con `lcov`, por lo que fue necesario ajustar los comandos para ignorar ciertos errores de procesamiento y poder generar correctamente el reporte.

En GitHub Actions también fue necesario corregir la ubicación de la carpeta `.github`, ya que debía estar en la raíz del repositorio. Además, se tuvo que eliminar la carpeta `build` del repositorio porque contenía archivos generados localmente que no funcionaban correctamente en el ambiente de GitHub.

Estas dificultades ayudaron a comprender mejor la diferencia entre archivos fuente y archivos generados.

---

### 14. ¿Cómo aplicaría pruebas automatizadas en un proyecto futuro?

Aplicaría pruebas automatizadas desde las primeras etapas del proyecto.

Primero, identificaría las funciones principales y escribiría pruebas unitarias para validar sus comportamientos normales.

Después, agregaría casos borde e inválidos para revisar condiciones límite y posibles errores.

También configuraría GitHub Actions para ejecutar las pruebas automáticamente cada vez que se suban cambios al repositorio.

De esta forma, el proyecto tendría una forma constante de verificar que los cambios nuevos no rompan funcionalidades existentes.

---

## Cierre de la reflexión

Este laboratorio permitió comprender que probar software no consiste únicamente en ejecutar un programa y ver si funciona.

El testing requiere pensar en casos normales, casos borde, errores posibles, entradas inválidas y requisitos funcionales.

También se aprendió que las pruebas automatizadas ayudan a mantener el código más confiable, facilitan la detección de errores y permiten trabajar de forma más ordenada en proyectos futuros.

Al finalizar el laboratorio, el proyecto cuenta con pruebas unitarias, pruebas funcionales, casos borde, uso de semillas, medición de cobertura, integración continua y evidencia de pruebas fallidas y corregidas.

---
