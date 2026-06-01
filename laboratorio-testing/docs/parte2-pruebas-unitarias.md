# Parte 2: Implementación inicial del código

## Objetivo de la parte

En esta segunda parte se implementó el código base del proyecto. El objetivo fue crear funciones sencillas en C++.

---

## ¿Qué se hizo?

Se crearon los archivos necesarios para implementar las funciones iniciales del laboratorio. Cada archivo `.h` contiene las declaraciones de las funciones, mientras que cada archivo `.cpp` contiene la implementación correspondiente.

Esta separación permite organizar mejor el proyecto, ya que otros archivos pueden incluir las declaraciones desde los encabezados sin depender directamente de los detalles internos de implementación.

---

## Archivos creados

En la carpeta `include` se crearon los siguientes archivos de cabecera:

```bash
include/calculator.h
include/string_utils.h
include/grade_utils.h
```

En la carpeta `src` se crearon los siguientes archivos fuente:

```bash
src/calculator.cpp
src/string_utils.cpp
src/grade_utils.cpp
```

---

## Comandos utilizados

Desde la carpeta `laboratorio-testing`, se crearon los archivos correspondientes dentro de `include` y `src`.

Los archivos creados fueron:

```bash
touch include/calculator.h
touch include/string_utils.h
touch include/grade_utils.h
touch src/calculator.cpp
touch src/string_utils.cpp
touch src/grade_utils.cpp
```

Luego se copió en cada archivo el código indicado en el enunciado del laboratorio.

---

## Módulos creados

### Módulo `calculator`

El módulo `calculator` contiene funciones matemáticas básicas y una función para verificar si un número es par.

Las funciones declaradas e implementadas en este módulo son:

```cpp
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
bool is_even(int number);
```

Este módulo permitirá probar operaciones aritméticas simples, así como el manejo de un caso inválido en la división entre cero.

---

### Módulo `string_utils`

El módulo `string_utils` contiene funciones para trabajar con cadenas de texto.

Las funciones declaradas e implementadas en este módulo son:

```cpp
std::string to_uppercase(const std::string& text);
bool is_palindrome(const std::string& text);
int count_vowels(const std::string& text);
```

Este módulo permitirá probar transformaciones de texto, detección de palíndromos y conteo de vocales.

---

### Módulo `grade_utils`

El módulo `grade_utils` contiene funciones relacionadas con notas numéricas.

Las funciones declaradas e implementadas en este módulo son:

```cpp
double average(const std::vector<int>& grades);
bool is_passing(int grade);
char letter_grade(int grade);
```

Este módulo permitirá probar el cálculo de promedios, la verificación de aprobación y la conversión de una nota numérica a una letra de calificación.

---

## Función de cada archivo `.h`

### `include/calculator.h`

Este archivo declara las funciones del módulo `calculator`. Su función es indicar qué operaciones matemáticas estarán disponibles para otros archivos del proyecto.

En este archivo se declaran las funciones de suma, resta, multiplicación, división y verificación de números pares.

---

### `include/string_utils.h`

Este archivo declara las funciones del módulo `string_utils`. Su función es indicar qué operaciones de texto estarán disponibles para otros archivos del proyecto.

En este archivo se declaran las funciones para convertir texto a mayúsculas, detectar palíndromos y contar vocales.

---

### `include/grade_utils.h`

Este archivo declara las funciones del módulo `grade_utils`. Su función es indicar qué operaciones relacionadas con notas estarán disponibles para otros archivos del proyecto.

En este archivo se declaran las funciones para calcular el promedio de una lista de notas, verificar si una nota es aprobatoria y convertir una nota numérica en una calificación con letra.

---

## Función de cada archivo `.cpp`

### `src/calculator.cpp`

Este archivo implementa las funciones declaradas en `calculator.h`.

Incluye la lógica para sumar, restar, multiplicar y dividir números enteros. También implementa la función `is_even`, que determina si un número es par.

Además, la función `divide` incluye una validación para evitar la división entre cero. Si el divisor es cero, se lanza una excepción de tipo `std::invalid_argument`.

---

### `src/string_utils.cpp`

Este archivo implementa las funciones declaradas en `string_utils.h`.

