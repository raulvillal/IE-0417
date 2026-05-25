# Laboratorio: depuración con gdb, valgrind y sanitizers

## 1. Información general

**Curso:** IE0417 - Diseño de software para ingeniería  
**Tema:** Depuración, análisis de memoria y análisis de hilos  
**Modalidad:** Individual
**Lenguaje:** C++  
**Herramientas:** `g++`, `gdb`, `valgrind`, sanitizers  
**Entrega:** Repositorio del curso  
**Formato de entrega:** Markdown con código, comandos, resultados y reflexiones  

---

## 2. Propósito del laboratorio

El propósito de este laboratorio es practicar técnicas básicas de depuración en programas escritos en C++. Se busca que el estudiante aprenda a observar un programa mientras se ejecuta, detenerlo en puntos específicos, inspeccionar variables, revisar la pila de llamadas, detectar errores de memoria y analizar problemas sencillos de concurrencia.

Este laboratorio no busca que el estudiante memorice comandos, sino que desarrolle una forma ordenada de razonar cuando un programa falla o produce resultados incorrectos.

Durante el laboratorio se trabajará con:

- Errores de sintaxis.
- Errores lógicos.
- Errores de tiempo de ejecución.
- Uso básico de `gdb`.
- Breakpoints.
- Ejecución paso a paso.
- Inspección de variables.
- Pila de llamadas.
- Análisis de memoria con `valgrind`.
- AddressSanitizer.
- ThreadSanitizer.
- Helgrind.
- Condiciones de carrera en programas multihilo.

---

## 3. Objetivos de aprendizaje

Al finalizar el laboratorio, el estudiante será capaz de:

1. Distinguir entre errores de sintaxis, errores de ejecución y errores lógicos.
2. Compilar programas de C++ con símbolos de depuración.
3. Usar `gdb` para ejecutar un programa paso a paso.
4. Crear breakpoints en funciones o líneas específicas.
5. Inspeccionar variables durante la ejecución.
6. Usar comandos básicos de `gdb`, como `run`, `break`, `next`, `step`, `continue`, `print` y `backtrace`.
7. Identificar errores de memoria usando `valgrind`.
8. Interpretar reportes básicos de `Memcheck`.
9. Usar AddressSanitizer para detectar errores de memoria.
10. Usar ThreadSanitizer o Helgrind para detectar condiciones de carrera.
11. Corregir errores encontrados en el código.
12. Documentar el proceso de depuración de forma clara.

---

## 4. Requisitos previos

El estudiante debe contar con:

- Linux, WSL2 o una máquina virtual Linux.
- Compilador `g++`.
- `gdb`.
- `valgrind`.
- Editor de texto o IDE.
- Git.
- Conocimientos básicos de C++.
- Conocimientos básicos de terminal.
- Conocimientos básicos de Markdown.

En Ubuntu, Debian o WSL2, las herramientas pueden instalarse con:

```bash
sudo apt update
sudo apt install build-essential gdb valgrind
```

Para verificar la instalación:

```bash
g++ --version
gdb --version
valgrind --version
```

---

## 5. Estructura de la entrega

En el repositorio del curso, cree una carpeta llamada:

```bash
laboratorio-depuracion
```

Dentro de esa carpeta, cree la siguiente estructura:

```bash
laboratorio-depuracion/
├── README.md
├── parte1-instalacion.md
├── parte2-tipos-errores.md
├── parte3-gdb-basico.md
├── parte4-gdb-funciones.md
├── parte5-valgrind.md
├── parte6-asan.md
├── parte7-hilos.md
├── parte8-reto-y-reflexion.md
└── codigo/
    ├── prueba.cpp
    ├── 01_error_sintaxis.cpp
    ├── 02_error_logico.cpp
    ├── 03_gdb_basico.cpp
    ├── 04_gdb_funciones.cpp
    ├── 05_memory_leak.cpp
    ├── 06_invalid_access.cpp
    ├── 07_use_after_free.cpp
    ├── 08_race_condition.cpp
    ├── 09_race_condition_corregido.cpp
    └── 10_reto.cpp
```

