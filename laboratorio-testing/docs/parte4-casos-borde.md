# Parte 6: diseño de casos borde

## Objetivo de la parte

En esta sexta parte se agregaron pruebas adicionales para verificar casos borde, casos especiales y valores límite dentro del proyecto.

El objetivo fue comprobar que las funciones no solo funcionaran con entradas normales, sino también con valores que se encuentran en los límites de comportamiento esperado.

---

## ¿Qué se hizo?

Se agregaron nuevas pruebas unitarias en los archivos de prueba del proyecto.

Estas pruebas verifican casos como divisiones con números negativos, el valor cero, cadenas vacías, cadenas de una sola letra, notas mínimas y máximas válidas, notas inválidas y límites entre letras de calificación.

---

## Archivos modificados

Los archivos modificados fueron:

```bash
tests/test_calculator.cpp
tests/test_string_utils.cpp
tests/test_grade_utils.cpp
```

---

## ¿Qué es un caso borde?

Un caso borde es una entrada que se encuentra en el límite de un rango o de una condición importante dentro del programa.

Estos casos son importantes porque muchos errores aparecen precisamente en los límites, por ejemplo, cuando una condición cambia de una categoría a otra.

En este laboratorio, algunos casos borde fueron las notas `0`, `60`, `70`, `80`, `90` y `100`, porque representan puntos donde cambia la clasificación de una nota o se valida el rango permitido.

---

## Casos borde agregados en `test_calculator.cpp`

En el archivo `tests/test_calculator.cpp` se agregaron pruebas para divisiones con números negativos y para verificar que el número cero sea considerado par.

```cpp
TEST(CalculatorTest, DivideNegativeNumbers) {
    EXPECT_EQ(divide(-10, -2), 5);
}

TEST(CalculatorTest, DividePositiveByNegative) {
    EXPECT_EQ(divide(10, -2), -5);
}

TEST(CalculatorTest, ZeroIsEven) {
    EXPECT_TRUE(is_even(0));
}
```

Estas pruebas son importantes porque permiten comprobar que la función `divide()` maneja correctamente los signos de los números y que la función `is_even()` considera correctamente el cero como un número par.

---

## Casos borde agregados en `test_string_utils.cpp`

En el archivo `tests/test_string_utils.cpp` se agregaron pruebas para cadenas vacías y cadenas de una sola letra.

```cpp
TEST(StringUtilsTest, EmptyStringToUppercase) {
    EXPECT_EQ(to_uppercase(""), "");
}

TEST(StringUtilsTest, EmptyStringIsPalindrome) {
    EXPECT_TRUE(is_palindrome(""));
}

TEST(StringUtilsTest, SingleLetterIsPalindrome) {
    EXPECT_TRUE(is_palindrome("a"));
}
```

Estas pruebas son importantes porque las cadenas vacías y las cadenas de un solo carácter pueden provocar comportamientos especiales en funciones de texto.

La prueba `EmptyStringToUppercase` verifica que convertir una cadena vacía a mayúsculas produzca otra cadena vacía.

La prueba `EmptyStringIsPalindrome` verifica que una cadena vacía sea tratada como palíndromo.

La prueba `SingleLetterIsPalindrome` verifica que una cadena de una sola letra sea considerada palíndromo, ya que se lee igual hacia adelante y hacia atrás.

---

## Casos borde agregados en `test_grade_utils.cpp`

En el archivo `tests/test_grade_utils.cpp` se agregaron pruebas para validar los extremos del rango de notas y los límites entre letras de calificación.

```cpp
TEST(GradeUtilsTest, MinimumValidGrade) {
    EXPECT_EQ(letter_grade(0), 'F');
}

TEST(GradeUtilsTest, MaximumValidGrade) {
    EXPECT_EQ(letter_grade(100), 'A');
}

TEST(GradeUtilsTest, NegativeGradeThrowsException) {
    EXPECT_THROW(letter_grade(-1), std::invalid_argument);
}

TEST(GradeUtilsTest, GradeBoundaryBetweenFAndD) {
    EXPECT_EQ(letter_grade(59), 'F');
    EXPECT_EQ(letter_grade(60), 'D');
}

TEST(GradeUtilsTest, GradeBoundaryBetweenDAndC) {
    EXPECT_EQ(letter_grade(69), 'D');
    EXPECT_EQ(letter_grade(70), 'C');
}

TEST(GradeUtilsTest, GradeBoundaryBetweenCAndB) {
    EXPECT_EQ(letter_grade(79), 'C');
    EXPECT_EQ(letter_grade(80), 'B');
}

TEST(GradeUtilsTest, GradeBoundaryBetweenBAndA) {
    EXPECT_EQ(letter_grade(89), 'B');
    EXPECT_EQ(letter_grade(90), 'A');
}
```