La función `to_uppercase` convierte los caracteres de una cadena a mayúsculas. La función `is_palindrome` normaliza el texto ignorando espacios y diferencias entre mayúsculas y minúsculas para verificar si el texto se lee igual en ambos sentidos. La función `count_vowels` cuenta cuántas vocales contiene una cadena.

---

### `src/grade_utils.cpp`

Este archivo implementa las funciones declaradas en `grade_utils.h`.

La función `average` calcula el promedio de una lista de notas y lanza una excepción si la lista está vacía. La función `is_passing` verifica si una nota alcanza el mínimo de aprobación. La función `letter_grade` convierte una nota numérica en una letra de calificación y rechaza notas fuera del rango permitido.

---

## Casos normales, casos borde y casos inválidos identificados

### Casos identificados en `calculator`

La función `add` puede tener casos normales como sumar dos enteros positivos o dos enteros negativos.

La función `subtract` puede probarse con restas donde el resultado sea positivo, negativo o cero.

La función `multiply` puede probarse con números positivos, negativos y con cero.

La función `divide` tiene casos normales cuando el divisor es distinto de cero. También tiene un caso inválido importante cuando el divisor es cero, ya que en ese caso debe lanzar una excepción.

La función `is_even` puede tener casos normales con números pares e impares. También tiene un caso borde relevante cuando el número es cero, porque cero debe considerarse par.

---

### Casos identificados en `string_utils`

La función `to_uppercase` puede tener casos normales con texto en minúsculas, texto mixto con mayúsculas y minúsculas, y texto que incluya números.

También puede tener un caso borde con una cadena vacía, ya que la función debería devolver otra cadena vacía sin generar errores.

La función `is_palindrome` puede tener casos normales con palabras palíndromas y no palíndromas. También puede tener casos especiales con espacios, letras mayúsculas y minúsculas, una sola letra o una cadena vacía.

La función `count_vowels` puede probarse con textos que tienen varias vocales, textos sin vocales y cadenas vacías.

---

### Casos identificados en `grade_utils`

La función `average` puede tener casos normales con una lista de notas válida. También tiene un caso inválido cuando la lista está vacía, ya que no se puede calcular un promedio sin datos.

La función `is_passing` puede probarse con notas aprobadas y reprobadas. Un caso borde importante es la nota mínima de aprobación, porque permite verificar si la comparación está implementada correctamente.

La función `letter_grade` tiene varios casos normales, como notas que corresponden a las letras `A`, `B`, `C`, `D` y `F`.

También tiene casos borde en los límites entre letras, por ejemplo en los cambios entre `F` y `D`, entre `D` y `C`, entre `C` y `B`, y entre `B` y `A`.

Además, tiene casos inválidos cuando la nota es menor que el mínimo permitido o mayor que el máximo permitido. En esos casos, la función debe lanzar una excepción.

---

### ¿Qué se aprendió?

Se aprendió que separar declaraciones e implementaciones permite organizar mejor un proyecto en C++. Los archivos `.h` funcionan como una interfaz para que otros archivos conozcan qué funciones existen, mientras que los archivos `.cpp` contienen la lógica interna de cada función.

---

# Parte 3: Primeras pruebas unitarias con Google Test

## Objetivo de la parte

En esta tercera parte se implementaron las primeras pruebas unitarias del proyecto usando Google Test. El objetivo fue verificar el funcionamiento individual de las funciones creadas en los módulos `calculator`, `string_utils` y `grade_utils`.

Las pruebas permitieron comprobar que las funciones retornaran los valores esperados en casos normales y que algunas funciones manejaran correctamente casos inválidos mediante excepciones.

---

## ¿Qué se hizo?

Se crearon archivos de prueba dentro de la carpeta `tests`. Cada archivo contiene pruebas asociadas a uno de los módulos implementados en la parte anterior.

Se probaron funciones matemáticas, funciones de manejo de texto y funciones relacionadas con notas numéricas.

---

## Archivos modificados o creados

Se crearon los siguientes archivos de prueba:

```bash
tests/test_calculator.cpp
tests/test_string_utils.cpp
tests/test_grade_utils.cpp
```

