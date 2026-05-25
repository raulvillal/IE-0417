# Parte 2: tipos de errores

## Ejercicio 1: error de sintaxis

### Código original

```cpp
#include <iostream>

int main() {
    std::cout << "Hola mundo" << std::endl
    return 0;
}
```

### Comando de compilación

Se compiló el programa con el siguiente comando:

```bash
g++ -g -o error_sintaxis codigo/01_error_sintaxis.cpp
```

### Resultado observado

Se obtuvo el siguiente mensaje de error del compilador:

```bash
codigo/01_error_sintaxis.cpp: In function ‘int main()’:
codigo/01_error_sintaxis.cpp:4:43: error: expected ‘;’ before ‘return’
    4 |     std::cout << "Hola mundo" << std::endl
      |                                           ^
      |                                           ;
    5 |     return 0;
      |     ~~~~~~
```

### Línea donde estaba el error

El error se encontraba en la línea donde se imprimía el mensaje `"Hola mundo"`:

```cpp
std::cout << "Hola mundo" << std::endl
```

### Causa del error

El problema ocurrió porque faltaba el punto y coma al final de la instrucción. En C++, cada sentencia debe finalizar con `;`. Al no encontrarlo, el compilador detectó el problema antes de generar el ejecutable.

### Corrección realizada

Se agregó el punto y coma faltante al final de la línea.

### Código corregido

```cpp
#include <iostream>

int main() {
    std::cout << "Hola mundo" << std::endl;
    return 0;
}
```

### Compilación después de corregir

Se volvió a compilar el programa con el siguiente comando:

```bash
g++ -g -o error_sintaxis codigo/01_error_sintaxis.cpp
```

Esta vez el comando no mostró errores, por lo que la compilación fue exitosa.

### Ejecución corregida

Se ejecutó el programa con el siguiente comando:

```bash
./error_sintaxis
```

Se obtuvo la siguiente salida:

```bash
Hola mundo
```

### Reflexión del ejercicio

Este error fue detectado por el compilador antes de ejecutar el programa. Se considera un error de sintaxis porque el código no cumplía con las reglas del lenguaje C++. Este tipo de error suele ser más fácil de corregir que un error lógico porque el compilador indica la línea aproximada donde se encuentra el problema.

## Ejercicio 2: error lógico

### Código original

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

### Comando de compilación

Se compiló el programa con el siguiente comando:

```bash
g++ -g -o error_logico codigo/02_error_logico.cpp
```

### Ejecución original

Se ejecutó el programa con el siguiente comando:

```bash
./error_logico
```

Se obtuvo la siguiente salida:

```bash
Promedio: 270
```

### Resultado esperado

El resultado esperado era:

```bash
Promedio: 90
```

### Explicación del error

El programa compiló y se ejecutó sin errores, pero produjo un resultado incorrecto. La función `calcular_promedio` estaba sumando todas las notas, pero devolvía únicamente la suma total. Por esta razón, en lugar de devolver el promedio, devolvía `270`.

El error no fue detectado por el compilador porque la instrucción `return suma;` es válida en C++. El problema estaba en la lógica del programa, ya que faltaba dividir la suma entre la cantidad de notas.

### Corrección realizada

Se agregó una variable llamada `cantidad` para contar cuántas notas se procesaron. Luego, se modificó el retorno de la función para devolver la división entre la suma y la cantidad de datos.

### Código corregido

```cpp
#include <iostream>
#include <vector>

double calcular_promedio(const std::vector<int>& notas) {
    int suma = 0;
    int cantidad = 0;

    for (int nota : notas) {
        suma += nota;
        cantidad++;
    }

    return suma / cantidad;
}

int main() {
    std::vector<int> notas = {80, 90, 100};

    double promedio = calcular_promedio(notas);

    std::cout << "Promedio: " << promedio << std::endl;

    return 0;
}
```

### Compilación después de corregir

Se volvió a compilar el programa con el siguiente comando:

```bash
g++ -g -o error_logico codigo/02_error_logico.cpp
```

El comando no mostró errores, por lo que la compilación fue exitosa.

### Ejecución corregida

Se ejecutó nuevamente el programa con el siguiente comando:

```bash
./error_logico
```

Se obtuvo la siguiente salida:

```bash
Promedio: 90
```

### Reflexión del ejercicio

Este error se considera lógico porque el programa era válido para el compilador, pero no resolvía correctamente el problema planteado. La estrategia utilizada para encontrarlo fue comparar el resultado obtenido con el resultado esperado. Al revisar la función, se observó que calculaba la suma, pero no realizaba la división necesaria para obtener el promedio.

## Preguntas de reflexión

### 1. ¿Este error fue detectado antes o durante la ejecución?

El error de sintaxis fue detectado antes de la ejecución, durante la compilación. El programa no pudo generar el ejecutable hasta que se corrigió la falta del punto y coma.

El error lógico no fue detectado por el compilador. Fue identificado después de ejecutar el programa y comparar el resultado obtenido con el resultado esperado.

### 2. ¿Qué herramienta detectó el error?

El error de sintaxis fue detectado por `g++`, ya que el compilador revisa que el código cumpla con las reglas del lenguaje.

El error lógico fue detectado mediante la ejecución y revisión manual del resultado, porque el compilador no puede saber si la operación realizada corresponde realmente con la intención del programador.

### 3. ¿Por qué este tipo de error suele ser más fácil de corregir que un error lógico?

Un error de sintaxis suele ser más fácil de corregir porque el compilador muestra un mensaje de error e indica la línea aproximada donde está el problema. En cambio, un error lógico puede ser más difícil porque el programa compila y ejecuta, pero produce resultados incorrectos sin mostrar necesariamente un mensaje de error.

### 4. ¿Por qué el compilador no detectó el error lógico?

El compilador no detectó el error lógico porque el código era sintácticamente válido. La función devolvía un valor entero compatible con el tipo de retorno `double`, por lo que no había una violación de las reglas del lenguaje. El problema era que la operación matemática no correspondía con el cálculo de un promedio.

### 5. ¿Por qué este error se considera lógico?

Se considera lógico porque el algoritmo implementado no hacía lo que debía hacer. Aunque la función se llamaba `calcular_promedio`, realmente devolvía la suma de las notas.

### 6. ¿Qué estrategia se usó para encontrarlo?

Se ejecutó el programa y se comparó el resultado obtenido con el resultado esperado. Al notar que el programa imprimía `270` en lugar de `90`, se revisó la función `calcular_promedio` y se identificó que faltaba dividir la suma entre la cantidad de notas.

### 7. ¿Qué pruebas adicionales podría hacer?

Se podrían probar otros conjuntos de notas para verificar que el promedio se calcula correctamente en diferentes casos. Por ejemplo, se podrían usar notas iguales, una sola nota, notas bajas, notas altas o una lista con más elementos. También sería conveniente revisar qué debería ocurrir si el vector estuviera vacío, porque en ese caso se podría producir una división entre cero.