El archivo `README.md` debe funcionar como índice del laboratorio.

---

## 6. Instrucciones generales de documentación

Cada parte debe documentarse en Markdown.

Para cada ejercicio, incluya:

1. Código original.
2. Comando de compilación.
3. Comando de ejecución.
4. Error observado.
5. Herramienta usada para depurar.
6. Explicación del problema.
7. Corrección realizada.
8. Código corregido o fragmento corregido.
9. Evidencia de que el programa corregido funciona.
10. Reflexión breve.

Ejemplo de formato esperado:

````md
## Ejercicio X

### Comando de compilación

```bash
g++ -g -o programa programa.cpp
```

### Resultado observado

El programa compila, pero produce un resultado incorrecto.

### Análisis

El error ocurre porque...

### Corrección

Se modificó...

### Evidencia

```bash
Resultado esperado: ...
Resultado obtenido: ...
```

### Reflexión

Este error demuestra que...
````

---

# Parte 1: instalación y verificación del ambiente

## 1.1 Objetivo

Verificar que el ambiente de trabajo tiene las herramientas necesarias para compilar, ejecutar y depurar programas en C++.

---

## 1.2 Actividades

Ejecute los siguientes comandos:

```bash
g++ --version
```

```bash
gdb --version
```

```bash
valgrind --version
```

Ahora cree el archivo:

```bash
codigo/prueba.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>

int main() {
    std::cout << "Ambiente listo para depuración" << std::endl;
    return 0;
}
```

Compile:

```bash
g++ -g -o prueba codigo/prueba.cpp
```

Ejecute:

```bash
./prueba
```

---

## 1.3 Documentación requerida

En `parte1-instalacion.md`, documente:

- Sistema operativo utilizado.
- Versión de `g++`.
- Versión de `gdb`.
- Versión de `valgrind`.
- Resultado de compilar y ejecutar el programa de prueba.
- Explicación de para qué sirve cada herramienta.

---

## 1.4 Preguntas de reflexión

Responda:

1. ¿Para qué sirve `g++`?
2. ¿Para qué sirve `gdb`?
3. ¿Para qué sirve `valgrind`?
4. ¿Por qué se recomienda compilar con `-g` al depurar?
5. ¿Qué diferencia hay entre compilar un programa y depurarlo?

---

# Parte 2: tipos de errores

## 2.1 Objetivo

Identificar tres tipos comunes de errores:

- Errores de sintaxis.
- Errores de tiempo de ejecución.
- Errores lógicos.

Un error de sintaxis normalmente es detectado por el compilador. Un error de ejecución ocurre mientras el programa se está ejecutando. Un error lógico puede ser más difícil de encontrar, porque el programa puede compilar y ejecutarse, pero producir resultados incorrectos.

---

## 2.2 Ejercicio 1: error de sintaxis

Cree el archivo:

```bash
codigo/01_error_sintaxis.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>

int main() {
    std::cout << "Hola mundo" << std::endl
    return 0;
}
```

Compile:

```bash
g++ -g -o error_sintaxis codigo/01_error_sintaxis.cpp
```

---

## 2.3 Actividad

El programa tiene un error intencional.

Debe:

1. Compilar el programa.
2. Leer el mensaje del compilador.
3. Identificar la línea problemática.
4. Corregir el error.
5. Compilar nuevamente.
6. Ejecutar el programa.

---

## 2.4 Documentación requerida

En `parte2-tipos-errores.md`, documente:

- Mensaje de error original.
- Línea donde estaba el error.
- Causa del error.
- Código corregido.
- Resultado de la ejecución corregida.

---

## 2.5 Preguntas de reflexión

Responda:

1. ¿Este error fue detectado antes o durante la ejecución?
2. ¿Qué herramienta detectó el error?
3. ¿Por qué este tipo de error suele ser más fácil de corregir que un error lógico?

---

## 2.6 Ejercicio 2: error lógico