En `test_calculator.cpp` se agregaron pruebas para suma, resta, multiplicación, división, división entre cero y detección de números pares e impares.

En `test_string_utils.cpp` se agregaron pruebas para conversión a mayúsculas, detección de palíndromos y conteo de vocales.

En `test_grade_utils.cpp` se agregaron pruebas para cálculo de promedio, lista vacía, nota aprobatoria, nota reprobatoria, letras de calificación y notas inválidas.

---

## Comandos utilizados para compilar

Desde la carpeta `laboratorio-testing`, se creó una carpeta de compilación llamada `build`:

```bash
mkdir build
cd build
```

Luego se configuró el proyecto con CMake:

```bash
cmake ..
```

Después se compiló el proyecto:

```bash
make
```

---

## Resultado de la configuración con CMake

El comando `cmake ..` configuró correctamente el proyecto. CMake detectó el compilador de C y C++ instalado en el sistema y generó los archivos necesarios dentro de la carpeta `build`.

Durante la configuración apareció una advertencia relacionada con `FetchContent` y la política `CMP0135`. Esta advertencia no impidió la configuración del proyecto ni detuvo el proceso de compilación.

---

## Resultado de la compilación

El comando `make` compiló correctamente el proyecto. Se construyó la biblioteca `project_lib`, se descargó y compiló Google Test, y se generó el ejecutable de pruebas llamado:

```bash
run_tests
```

El proceso de compilación finalizó correctamente hasta llegar al 100%.

---

## Comandos utilizados para ejecutar las pruebas

Primero se ejecutaron las pruebas con el ejecutable generado:

```bash
./run_tests
```

Luego se ejecutaron las pruebas usando CTest:

```bash
ctest --output-on-failure
```

---

## Resultado de `./run_tests`

La ejecución de `./run_tests` mostró que se ejecutaron 25 pruebas distribuidas en 3 grupos de pruebas.

Los grupos de pruebas fueron:

```bash
CalculatorTest
StringUtilsTest
GradeUtilsTest
```

El resultado general fue:

```bash
[==========] 25 tests from 3 test suites ran.
[  PASSED  ] 25 tests.
```

Esto indica que todas las pruebas ejecutadas fueron exitosas.

---

## Resultado de `ctest --output-on-failure`

El comando `ctest --output-on-failure` ejecutó las mismas pruebas desde el sistema de pruebas de CMake.

El resultado final fue:

```bash
100% tests passed, 0 tests failed out of 25
```

Esto confirma que todas las pruebas fueron reconocidas y ejecutadas correctamente por CTest.

---

## Cantidad de pruebas ejecutadas

Se ejecutaron en total 25 pruebas.

La distribución fue la siguiente:

```bash
8 pruebas en CalculatorTest
7 pruebas en StringUtilsTest
10 pruebas en GradeUtilsTest
```

Todas las pruebas pasaron correctamente.

---

## Cantidad de pruebas exitosas

La cantidad de pruebas exitosas fue:

```bash
25 pruebas exitosas
```

No se presentaron pruebas fallidas en esta parte.

---

## Explicación de pruebas implementadas

### Prueba de suma de números positivos

La prueba `CalculatorTest.AddPositiveNumbers` verifica que la función `add` sume correctamente dos números positivos.

El caso probado fue:

```cpp
EXPECT_EQ(add(2, 3), 5);
```

Esta prueba confirma que la función retorna `5` al sumar `2` y `3`.

---

### Prueba de división entre cero

La prueba `CalculatorTest.DivideByZeroThrowsException` verifica que la función `divide` lance una excepción cuando se intenta dividir entre cero.

El caso probado fue:

```cpp
EXPECT_THROW(divide(10, 0), std::invalid_argument);
```

Esta prueba es importante porque la división entre cero es un caso inválido y no debe permitirse como una operación normal.

---

### Prueba de conversión a mayúsculas

La prueba `StringUtilsTest.ConvertTextToUppercase` verifica que la función `to_uppercase` convierta correctamente un texto en minúsculas a mayúsculas.

El caso probado fue:

```cpp
EXPECT_EQ(to_uppercase("hola"), "HOLA");
```

Esta prueba confirma que la función transforma cada letra al formato esperado.

