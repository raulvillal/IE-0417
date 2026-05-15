# Parte 2: Primer contenedor

## Objetivo

Ejecutar un primer contenedor usando una imagen existente desde Docker Hub y observar la diferencia entre contenedores activos y contenedores creados previamente.

## Comandos ejecutados

```bash
docker run hello-world
docker ps
docker ps -a
```

## Resultado de `docker run hello-world`

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker run hello-world

Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/
```

## Explicación de `docker run hello-world`

En este comando se ejecutó un contenedor a partir de la imagen `hello-world`. Esta imagen se utiliza como una prueba básica para verificar que Docker puede crear y ejecutar contenedores correctamente.

Durante la ejecución, el contenedor imprimió el mensaje `Hello from Docker!` y luego finalizó. Esto permitió comprobar que el cliente de Docker pudo comunicarse con el daemon, que se pudo utilizar la imagen correspondiente y que Docker logró crear un contenedor funcional.

## ¿Qué ocurrió si la imagen no estaba descargada?

Si la imagen no está descargada localmente, Docker la busca en Docker Hub, la descarga y luego crea el contenedor a partir de ella.

En este caso, la imagen ya había sido descargada en una ejecución anterior, por lo que en la salida no apareció nuevamente el proceso completo de descarga. Aun así, el mensaje de `hello-world` describe el flujo general: el cliente contacta al daemon, el daemon obtiene la imagen si es necesario, crea el contenedor y envía la salida hacia la terminal.

## Resultado de `docker ps`

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker ps
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
```

## Explicación de `docker ps`

Con el comando `docker ps` se revisaron los contenedores que estaban en ejecución en ese momento. La salida no mostró ningún contenedor activo porque el contenedor `hello-world` terminó inmediatamente después de imprimir su mensaje.

## Resultado de `docker ps -a`

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker ps -a
CONTAINER ID   IMAGE         COMMAND    CREATED          STATUS                      PORTS     NAMES
9701e13e739d   hello-world   "/hello"   19 seconds ago   Exited (0) 17 seconds ago             eloquent_agnesi
cbf788acd21c   hello-world   "/hello"   51 minutes ago   Exited (0) 51 minutes ago             unruffled_brahmagupta
```

## Explicación de `docker ps -a`

Con el comando `docker ps -a` se observaron todos los contenedores existentes, incluyendo los que ya habían terminado.

En la salida aparecen dos contenedores creados a partir de la imagen `hello-world`. Ambos muestran el estado `Exited (0)`, lo cual indica que finalizaron correctamente. El código `0` significa que el proceso dentro del contenedor terminó sin errores.

## Diferencia entre `docker ps` y `docker ps -a`

La diferencia principal es que `docker ps` solo muestra los contenedores que están ejecutándose en ese momento, mientras que `docker ps -a` muestra todos los contenedores, incluyendo los detenidos o finalizados.

Por eso, `docker ps` no mostró ningún contenedor activo, pero `docker ps -a` sí mostró los contenedores `hello-world` que ya habían finalizado.

## Reflexión

La imagen `hello-world` es una imagen mínima de prueba utilizada para verificar que Docker funciona correctamente. No ejecuta una aplicación compleja, sino un proceso simple que imprime un mensaje en la terminal.

El contenedor no quedó ejecutándose después de imprimir el mensaje. Esto se comprobó con `docker ps`, ya que no apareció ningún contenedor activo. Sin embargo, sí apareció en `docker ps -a` con el estado `Exited (0)`.

La razón por la que aparece en `docker ps -a` y no en `docker ps` es que `docker ps` solo muestra contenedores activos, mientras que `docker ps -a` muestra todos los contenedores, incluyendo los que ya finalizaron.

Este primer ejemplo demuestra que Docker puede usar una imagen para crear un contenedor, ejecutar un proceso dentro de él y devolver la salida a la terminal. También muestra que algunos contenedores tienen una vida corta: se crean, ejecutan una tarea específica y luego terminan.