Cree el archivo:

```bash
codigo/02_error_logico.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>
#include <vector>

double calcular_promedio(const std::vector<int>& notas) {
    int suma = 0;

    for (int nota : notas) {
        suma += nota;
    }

    return suma;
}

int main() {
    std::vector<int> notas = {80, 90, 100};

    double promedio = calcular_promedio(notas);

    std::cout << "Promedio: " << promedio << std::endl;

    return 0;
}
```

Compile:

```bash
g++ -g -o error_logico codigo/02_error_logico.cpp
```

Ejecute:

```bash
./error_logico
```

---

## 2.7 Actividad

El programa compila y ejecuta, pero el resultado es incorrecto.

Debe:

1. Ejecutar el programa.
2. Calcular manualmente el promedio esperado.
3. Comparar el resultado esperado contra el resultado obtenido.
4. Identificar la causa del error.
5. Corregir el programa.
6. Ejecutarlo nuevamente.

---

## 2.8 Documentación requerida

En `parte2-tipos-errores.md`, documente:

- Resultado obtenido originalmente.
- Resultado esperado.
- Explicación del error.
- Código corregido.
- Resultado final.

---

## 2.9 Preguntas de reflexión

Responda:

1. ¿Por qué el compilador no detectó este error?
2. ¿Por qué este error se considera lógico?
3. ¿Qué estrategia usó para encontrarlo?
4. ¿Qué pruebas adicionales podría hacer?

---

# Parte 3: introducción a gdb

## 3.1 Objetivo

Usar `gdb` para ejecutar un programa paso a paso, detenerlo en una función e inspeccionar variables.

---

## 3.2 Código base

Cree el archivo:

```bash
codigo/03_gdb_basico.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>

int duplicar(int x) {
    int resultado = x * 2;
    return resultado;
}

int sumar(int a, int b) {
    int resultado = a + b;
    return resultado;
}

int main() {
    int numero = 5;
    int doble = duplicar(numero);
    int total = sumar(doble, 10);

    std::cout << "Número: " << numero << std::endl;
    std::cout << "Doble: " << doble << std::endl;
    std::cout << "Total: " << total << std::endl;

    return 0;
}
```

Compile con símbolos de depuración:

```bash
g++ -g -o gdb_basico codigo/03_gdb_basico.cpp
```

Ejecute normalmente:

```bash
./gdb_basico
```

Ahora abra el programa con `gdb`:

```bash
gdb ./gdb_basico
```

Dentro de `gdb`, ejecute:

```gdb
break main
run
next
next
print numero
next
print doble
next
print total
continue
quit
```

Cuando `gdb` pregunte si desea salir, responda:

```gdb
y
```

---

## 3.3 Documentación requerida

En `parte3-gdb-basico.md`, documente:

- Para qué sirve `-g`.
- Qué hace `break main`.
- Qué hace `run`.
- Qué hace `next`.
- Qué hace `print`.
- Qué valores observó para `numero`, `doble` y `total`.
- Captura o salida de terminal del uso de `gdb`.

---

## 3.4 Preguntas de reflexión

Responda:

1. ¿Qué es un breakpoint?
2. ¿Qué diferencia hay entre ejecutar el programa normalmente y ejecutarlo dentro de `gdb`?
3. ¿Qué ventaja tiene inspeccionar variables mientras el programa se ejecuta?
4. ¿Por qué `next` no entra dentro de las funciones?

---

# Parte 4: step, next y backtrace

## 4.1 Objetivo

Comprender la diferencia entre avanzar línea por línea sin entrar en funciones y entrar dentro de funciones. Además, usar `backtrace` para revisar la pila de llamadas.

---

## 4.2 Código base

Cree el archivo:

```bash
codigo/04_gdb_funciones.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>

int dividir(int a, int b) {
    int resultado = a / b;
    return resultado;
}

int calcular(int x) {
    int divisor = x - 5;
    int resultado = dividir(100, divisor);
    return resultado;
}

int main() {
    int valor = 5;
    int respuesta = calcular(valor);

    std::cout << "Respuesta: " << respuesta << std::endl;

    return 0;
}
```