---

### Prueba de detección de palíndromo con espacios

La prueba `StringUtilsTest.DetectPalindromeWithSpaces` verifica que la función `is_palindrome` pueda reconocer un palíndromo aunque el texto contenga espacios.

El caso probado fue:

```cpp
EXPECT_TRUE(is_palindrome("anita lava la tina"));
```

Esta prueba es relevante porque no solo prueba una palabra simple, sino también una frase con espacios.

---

### Prueba de promedio de notas

La prueba `GradeUtilsTest.CalculateAverage` verifica que la función `average` calcule correctamente el promedio de una lista de notas.

El caso probado fue:

```cpp
std::vector<int> grades = {80, 90, 100};
EXPECT_DOUBLE_EQ(average(grades), 90.0);
```

Esta prueba confirma que la función suma las notas y divide correctamente entre la cantidad de elementos.

---

### Prueba de lista vacía en promedio

La prueba `GradeUtilsTest.AverageEmptyVectorThrowsException` verifica que la función `average` lance una excepción cuando recibe una lista vacía.

El caso probado fue:

```cpp
std::vector<int> grades = {};
EXPECT_THROW(average(grades), std::invalid_argument);
```

Esta prueba es importante porque no se puede calcular un promedio si no existen datos.

---

### Prueba de nota inválida

La prueba `GradeUtilsTest.InvalidGradeThrowsException` verifica que la función `letter_grade` rechace una nota fuera del rango permitido.

El caso probado fue:

```cpp
EXPECT_THROW(letter_grade(120), std::invalid_argument);
```

Esta prueba confirma que la función valida correctamente sus entradas y no acepta notas mayores a 100.

---

## Errores encontrados

No se encontraron errores en la ejecución de las pruebas. Todas las pruebas pasaron correctamente.

Sin embargo, durante la configuración con CMake apareció una advertencia relacionada con `FetchContent` y la política `CMP0135`. Esta advertencia no afectó la compilación ni la ejecución de las pruebas.

---

## ¿Cómo se corrigieron los errores?

No fue necesario corregir errores en esta parte, porque el proyecto compiló correctamente y todas las pruebas pasaron.

La advertencia de CMake no requirió una corrección inmediata, ya que no impidió generar los archivos de compilación ni ejecutar las pruebas.

---

## ¿Qué se aprendió?

Se aprendió a crear pruebas unitarias usando Google Test y a ejecutar esas pruebas desde un proyecto configurado con CMake.

También se comprobó que las pruebas automatizadas permiten verificar varias funciones de forma rápida y ordenada. Además, se observó que CTest puede ejecutar las pruebas registradas por CMake y mostrar un resumen claro de los resultados.

---

## Preguntas de reflexión

### 1. ¿Qué significa que una prueba pase?

Significa que el resultado obtenido por la función coincide con el resultado esperado definido en la prueba.

Cuando una prueba pasa, se tiene evidencia de que ese caso específico funciona correctamente. Sin embargo, esto no garantiza que el programa completo esté libre de errores, porque podrían existir otros casos que aún no han sido probados.

---

### 2. ¿Qué significa que una prueba falle?

Significa que el resultado obtenido no coincide con el resultado esperado, o que ocurrió un comportamiento no deseado durante la ejecución.

Una prueba fallida indica que puede existir un error en el código, en la prueba o en la forma en que se definió el resultado esperado. Por eso es necesario revisar el mensaje de error y analizar qué esperaba la prueba y qué se obtuvo realmente.

---

### 3. ¿Qué diferencia hay entre probar una función manualmente y probarla con Google Test?

Probar manualmente implica ejecutar el programa y revisar los resultados por cuenta propia. Este proceso puede ser más lento y depende de que la persona recuerde todos los casos que debe verificar.

Probar con Google Test permite escribir casos de prueba automatizados que se pueden ejecutar muchas veces. Esto hace que la verificación sea más rápida, repetible y menos propensa a errores humanos.

---

### 4. ¿Por qué las pruebas unitarias deben ser rápidas?

Las pruebas unitarias deben ser rápidas porque se ejecutan con frecuencia durante el desarrollo. Si tardan demasiado, es menos probable que se ejecuten después de cada cambio.

