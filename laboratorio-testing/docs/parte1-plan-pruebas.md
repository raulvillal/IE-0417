# Parte 1: Plan de pruebas y preparación del proyecto

## Objetivo de la parte

En esta primera parte se preparó la estructura base del proyecto `laboratorio-testing`. El objetivo fue crear un proyecto en C++ organizado con carpetas separadas para archivos de cabecera, código fuente, pruebas automatizadas, documentación y configuración de GitHub Actions.

---

## ¿Qué es CMake?

CMake es una herramienta que permite configurar y generar archivos de compilación para proyectos de software. En este laboratorio se utiliza para organizar la compilación del proyecto en C++, definir el estándar del lenguaje, incluir los archivos fuente, crear una biblioteca del proyecto y preparar el ejecutable de pruebas.

CMake es útil porque evita compilar manualmente cada archivo con comandos largos de `g++`. En su lugar, permite definir la configuración del proyecto en un archivo llamado `CMakeLists.txt` y luego compilar usando comandos más simples como `cmake` y `make`.

---

## ¿Para qué sirve Google Test?

Google Test es un framework de pruebas unitarias para C++. Permite escribir pruebas automatizadas para verificar que las funciones del programa se comporten como se espera.

En este laboratorio se usará Google Test para probar funciones individuales del proyecto, como operaciones matemáticas, manejo de cadenas de texto y funciones relacionadas con notas. Permite crear pruebas automatizadas para verificar que los resultados sean los esperados.

---

## ¿Qué significa automatizar pruebas?

Automatizar pruebas significa escribir pruebas que puedan ejecutarse sin intervención manual cada vez que se necesite verificar el funcionamiento del programa.

En lugar de probar las funciones una por una de forma manual, se crean archivos de prueba que ejecutan varios casos automáticamente. Esto permite detectar errores de forma más rápida, repetir las pruebas después de cada cambio y verificar que el código siga funcionando correctamente.

---

## ¿Qué significa que las pruebas sean repetibles?

Que una prueba sea repetible significa que puede ejecutarse muchas veces bajo las mismas condiciones y producir el mismo resultado.

Esto es importante porque permite confiar en los resultados obtenidos. Si una prueba pasa una vez, pero falla después sin que el código haya cambiado, entonces la prueba no es confiable. En este laboratorio se busca que las pruebas sean deterministas y repetibles, para que sirvan como evidencia clara del comportamiento del programa.

---

## Archivos y carpetas creadas

Se creó la carpeta principal del laboratorio:

```bash
laboratorio-testing
```

Dentro de esta carpeta se crearon los siguientes directorios:

```bash
laboratorio-testing/include
laboratorio-testing/src
laboratorio-testing/tests
laboratorio-testing/docs
laboratorio-testing/.github/workflows
```

La carpeta `include` se utilizará para guardar los archivos de cabecera `.h`.

La carpeta `src` se utilizará para guardar los archivos fuente `.cpp`.

La carpeta `tests` se utilizará para guardar las pruebas unitarias con Google Test.

La carpeta `docs` se utilizará para guardar la documentación del laboratorio en formato Markdown.

La carpeta `.github/workflows` se utilizará posteriormente para guardar el archivo de configuración de GitHub Actions.

También se creó el archivo:

```bash
CMakeLists.txt
```

Este archivo contiene la configuración inicial del proyecto, incluyendo el nombre del proyecto, el estándar de C++, la opción de cobertura, la descarga de Google Test mediante `FetchContent`, la creación de la biblioteca del proyecto y la creación del ejecutable de pruebas.

---

## Comandos utilizados

Desde la raíz del repositorio se ejecutaron comandos para crear la estructura del proyecto:

```bash
mkdir -p laboratorio-testing/include
mkdir -p laboratorio-testing/src
mkdir -p laboratorio-testing/tests
mkdir -p laboratorio-testing/docs
mkdir -p laboratorio-testing/.github/workflows
cd laboratorio-testing
```

Luego se creó el archivo:

```bash
CMakeLists.txt
```

En este archivo se pegó el contenido de configuración indicado en el enunciado del laboratorio.

---

## Resultado obtenido

Como resultado de esta parte, el proyecto quedó organizado con una estructura inicial adecuada para continuar con la implementación del código fuente, las pruebas unitarias y la documentación.

---

## Preguntas de reflexión

### 1. ¿Por qué conviene separar el código fuente de las pruebas?

Conviene separar el código fuente de las pruebas porque cada parte tiene un propósito diferente. El código fuente contiene la implementación del programa, mientras que las pruebas verifican que esa implementación funcione correctamente.

Esta separación permite mantener el proyecto más ordenado, facilita encontrar archivos específicos y evita mezclar la lógica del programa con el código usado para probarlo.