Estas pruebas son importantes porque verifican que la función `letter_grade()` clasifique correctamente las notas en los puntos donde cambia la letra asignada.

También se verifica que una nota negativa sea rechazada mediante una excepción, ya que está fuera del rango permitido.

---

## Comandos ejecutados

Desde la carpeta `build`, se recompiló el proyecto con:

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

La salida mostró que se construyeron los objetivos necesarios del proyecto, incluyendo `project_lib`, `gtest`, `gtest_main`, `run_tests`, `gmock` y `gmock_main`.

El proceso llegó hasta el 100%, por lo que el ejecutable de pruebas quedó generado correctamente.

---

## Resultado de las pruebas

Al ejecutar `./run_tests`, Google Test ejecutó 40 pruebas distribuidas en 3 conjuntos de pruebas:

```text
[==========] Running 40 tests from 3 test suites.
```

Los conjuntos de pruebas ejecutados fueron:

```text
CalculatorTest
StringUtilsTest
GradeUtilsTest
```

En `CalculatorTest` se ejecutaron 13 pruebas. Entre las pruebas nuevas, pasaron correctamente:

```text
[       OK ] CalculatorTest.DivideNegativeNumbers
[       OK ] CalculatorTest.DividePositiveByNegative
[       OK ] CalculatorTest.ZeroIsEven
```

En `StringUtilsTest` se ejecutaron 10 pruebas. Entre las pruebas nuevas, pasaron correctamente:

```text
[       OK ] StringUtilsTest.EmptyStringToUppercase
[       OK ] StringUtilsTest.EmptyStringIsPalindrome
[       OK ] StringUtilsTest.SingleLetterIsPalindrome
```

En `GradeUtilsTest` se ejecutaron 17 pruebas. Entre las pruebas nuevas, pasaron correctamente:

```text
[       OK ] GradeUtilsTest.MinimumValidGrade
[       OK ] GradeUtilsTest.MaximumValidGrade
[       OK ] GradeUtilsTest.NegativeGradeThrowsException
[       OK ] GradeUtilsTest.GradeBoundaryBetweenFAndD
[       OK ] GradeUtilsTest.GradeBoundaryBetweenDAndC
[       OK ] GradeUtilsTest.GradeBoundaryBetweenCAndB
[       OK ] GradeUtilsTest.GradeBoundaryBetweenBAndA
```

El resultado final fue:

```text
[==========] 40 tests from 3 test suites ran. (1 ms total)
[  PASSED  ] 40 tests.
```

Esto indica que todas las pruebas pasaron correctamente.

---

## ¿Falló alguna prueba?

No falló ninguna prueba durante esta parte.

Las pruebas de casos borde se ejecutaron correctamente y no fue necesario realizar correcciones adicionales en el código fuente.

---

## Resultado obtenido

El resultado obtenido fue exitoso, ya que las 40 pruebas pasaron correctamente.

Esto demuestra que las funciones evaluadas respondieron adecuadamente tanto en casos normales como en casos borde.

---

## ¿Qué se aprendió?

Se aprendió que los casos borde permiten revisar situaciones que podrían no aparecer al probar únicamente valores normales.

También se observó que las pruebas unitarias ayudan a confirmar que los límites de una función se comportan como se espera.

Además, se comprendió que probar valores justo antes y justo después de un cambio de categoría ayuda a detectar errores en condiciones como `>=`, `>`, `<=` o `<`.

---

## Preguntas de reflexión

### 1. ¿Por qué no basta con probar casos normales?

No basta con probar casos normales porque un programa puede funcionar correctamente con entradas comunes, pero fallar en los límites o en situaciones especiales.

Por ejemplo, una función de calificaciones podría funcionar con una nota como `85`, pero fallar al evaluar exactamente `80`, `90` o `70`, que son puntos donde cambia la categoría de la nota.

---

### 2. ¿Qué es un caso borde?

Un caso borde es una entrada que se encuentra en el límite de una condición, rango o cambio de comportamiento.

Por ejemplo, en la función `letter_grade()`, los valores `60`, `70`, `80` y `90` son casos borde porque representan los puntos exactos donde cambia la letra asignada.

---