Cuando las pruebas son rápidas, ayudan a detectar errores de manera temprana sin interrumpir demasiado el flujo de trabajo.

---

### 5. ¿Por qué las pruebas unitarias deben ser deterministas?

Las pruebas unitarias deben ser deterministas porque deben producir el mismo resultado cada vez que se ejecutan bajo las mismas condiciones.

Si una prueba a veces pasa y a veces falla sin cambios en el código, entonces no es confiable. Una prueba determinista permite saber con mayor claridad si un cambio introdujo un error real.

---

# Parte 4: EXPECT vs ASSERT

## Objetivo de la parte

En esta cuarta parte se trabajó con la diferencia entre las verificaciones `EXPECT_` y `ASSERT_` de Google Test.

El objetivo fue observar que `EXPECT_` permite que la prueba continúe aunque una verificación falle, mientras que `ASSERT_` detiene la ejecución de la prueba actual cuando la condición no se cumple.

---

## ¿Qué se hizo?

Se agregaron dos nuevas pruebas al archivo `tests/test_calculator.cpp`.

La primera prueba utiliza varias verificaciones con `EXPECT_EQ` para comprobar diferentes sumas en una misma prueba.

La segunda prueba utiliza `ASSERT_NE` antes de realizar una división, con el fin de verificar que el divisor no sea cero antes de continuar con la operación.

---

## Archivo modificado

El archivo modificado fue:

```bash
tests/test_calculator.cpp
```

En este archivo se agregaron las pruebas:

```cpp
TEST(CalculatorTest, MultipleExpectChecks) {
    EXPECT_EQ(add(1, 1), 2);
    EXPECT_EQ(add(2, 2), 4);
    EXPECT_EQ(add(3, 3), 6);
}
```

y:

```cpp
TEST(CalculatorTest, AssertBeforeDivision) {
    int divisor = 2;

    ASSERT_NE(divisor, 0);

    EXPECT_EQ(divide(10, divisor), 5);
}
```

---

## Comandos ejecutados

Desde la carpeta `build`, se recompiló el proyecto:

```bash
make
```

Luego se ejecutaron las pruebas:

```bash
./run_tests
```

---

## Resultado con `divisor = 2`

Cuando la prueba `AssertBeforeDivision` tenía el valor:

```cpp
int divisor = 2;
```

la verificación con `ASSERT_NE(divisor, 0)` fue exitosa, porque el divisor era distinto de cero.

Por esa razón, la prueba continuó y se ejecutó la verificación:

```cpp
EXPECT_EQ(divide(10, divisor), 5);
```

El resultado general fue exitoso:

```bash
[==========] 27 tests from 3 test suites ran.
[  PASSED  ] 27 tests.
```

Esto indica que todas las pruebas pasaron correctamente.

---

## Actividad experimental con `divisor = 0`

Después se modificó temporalmente la prueba para que el divisor tuviera el valor:

```cpp
int divisor = 0;
```

La prueba quedó temporalmente de la siguiente forma:

```cpp
TEST(CalculatorTest, AssertBeforeDivision) {
    int divisor = 0;

    ASSERT_NE(divisor, 0);

    EXPECT_EQ(divide(10, divisor), 5);
}
```

Luego se volvió a compilar y ejecutar el proyecto:

```bash
make
./run_tests
```

En este caso, la prueba falló porque `ASSERT_NE(divisor, 0)` esperaba que el divisor fuera distinto de cero, pero el valor real era cero.

El mensaje mostrado fue:

```bash
Expected: (divisor) != (0), actual: 0 vs 0
```

El resumen de la ejecución indicó:

```bash
[  PASSED  ] 26 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] CalculatorTest.AssertBeforeDivision
```

---

## ¿Por qué `ASSERT_NE` detuvo la prueba?

`ASSERT_NE` detuvo la prueba porque la condición necesaria para continuar no se cumplió. La condición indicaba que el divisor debía ser diferente de cero.

Como el divisor era cero, no tenía sentido continuar con la operación de división. Si la prueba continuaba, se intentaría evaluar una división entre cero, lo cual representa un caso inválido.