Compile:

```bash
g++ -g -o gdb_funciones codigo/04_gdb_funciones.cpp
```

Ejecute normalmente:

```bash
./gdb_funciones
```

Es probable que ocurra un error de ejecución por división entre cero.

Ahora ejecute con `gdb`:

```bash
gdb ./gdb_funciones
```

Dentro de `gdb`, ejecute:

```gdb
break main
run
next
step
step
print x
print divisor
step
print a
print b
backtrace
quit
```

Cuando `gdb` pregunte si desea salir, responda:

```gdb
y
```

---

## 4.3 Actividad

Debe encontrar por qué el programa falla.

Observe:

- Valor de `valor`.
- Valor de `x`.
- Valor de `divisor`.
- Valor de `b` en la función `dividir`.
- Pila de llamadas mostrada por `backtrace`.

Corrija el programa para evitar la división por cero. Puede usar una validación sencilla:

```cpp
if (b == 0) {
    std::cout << "Error: no se puede dividir entre cero." << std::endl;
    return 0;
}
```

---

## 4.4 Documentación requerida

En `parte4-gdb-funciones.md`, documente:

- Error observado al ejecutar normalmente.
- Qué encontró usando `gdb`.
- Diferencia entre `next` y `step`.
- Resultado de `backtrace`.
- Código corregido.
- Resultado final.

---

## 4.5 Preguntas de reflexión

Responda:

1. ¿Qué diferencia observó entre `next` y `step`?
2. ¿Para qué sirve `backtrace`?
3. ¿Cuál fue la causa del error?
4. ¿Por qué este error es de tiempo de ejecución?
5. ¿Cómo podría prevenirse este tipo de error desde el diseño del programa?

---

# Parte 5: análisis de memoria con valgrind

## 5.1 Objetivo

Usar `valgrind` para detectar pérdidas de memoria y errores de acceso a memoria.

---

## 5.2 Ejercicio 1: pérdida de memoria

Cree el archivo:

```bash
codigo/05_memory_leak.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>

void crear_arreglo() {
    int* datos = new int[10];

    for (int i = 0; i < 10; i++) {
        datos[i] = i * 2;
    }

    std::cout << "Primer elemento: " << datos[0] << std::endl;
}

int main() {
    crear_arreglo();
    return 0;
}
```

Compile:

```bash
g++ -g -o memory_leak codigo/05_memory_leak.cpp
```

Ejecute:

```bash
./memory_leak
```

Analice con `valgrind`:

```bash
valgrind --leak-check=yes ./memory_leak
```

También puede usar una salida más detallada:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./memory_leak
```

---

## 5.3 Actividad

Debe:

1. Ejecutar el programa normalmente.
2. Ejecutarlo con `valgrind`.
3. Identificar si hay memoria perdida.
4. Corregir el programa usando `delete[]`.
5. Volver a ejecutar `valgrind`.
6. Confirmar que ya no hay pérdida de memoria.

Corrección esperada:

```cpp
delete[] datos;
```

---

## 5.4 Documentación requerida

En `parte5-valgrind.md`, documente:

- Qué hace el programa.
- Qué error de memoria tiene.
- Qué reportó `valgrind`.
- Qué significa `definitely lost`.
- Cómo corrigió el problema.
- Resultado de `valgrind` después de corregir.

---

## 5.5 Preguntas de reflexión

Responda:

1. ¿Qué es una pérdida de memoria?
2. ¿Por qué el programa puede terminar aparentemente bien aunque tenga una pérdida de memoria?
3. ¿Qué significa liberar memoria dinámica?
4. ¿Por qué se usa `delete[]` y no solo `delete`?
5. ¿Qué tipo de problemas podrían aparecer en programas grandes si no se libera memoria?

---

## 5.6 Ejercicio 2: acceso fuera de límites

Cree el archivo:

```bash
codigo/06_invalid_access.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>

