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
