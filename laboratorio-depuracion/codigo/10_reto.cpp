#include <iostream>

int obtener_mayor(int* datos, int tamano) {
    int mayor = datos[0];  //Error lógico, se colocaba 0 siempre como payor pues los valores son negativos.

    for (int i = 1; i < tamano; i++) { //Error de memoria: el ciclo for debería ser i < tamano, no i <= tamano
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

    return suma/tamano;  //Error lógico: el promedio se calcula dividiendo la suma entre el tamaño, no solo retornando la suma
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

    delete[] datos;       // Liberar la memoria asignada

    return 0;
}