int main() {
    int* arreglo = new int[5];

    for (int i = 0; i <= 5; i++) {
        arreglo[i] = i * 10;
    }

    std::cout << "Programa finalizado" << std::endl;

    delete[] arreglo;

    return 0;
}
```

Compile:

```bash
g++ -g -o invalid_access codigo/06_invalid_access.cpp
```

Ejecute:

```bash
./invalid_access
```

Analice con `valgrind`:

```bash
valgrind --leak-check=full ./invalid_access
```

---

## 5.7 Actividad

Debe:

1. Ejecutar el programa normalmente.
2. Observar si falla o no falla.
3. Ejecutarlo con `valgrind`.
4. Identificar el acceso inválido.
5. Corregir el ciclo.
6. Ejecutar nuevamente con `valgrind`.

Corrección esperada:

```cpp
for (int i = 0; i < 5; i++) {
    arreglo[i] = i * 10;
}
```

---

## 5.8 Documentación requerida

En `parte5-valgrind.md`, documente:

- Resultado de ejecutar normalmente.
- Resultado con `valgrind`.
- Qué significa `Invalid write`.
- Línea donde ocurre el problema.
- Código corregido.
- Resultado final.

---

## 5.9 Preguntas de reflexión

Responda:

1. ¿Por qué el programa podría no fallar aunque acceda fuera del arreglo?
2. ¿Qué significa escribir fuera de los límites de un arreglo?
3. ¿Por qué este tipo de error es peligroso?
4. ¿Qué diferencia hay entre un error visible y un comportamiento indefinido?

---

# Parte 6: AddressSanitizer

## 6.1 Objetivo

Usar AddressSanitizer para detectar errores de memoria al ejecutar un programa.

---

## 6.2 Código base

Cree el archivo:

```bash
codigo/07_use_after_free.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>

int main() {
    int* numero = new int;
    *numero = 42;

    delete numero;

    std::cout << "Número: " << *numero << std::endl;

    return 0;
}
```

Compile normalmente:

```bash
g++ -g -o use_after_free codigo/07_use_after_free.cpp
```

Ejecute:

```bash
./use_after_free
```

Ahora compile con AddressSanitizer:

```bash
g++ -g -fsanitize=address -o use_after_free_asan codigo/07_use_after_free.cpp
```

Ejecute:

```bash
./use_after_free_asan
```

---

## 6.3 Actividad

Debe:

1. Ejecutar el programa sin sanitizer.
2. Observar qué ocurre.
3. Ejecutar el programa con AddressSanitizer.
4. Identificar el error reportado.
5. Corregir el programa para no usar memoria liberada.
6. Ejecutar nuevamente con AddressSanitizer.

Una posible corrección:

```cpp
#include <iostream>