### 3. ¿Qué es un caso inválido?

Un caso inválido es una entrada que no debería ser aceptada por el programa porque está fuera del rango permitido o no cumple con las condiciones esperadas.

En este laboratorio, una nota como `-1` es un caso inválido porque las notas válidas deben estar entre `0` y `100`.

---

### 4. ¿Qué diferencia hay entre probar `85` y probar exactamente `80`, `90` o `70`?

Probar `85` permite verificar un caso normal dentro del rango de la letra `B`.

En cambio, probar exactamente `80`, `90` o `70` permite verificar los límites donde cambia la clasificación de la nota.

Estos valores son más sensibles porque un error en las condiciones podría clasificar incorrectamente la nota. Por ejemplo, si se usa `>` en lugar de `>=`, una nota límite podría recibir una letra incorrecta.

---

### 5. ¿Cómo puede un caso borde revelar errores ocultos?

Un caso borde puede revelar errores ocultos porque obliga a probar las condiciones exactas donde el programa cambia su comportamiento.

Si una función tiene mal definida una comparación, como usar `>` en lugar de `>=`, puede funcionar bien con valores intermedios, pero fallar justo en el límite.

Por eso, los casos borde son útiles para detectar errores que no aparecerían al probar únicamente entradas normales.

---

## Semillas en pruebas

# Parte 7: uso de semillas en pruebas

## Semillas en pruebas

## Objetivo de la parte

En esta séptima parte se trabajó con una prueba que utiliza valores aleatorios controlados mediante una semilla.

El objetivo fue comprender que una semilla permite generar una secuencia reproducible de valores aleatorios. Esto es importante porque una prueba automatizada debe poder repetirse y producir el mismo comportamiento cuando se ejecuta bajo las mismas condiciones.

---

## ¿Qué se hizo?

Se agregó una nueva prueba al archivo `tests/test_calculator.cpp`.

Esta prueba utiliza un generador de números aleatorios con una semilla fija para generar pares de números enteros. Luego, cada par de números se suma usando la función `add()` y se compara el resultado con la suma esperada.

---

## Archivo modificado

El archivo modificado fue:

```bash
tests/test_calculator.cpp
```

Primero, se agregó la biblioteca necesaria para trabajar con números aleatorios:

```cpp
#include <random>
```

Luego, se agregó la siguiente prueba:

```cpp
TEST(CalculatorTest, RandomAdditionsWithFixedSeed) {
    std::mt19937 generator(12345);
    std::uniform_int_distribution<int> distribution(-100, 100);

    for (int i = 0; i < 10; i++) {
        int a = distribution(generator);
        int b = distribution(generator);

        EXPECT_EQ(add(a, b), a + b);
    }
}
```

---

## ¿Qué hace la semilla?

La semilla es el valor inicial que utiliza el generador de números pseudoaleatorios.

En este caso, la semilla utilizada fue:

```cpp
std::mt19937 generator(12345);
```

Aunque los valores parecen aleatorios, al usar siempre la misma semilla se genera la misma secuencia de números cada vez que se ejecuta la prueba.

Esto permite que la prueba sea repetible y más fácil de revisar si aparece un error.

---

## ¿Por qué se usa una semilla fija?

Se usa una semilla fija porque las pruebas automatizadas deben ser deterministas.

Una prueba determinista es una prueba que produce el mismo resultado cuando se ejecuta varias veces bajo las mismas condiciones.

Si se usaran valores aleatorios sin control, una prueba podría pasar en una ejecución y fallar en otra, lo que dificultaría identificar si el problema está en el código o en los datos generados aleatoriamente.

---

## Comandos ejecutados

Desde la carpeta `build`, se recompiló el proyecto con:

```bash
make
```

Luego se ejecutaron las pruebas unitarias con:

```bash
./run_tests
```

---

## Resultado después de agregar la prueba con semilla fija

Después de agregar la prueba `RandomAdditionsWithFixedSeed`, se ejecutaron las pruebas del proyecto.

Google Test ejecutó 41 pruebas distribuidas en 3 conjuntos de pruebas:

```text
[==========] Running 41 tests from 3 test suites.
```

En el conjunto `CalculatorTest`, se ejecutaron 14 pruebas. La nueva prueba pasó correctamente:

```text
[ RUN      ] CalculatorTest.RandomAdditionsWithFixedSeed
[       OK ] CalculatorTest.RandomAdditionsWithFixedSeed (0 ms)
```

El resultado final fue:

