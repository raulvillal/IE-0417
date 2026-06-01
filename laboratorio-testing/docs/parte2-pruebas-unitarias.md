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