int main() {
    int* numero = new int;
    *numero = 42;

    std::cout << "Número: " << *numero << std::endl;

    delete numero;
    numero = nullptr;

    return 0;
}
```

---

## 6.4 Documentación requerida

En `parte6-asan.md`, documente:

- Qué ocurrió al ejecutar sin sanitizer.
- Qué ocurrió al ejecutar con AddressSanitizer.
- Qué significa `heap-use-after-free`.
- Línea donde ocurre el error.
- Código corregido.
- Resultado final.

---

## 6.5 Preguntas de reflexión

Responda:

1. ¿Qué significa usar memoria después de liberarla?
2. ¿Por qué este error puede ser difícil de detectar sin herramientas?
3. ¿Qué ventaja tiene AddressSanitizer sobre ejecutar el programa normalmente?
4. ¿Qué diferencia observó entre el reporte de `valgrind` y el reporte de AddressSanitizer?
5. ¿Por qué es buena práctica asignar `nullptr` después de liberar un puntero?

---

# Parte 7: análisis de hilos y condiciones de carrera

## 7.1 Objetivo

Identificar una condición de carrera en un programa multihilo usando herramientas de análisis.

---

## 7.2 Código base con condición de carrera

Cree el archivo:

```bash
codigo/08_race_condition.cpp
```

Con el siguiente contenido:

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

Compile:

```bash
g++ -g -pthread -o race_condition codigo/08_race_condition.cpp
```

Ejecute varias veces:

```bash
./race_condition
./race_condition
./race_condition
```

Ahora compile con ThreadSanitizer:

```bash
g++ -g -fsanitize=thread -pthread -o race_condition_tsan codigo/08_race_condition.cpp
```

Ejecute:

```bash
./race_condition_tsan
```

También puede analizar con Helgrind:

```bash
valgrind --tool=helgrind ./race_condition
```

---

## 7.3 Actividad

Debe:

1. Ejecutar el programa varias veces.
2. Observar si el resultado siempre es igual.
3. Identificar cuál sería el resultado esperado.
4. Ejecutar con ThreadSanitizer.
5. Ejecutar con Helgrind.
6. Explicar qué es una condición de carrera.
7. Corregir el programa usando `std::mutex`.

---

## 7.4 Código corregido

Cree el archivo:

```bash
codigo/09_race_condition_corregido.cpp
```

Con el siguiente contenido:

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

Compile:

```bash
g++ -g -pthread -o race_condition_corregido codigo/09_race_condition_corregido.cpp
```

Ejecute:

```bash
./race_condition_corregido
```

Analice con Helgrind:

```bash
valgrind --tool=helgrind ./race_condition_corregido
```

También puede compilar con ThreadSanitizer:

```bash
g++ -g -fsanitize=thread -pthread -o race_condition_corregido_tsan codigo/09_race_condition_corregido.cpp
```

Ejecute:

```bash
./race_condition_corregido_tsan
```

---

## 7.5 Documentación requerida

En `parte7-hilos.md`, documente:

- Resultado esperado del contador.
- Resultados obtenidos al ejecutar varias veces.
- Qué reportó ThreadSanitizer.
- Qué reportó Helgrind.
- Qué es una condición de carrera.
- Cómo se corrigió con `std::mutex`.
- Resultado después de corregir.

---

## 7.6 Preguntas de reflexión

Responda:

1. ¿Por qué `contador++` no es una operación segura entre varios hilos?
2. ¿Qué significa que dos hilos accedan a la misma variable compartida?
3. ¿Qué problema resuelve `std::mutex`?
4. ¿Qué hace `std::lock_guard`?
5. ¿Por qué los errores de concurrencia pueden ser difíciles de reproducir?
6. ¿Cuál herramienta le pareció más clara para analizar este caso: ThreadSanitizer o Helgrind?

---

# Parte 8: mini reto de depuración

## 8.1 Objetivo

Aplicar lo aprendido en un programa con varios errores pequeños.

---

## 8.2 Código del reto

Cree el archivo:

```bash
codigo/10_reto.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>

int obtener_mayor(int* datos, int tamano) {
    int mayor = 0;

    for (int i = 0; i <= tamano; i++) {
        if (datos[i] > mayor) {
            mayor = datos[i];
        }
    }

    return mayor;
}

double calcular_promedio(int* datos, int tamano) {
    int suma = 0;

    for (int i = 0; i < tamano; i++) {
        suma += datos[i];
    }

    return suma;
}