---

### 2. ¿Qué ventaja tiene usar CMake en un proyecto de C++?

La ventaja de usar CMake es que permite configurar la compilación del proyecto de forma organizada y reproducible. En lugar de compilar manualmente cada archivo, CMake define cómo debe construirse el proyecto y genera los archivos necesarios para compilarlo con herramientas como `make`.

También facilita agregar bibliotecas externas, como Google Test, y permite que el proyecto pueda compilarse de forma más sencilla en diferentes entornos.

---

### 3. ¿Por qué es útil que las pruebas se puedan ejecutar con un solo comando?

Es útil porque permite verificar rápidamente si el programa sigue funcionando correctamente. Cuando las pruebas se ejecutan con un solo comando, es más fácil repetirlas después de cada cambio en el código.

Esto ayuda a detectar errores de forma temprana y reduce el riesgo de integrar cambios que rompan funcionalidades existentes.

---

### 4. ¿Qué diferencia hay entre probar manualmente y probar automáticamente?

Probar manualmente significa que una persona ejecuta el programa, introduce datos y revisa los resultados por su cuenta. Este proceso puede ser lento, repetitivo y propenso a errores humanos.

Probar automáticamente significa que las pruebas ya están escritas en código y se ejecutan de forma automática. Esto permite repetir las mismas verificaciones muchas veces, obtener resultados consistentes y detectar errores con mayor rapidez.

# Parte 9: pruebas funcionales sencillas

## Objetivo de la parte

En esta parte se trabajó con pruebas funcionales sencillas relacionadas con la conversión de notas numéricas a letras de calificación.

El objetivo fue diseñar casos de prueba a partir de un requisito funcional del sistema y verificar que dichos casos estuvieran cubiertos por las pruebas unitarias existentes.

---

## Requisito funcional evaluado

El sistema debe convertir una nota numérica entre `0` y `100` a una letra de calificación.

Las notas entre `90` y `100` deben clasificarse como `A`, las notas entre `80` y `89` como `B`, las notas entre `70` y `79` como `C`, las notas entre `60` y `69` como `D`, y las notas menores a `60` como `F`.

Si la nota está fuera del rango permitido, el sistema debe rechazarla mediante una excepción.

---

## Tabla de casos funcionales

| ID     | Requisito                | Entrada | Resultado esperado | Tipo de caso |
| ------ | ------------------------ | ------: | ------------------ | ------------ |
| TC-001 | Convertir nota excelente |      95 | A                  | Normal       |
| TC-002 | Límite inferior de A     |      90 | A                  | Borde        |
| TC-003 | Límite superior de B     |      89 | B                  | Borde        |
| TC-004 | Nota inválida baja       |      -1 | Excepción          | Inválido     |
| TC-005 | Nota inválida alta       |     101 | Excepción          | Inválido     |

---

## Verificación de cobertura de los casos funcionales

Después de revisar el archivo `tests/test_grade_utils.cpp`, se verificó que la mayoría de los casos funcionales ya estaban cubiertos por pruebas implementadas previamente.

| ID     | Entrada | Resultado esperado | Prueba que lo cubre                | Estado   |
| ------ | ------: | ------------------ | ---------------------------------- | -------- |
| TC-001 |      95 | A                  | `LetterGradeA`                     | Cubierto |
| TC-002 |      90 | A                  | `GradeBoundaryBetweenBAndA`        | Cubierto |
| TC-003 |      89 | B                  | `GradeBoundaryBetweenBAndA`        | Cubierto |
| TC-004 |      -1 | Excepción          | `NegativeGradeThrowsException`     | Cubierto |
| TC-005 |     101 | Excepción          | `GradeAboveMaximumThrowsException` | Agregado |

---

## Prueba agregada

Para cubrir de forma directa el caso funcional `TC-005`, se agregó una nueva prueba en el archivo `tests/test_grade_utils.cpp`.

La prueba agregada fue:

```cpp
TEST(GradeUtilsTest, GradeAboveMaximumThrowsException) {
    EXPECT_THROW(letter_grade(101), std::invalid_argument);
}
```

Esta prueba verifica que la función `letter_grade()` rechace una nota justo por encima del valor máximo permitido.

El valor `101` es importante porque representa el primer valor entero inválido después del límite superior `100`.

---

## Archivo modificado

El archivo modificado fue:

```bash
tests/test_grade_utils.cpp
```

En este archivo se agregó la prueba `GradeAboveMaximumThrowsException`.

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

La compilación finalizó correctamente y se generó nuevamente el ejecutable `run_tests`.

Durante la compilación apareció el siguiente mensaje:

```text
libgcov profiling error: ... overwriting an existing profile data with a different checksum
```