```text
[==========] 41 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 41 tests.
```

Esto indica que la nueva prueba fue ejecutada correctamente y que todas las pruebas pasaron.

---

## Cambio temporal de la semilla

Después se cambió temporalmente la semilla de:

```cpp
std::mt19937 generator(12345);
```

a:

```cpp
std::mt19937 generator(54321);
```

Este cambio hace que el generador produzca una secuencia diferente de valores pseudoaleatorios.

Luego se recompiló el proyecto y se ejecutaron nuevamente las pruebas:

```bash
make
./run_tests
```

---

## Resultado después de cambiar la semilla

Después de cambiar temporalmente la semilla, las pruebas volvieron a ejecutarse correctamente.

La prueba `RandomAdditionsWithFixedSeed` volvió a pasar:

```text
[ RUN      ] CalculatorTest.RandomAdditionsWithFixedSeed
[       OK ] CalculatorTest.RandomAdditionsWithFixedSeed (0 ms)
```

El resultado final volvió a ser exitoso:

```text
[==========] 41 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 41 tests.
```

Esto indica que, aunque la semilla cambió y la secuencia de valores generados también cambió, la función `add()` siguió comportándose correctamente para los valores evaluados.

---

## Corrección final

Después del experimento, la semilla debe volver a su valor original:

```cpp
std::mt19937 generator(12345);
```

Esto permite mantener la prueba en un estado reproducible y documentado.

---

## ¿Qué pasó al cambiar la semilla?

Al cambiar la semilla, el generador produjo una secuencia diferente de números pseudoaleatorios.

Sin embargo, las pruebas siguieron pasando porque la función `add()` realizó correctamente la suma de los valores generados.

El cambio de semilla no provocó errores, pero permitió observar que una semilla controla la secuencia de datos que se usan durante la prueba.

---

## ¿Por qué esto ayuda en debugging?

Esto ayuda en debugging porque, si una prueba con datos aleatorios falla, la semilla permite repetir exactamente la misma secuencia de valores que produjo el error.

De esta forma, el error puede reproducirse y analizarse con mayor facilidad.

Si no se documenta la semilla, podría ser difícil volver a generar los mismos valores y encontrar la causa del fallo.

---

## Resultado obtenido

El resultado obtenido fue exitoso.

Después de agregar la prueba con valores aleatorios controlados, se ejecutaron 41 pruebas y todas pasaron correctamente.

Después de cambiar temporalmente la semilla, se volvieron a ejecutar 41 pruebas y todas pasaron correctamente.

No se presentaron errores de compilación ni pruebas fallidas.

---

## ¿Qué se aprendió?

Se aprendió que los valores aleatorios pueden utilizarse en pruebas unitarias siempre que se controlen adecuadamente.

También se comprendió que una semilla fija permite repetir una prueba con la misma secuencia de datos, lo cual facilita la depuración y mantiene el carácter determinista de las pruebas.

Además, se observó que cambiar la semilla modifica los datos evaluados, pero no debería afectar el resultado de la prueba si la función evaluada funciona correctamente para todos los casos generados.

---

## Preguntas de reflexión

### 1. ¿Por qué las pruebas con datos aleatorios pueden ser peligrosas si no se controlan?

Las pruebas con datos aleatorios pueden ser peligrosas si no se controlan porque podrían generar datos diferentes en cada ejecución.

Esto puede provocar que una prueba pase algunas veces y falle otras, lo cual dificulta saber si existe un error real en el código o si el fallo depende de los datos generados en ese momento.

---

### 2. ¿Qué ventaja tiene usar una semilla fija?

La ventaja de usar una semilla fija es que permite repetir la misma secuencia de valores pseudoaleatorios cada vez que se ejecuta la prueba.

Esto hace que la prueba sea reproducible, más estable y más fácil de analizar si aparece un fallo.

---

### 3. ¿Cómo ayuda la semilla a reproducir errores?

La semilla ayuda a reproducir errores porque permite generar nuevamente los mismos valores que provocaron una falla.

Si una prueba falla con una semilla específica, se puede volver a ejecutar la prueba con esa misma semilla para analizar el problema y verificar si la corrección realizada funcionó.

---

### 4. ¿Por qué es importante documentar la semilla usada?

Es importante documentar la semilla usada porque permite saber exactamente qué secuencia de valores fue utilizada durante la prueba.

Esto facilita repetir la prueba en otro momento o en otra computadora, especialmente si se necesita investigar un error relacionado con datos aleatorios.

---
