# Laboratorio 2: Introducción práctica a contenedores con Docker

## Información general

Curso: IE0417 - Diseño de Software para Ingeniería  
Tema: Contenedores y Docker  
Modalidad: Individual  
Entorno utilizado: Windows con WSL2 y Docker Desktop  

## Descripción

Este laboratorio tuvo como objetivo introducir el uso práctico de contenedores mediante Docker. Se trabajó con imágenes, contenedores, puertos, volúmenes, bind mounts, redes, variables de entorno, logs, inspección de contenedores y limpieza del ambiente.

Durante el desarrollo del laboratorio se creó una aplicación web sencilla con Flask, se construyó una imagen personalizada mediante un `Dockerfile` y se ejecutaron diferentes contenedores para analizar su comportamiento.

## Índice del laboratorio

- [Parte 1: Verificación de instalación de Docker](parte1-verificacion.md)
- [Parte 2: Primer contenedor](parte2-comandos-basicos.md)
- [Parte 3: Imágenes y contenedores](parte3-imagenes-y-contenedores.md)
- [Parte 4: Administración básica de contenedores](parte3-imagenes-y-contenedores.md#administración-de-contenedores)
- [Parte 5: Crear una aplicación sencilla](parte4-dockerfile.md)
- [Parte 6: Construir una imagen con Dockerfile](parte4-dockerfile.md#parte-6-construir-una-imagen-con-dockerfile)
- [Parte 7: Publicación de puertos](parte5-puertos.md)
- [Parte 8: Logs e inspección de contenedores](parte5-puertos.md#parte-8-logs-e-inspección-de-contenedores)
- [Parte 9: Variables de entorno](parte5-puertos.md#parte-9-variables-de-entorno)
- [Parte 10: Persistencia con volúmenes](parte6-volumenes.md)
- [Parte 11: Bind mounts](parte6-volumenes.md#parte-11-bind-mounts)
- [Parte 12: Redes de Docker](parte7-redes.md)
- [Parte 13: Comunicación entre servicios](parte7-redes.md#parte-13-comunicación-entre-servicios)
- [Parte 14: Limpieza del ambiente](parte8-limpieza.md)

## Estructura del proyecto

```text
laboratorio-contenedores/
├── README.md
├── parte1-verificacion.md
├── parte2-comandos-basicos.md
├── parte3-imagenes-y-contenedores.md
├── parte4-dockerfile.md
├── parte5-puertos.md
├── parte6-volumenes.md
├── parte7-redes.md
├── parte8-limpieza.md
├── evidencias/
└── app/
    ├── Dockerfile
    ├── app.py
    └── requirements.txt
```

## Aplicación desarrollada

La aplicación creada para el laboratorio utiliza Flask y contiene dos rutas principales:

- `/`: muestra un mensaje HTML.
- `/info`: devuelve información básica del laboratorio en formato JSON.

La aplicación fue ejecutada localmente y también dentro de contenedores Docker. Además, se probó el uso de variables de entorno para modificar el mensaje mostrado sin reconstruir la imagen.

## Reflexión final

Un contenedor es una unidad ligera y ejecutable que incluye una aplicación junto con sus dependencias y configuración. A diferencia de una máquina virtual, no ejecuta un sistema operativo completo con su propio kernel, sino que comparte el kernel del sistema anfitrión.

Docker resuelve el problema de ejecutar aplicaciones de forma consistente entre distintos entornos. Permite empaquetar una aplicación con sus dependencias para que pueda ejecutarse de manera similar en desarrollo, pruebas o producción.

Una imagen y un contenedor no son lo mismo. La imagen funciona como una plantilla inmutable, mientras que el contenedor es una instancia creada a partir de esa imagen. Una misma imagen puede generar varios contenedores con ciclos de vida independientes.

La diferencia entre un contenedor y una máquina virtual es que la máquina virtual incluye un sistema operativo completo, mientras que el contenedor comparte el kernel con el host. Por eso, los contenedores suelen ser más ligeros, rápidos de iniciar y fáciles de recrear.

Sobre puertos, se aprendió que no basta con que una aplicación escuche dentro del contenedor. Para acceder desde la máquina anfitriona, se debe publicar el puerto con la opción `-p`, indicando el puerto del host y el puerto del contenedor.

Sobre volúmenes, se comprobó que permiten conservar datos aunque un contenedor sea eliminado. Esto es importante porque los datos creados únicamente dentro del sistema de archivos del contenedor pueden perderse al eliminarlo.

Sobre redes, se observó que los contenedores pueden comunicarse entre sí cuando están conectados a una misma red Docker. También se comprobó que pueden usar nombres de contenedor como referencia, evitando depender directamente de direcciones IP internas.

Docker sería útil en proyectos de software donde se necesite ejecutar una aplicación con dependencias específicas, probar servicios aislados, levantar una aplicación junto con una base de datos, facilitar la instalación del entorno o asegurar que todos los integrantes de un equipo trabajen bajo condiciones similares.

La parte más útil del laboratorio fue la combinación entre construcción de imagen, publicación de puertos y variables de entorno, porque muestra un flujo cercano a cómo se podría ejecutar una aplicación real en un contenedor.

La parte más confusa fue la diferencia entre volúmenes y bind mounts. Ambos permiten montar información dentro de un contenedor, pero tienen propósitos distintos: los volúmenes son más adecuados para persistencia administrada por Docker, mientras que los bind mounts son más útiles durante el desarrollo porque conectan directamente archivos del host con el contenedor.