Este mensaje está relacionado con archivos de cobertura generados previamente por `gcov`. No impidió la compilación ni afectó la ejecución de las pruebas.

---

## Resultado de la ejecución de pruebas

Al ejecutar `./run_tests`, Google Test ejecutó 42 pruebas distribuidas en 3 conjuntos de pruebas:

```text
[==========] Running 42 tests from 3 test suites.
```

Los conjuntos de pruebas ejecutados fueron:

```text
CalculatorTest
StringUtilsTest
GradeUtilsTest
```

En `CalculatorTest` se ejecutaron 14 pruebas.

En `StringUtilsTest` se ejecutaron 10 pruebas.

En `GradeUtilsTest` se ejecutaron 18 pruebas.

La nueva prueba agregada pasó correctamente:

```text
[ RUN      ] GradeUtilsTest.GradeAboveMaximumThrowsException
[       OK ] GradeUtilsTest.GradeAboveMaximumThrowsException (0 ms)
```

El resultado final fue:

```text
[==========] 42 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 42 tests.
```

Esto indica que todas las pruebas pasaron correctamente.

---

## ¿Cuáles casos ya estaban cubiertos?

El caso `TC-001`, correspondiente a la nota `95`, ya estaba cubierto por la prueba `LetterGradeA`.

Los casos `TC-002` y `TC-003`, correspondientes a las notas `90` y `89`, ya estaban cubiertos por la prueba `GradeBoundaryBetweenBAndA`.

El caso `TC-004`, correspondiente a la nota inválida `-1`, ya estaba cubierto por la prueba `NegativeGradeThrowsException`.

---

## ¿Cuál caso tuvo que agregarse?

Se agregó el caso `TC-005`, correspondiente a la nota inválida alta `101`.

Aunque ya existía una prueba llamada `InvalidGradeThrowsException`, esta utilizaba el valor `120`. Por eso, se agregó una prueba más específica con `101`, ya que este valor está justo por encima del límite superior permitido.

---

## ¿Por qué estas pruebas se consideran funcionales?

Estas pruebas se consideran funcionales porque parten de un requisito del sistema.

El requisito indica cómo debe comportarse el programa cuando recibe una nota numérica. Por eso, las pruebas no se enfocan solamente en la estructura interna de la función, sino en verificar que el comportamiento observable sea el esperado.

Por ejemplo, si el sistema recibe `95`, debe devolver `A`. Si recibe `89`, debe devolver `B`. Si recibe `101`, debe rechazar la entrada mediante una excepción.

---

## Resultado obtenido

El resultado obtenido fue exitoso.

Después de agregar la prueba faltante para el valor `101`, se ejecutaron 42 pruebas y todas pasaron correctamente.

Esto confirma que los casos funcionales definidos en la tabla quedaron cubiertos por el conjunto de pruebas del proyecto.

---

## ¿Qué se aprendió?

Se aprendió que una prueba funcional permite relacionar directamente los requisitos del sistema con casos de prueba concretos.

También se observó que no basta con tener muchas pruebas; es importante verificar que los requisitos específicos estén cubiertos.

Además, se comprendió que los valores cercanos a los límites, como `89`, `90`, `100` y `101`, son importantes porque permiten confirmar que el sistema clasifica y rechaza entradas correctamente.

---

## Preguntas de reflexión

### 1. ¿Qué diferencia hay entre una prueba unitaria y una prueba funcional?

Una prueba unitaria verifica una unidad pequeña del código, como una función específica.

Una prueba funcional verifica que el sistema cumpla con un comportamiento esperado a partir de un requisito.

En esta parte, se probó la función `letter_grade()`, pero el enfoque fue funcional porque se partió del requisito de convertir notas numéricas en letras de calificación.

---

### 2. ¿Por qué una prueba funcional se relaciona con requisitos?

Una prueba funcional se relaciona con requisitos porque busca comprobar que el programa haga lo que se espera desde el punto de vista del sistema o del usuario.

En este caso, el requisito define cómo deben clasificarse las notas y qué debe ocurrir si una nota está fuera del rango permitido.

---

### 3. ¿Qué significa pensar desde la perspectiva del usuario o del sistema?

Significa enfocarse en el comportamiento esperado y no solamente en cómo está escrito internamente el código.

Desde la perspectiva del sistema, lo importante es que una entrada produzca la salida correcta. Por ejemplo, una nota de `90` debe clasificarse como `A`, y una nota de `101` debe ser rechazada.

---

### 4. ¿Por qué la documentación de casos de prueba ayuda al equipo?

La documentación de casos de prueba ayuda porque deja claro qué requisito se está verificando, qué entrada se usó y cuál era el resultado esperado.

También facilita que otras personas revisen si el sistema está siendo probado correctamente y si todos los casos importantes están cubiertos.

---