int main() {
    int tamano = 5;
    int* datos = new int[tamano];

    datos[0] = -10;
    datos[1] = -20;
    datos[2] = -5;
    datos[3] = -30;
    datos[4] = -15;

    int mayor = obtener_mayor(datos, tamano);
    double promedio = calcular_promedio(datos, tamano);

    std::cout << "Mayor: " << mayor << std::endl;
    std::cout << "Promedio: " << promedio << std::endl;

    return 0;
}
```

---

## 8.3 Actividad

El programa tiene varios problemas:

- Un error lógico en el cálculo del mayor.
- Un acceso fuera de límites.
- Una pérdida de memoria.
- Un error en el cálculo del promedio.

Debe usar al menos dos herramientas entre:

- Ejecución normal.
- `gdb`.
- `valgrind`.
- AddressSanitizer.

Compile normalmente:

```bash
g++ -g -o reto codigo/10_reto.cpp
```

Ejecute:

```bash
./reto
```

Analice con `valgrind`:

```bash
valgrind --leak-check=full ./reto
```

Compile con AddressSanitizer:

```bash
g++ -g -fsanitize=address -o reto_asan codigo/10_reto.cpp
```

Ejecute:

```bash
./reto_asan
```

Depure con `gdb`:

```bash
gdb ./reto
```

Comandos sugeridos dentro de `gdb`:

```gdb
break main
run
next
next
break obtener_mayor
continue
print tamano
next
print i
print datos[i]
backtrace
quit
```

---

## 8.4 Correcciones esperadas

El programa corregido debería:

1. No acceder fuera de los límites.
2. Calcular correctamente el mayor aunque todos los números sean negativos.
3. Calcular correctamente el promedio.
4. Liberar la memoria dinámica.



---

## 8.5 Documentación requerida

En `parte8-reto-y-reflexion.md`, cree una sección llamada:

```md
## Mini reto de depuración
```

Documente:

- Resultado inicial del programa.
- Herramientas usadas.
- Errores encontrados.
- Cómo se encontró cada error.
- Corrección realizada.
- Resultado final.
- Qué herramienta fue más útil y por qué.

---

# Parte 9: reflexión final

En el archivo `parte8-reto-y-reflexion.md`, cree una sección llamada:

```md
## Reflexión final
```

Responda:

1. ¿Qué entiende ahora por depuración?
2. ¿Por qué no basta con que un programa compile?
3. ¿Cuál fue la diferencia entre un error de sintaxis y un error lógico?
4. ¿Qué ventaja tiene usar `gdb`?
5. ¿Qué ventaja tiene usar `valgrind`?
6. ¿Qué ventaja tiene usar AddressSanitizer?
7. ¿Qué aprendió sobre errores de memoria?
8. ¿Qué aprendió sobre errores de concurrencia?
9. ¿Cuál fue el error más fácil de encontrar?
10. ¿Cuál fue el error más difícil de entender?
11. ¿Qué herramienta usaría primero si un programa produce un resultado incorrecto?
12. ¿Qué herramienta usaría primero si un programa falla con segmentation fault?
13. ¿Qué herramienta usaría primero si sospecha una pérdida de memoria?
14. ¿Qué herramienta usaría primero si sospecha un problema con hilos?
15. ¿Cómo aplicaría estas herramientas en proyectos futuros?

---

# Entregables

El estudiante debe entregar:

1. Enlace al repositorio.
2. Carpeta `laboratorio-depuracion`.
3. Archivos `.md` solicitados.
4. Archivos `.cpp` solicitados.
5. Evidencias de compilación.
6. Evidencias de ejecución.
7. Evidencias de uso de `gdb`.
8. Evidencias de uso de `valgrind`.
9. Evidencias de uso de sanitizers.
10. Código corregido para cada ejercicio.
11. Reflexión final.

---

# Reglas de entrega

- No se aceptan únicamente capturas de pantalla.
- No se aceptan únicamente comandos sin explicación.
- Cada error debe estar explicado con palabras propias.
- Cada corrección debe estar justificada.
- Se debe mostrar evidencia antes y después de corregir.
- El repositorio debe estar ordenado.
- El código debe compilar.
- Las respuestas deben estar en Markdown.
- Se permite trabajar en parejas, pero ambos integrantes deben comprender todos los ejercicios.

# Recomendación final

Al trabajar este laboratorio, no se debe intentar corregir el código de inmediato sin observar primero el problema. El proceso recomendado es:

1. Ejecutar el programa.
2. Observar el síntoma.
3. Reproducir el error.
4. Usar una herramienta adecuada.
5. Identificar la causa.
6. Corregir el código.
7. Verificar que el problema desapareció.
8. Documentar lo aprendido.

La depuración es una habilidad práctica. Entre más se practique, más fácil será encontrar errores en programas reales.