Por eso, `ASSERT_NE` detuvo inmediatamente la prueba `AssertBeforeDivision`.

---

## Corrección realizada

Después del experimento, la prueba debe volver a su estado correcto:

```cpp
TEST(CalculatorTest, AssertBeforeDivision) {
    int divisor = 2;

    ASSERT_NE(divisor, 0);

    EXPECT_EQ(divide(10, divisor), 5);
}
```

Con esta corrección, el divisor vuelve a ser válido y la prueba puede ejecutarse correctamente.

---

## Diferencia entre `EXPECT_` y `ASSERT_`

Las verificaciones `EXPECT_` se utilizan cuando se desea comprobar una condición, pero se permite que la prueba continúe aunque esa condición falle.

Esto es útil cuando se quieren revisar varias condiciones dentro de una misma prueba y obtener información sobre todas las verificaciones que fallan.

Por otro lado, las verificaciones `ASSERT_` se utilizan cuando una condición es indispensable para continuar. Si un `ASSERT_` falla, la prueba se detiene inmediatamente.

En este caso, `ASSERT_NE(divisor, 0)` fue adecuado porque no se debe continuar con la división si el divisor es cero.

---

## Resultado obtenido

Como resultado de esta parte, se comprobó que `EXPECT_` y `ASSERT_` no se comportan igual ante una falla.

La prueba con `divisor = 2` pasó correctamente. La prueba experimental con `divisor = 0` falló de forma controlada y permitió observar cómo Google Test detiene una prueba cuando falla una verificación de tipo `ASSERT_`.

---

## Errores encontrados

Se provocó un fallo intencional al modificar el divisor de `2` a `0`.

El fallo apareció en la prueba:

```bash
CalculatorTest.AssertBeforeDivision
```

El mensaje indicó que se esperaba que el divisor fuera distinto de cero, pero el valor real era cero.

---

## ¿Cómo se corrigió el error?

El error se corrigió devolviendo el valor del divisor a `2`.

De esta forma, la condición `ASSERT_NE(divisor, 0)` volvió a cumplirse y la prueba pudo continuar con la división.

---

## ¿Qué se aprendió?

Se aprendió que `ASSERT_` debe utilizarse cuando una condición es necesaria para que el resto de la prueba tenga sentido.

También se observó que una prueba fallida puede ser útil para comprender el comportamiento de la herramienta y para confirmar que Google Test detecta errores de manera clara.

Además, se comprendió que `EXPECT_` permite continuar evaluando otras condiciones, mientras que `ASSERT_` detiene la prueba actual cuando una condición crítica falla.

---

## Preguntas de reflexión

### 1. ¿Cuándo conviene usar `EXPECT_`?

Conviene usar `EXPECT_` cuando se desea comprobar una condición, pero la prueba puede continuar aunque esa condición falle.

Es útil cuando una prueba tiene varias verificaciones independientes y se quiere obtener información sobre todas ellas en una misma ejecución.

---

### 2. ¿Cuándo conviene usar `ASSERT_`?

Conviene usar `ASSERT_` cuando una condición es necesaria para poder continuar con la prueba.

Por ejemplo, antes de hacer una división, conviene verificar que el divisor no sea cero. Si esa condición falla, no tiene sentido seguir ejecutando la prueba.

---

### 3. ¿Qué podría pasar si se usa `EXPECT_` cuando en realidad se necesitaba detener la prueba?

Si se usa `EXPECT_` en una condición crítica, la prueba podría continuar aunque ya no tenga sentido hacerlo.

Esto podría causar errores adicionales, resultados confusos o incluso la ejecución de operaciones inválidas. Por ejemplo, si se usara `EXPECT_NE` en lugar de `ASSERT_NE` antes de una división entre cero, la prueba podría intentar continuar con una operación no válida.

---

### 4. ¿Qué podría pasar si se usa `ASSERT_` en exceso?

Si se usa `ASSERT_` en exceso, una prueba podría detenerse demasiado pronto y ocultar otras fallas importantes.

Esto puede reducir la cantidad de información disponible después de ejecutar las pruebas, porque solo se reportaría la primera condición crítica que falló y no las demás verificaciones que también podrían estar incorrectas.

---
