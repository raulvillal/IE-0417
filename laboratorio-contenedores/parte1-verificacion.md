# Parte 1: Verificación de instalación de Docker

## Objetivo

Verificar que Docker está instalado correctamente y que puede ejecutarse desde la terminal de WSL2.

## Sistema utilizado

El laboratorio se realizó en Windows usando WSL2 como entorno de terminal. Docker se ejecuta mediante Docker Desktop integrado con WSL2.

## Comandos ejecutados

```bash
docker --version
docker info
docker help
```

## Resultado de `docker --version`

```text
Docker version 29.4.2, build 055a478
```

Este resultado confirma que el cliente de Docker está instalado y disponible desde la terminal.

## Resultado parcial de `docker info`

```text
Client:
 Version:    29.4.2
 Context:    default

Server:
 Containers: 0
  Running: 0
  Paused: 0
  Stopped: 0
 Images: 0
 Server Version: 29.4.2
 Storage Driver: overlayfs
 Cgroup Version: 2
 Kernel Version: 6.6.114.1-microsoft-standard-WSL2
 Operating System: Docker Desktop
 OSType: linux
 Architecture: x86_64
 CPUs: 8
 Total Memory: 3.467GiB
 Name: docker-desktop
```

## Explicación de `docker info`

El comando `docker info` muestra información detallada sobre la instalación y el estado actual de Docker. Incluye datos del cliente, del servidor o daemon, la cantidad de contenedores e imágenes existentes, la versión del servidor, el sistema operativo usado por Docker, el kernel, la arquitectura, la memoria disponible, el tipo de almacenamiento y los plugins disponibles.

Esta información es importante porque permite confirmar no solo que el comando `docker` existe, sino también que el cliente puede comunicarse correctamente con el servicio de Docker.

## Resultado de `docker help`

El comando `docker help` muestra la lista general de comandos disponibles en Docker. Sirve como una referencia rápida para conocer las operaciones principales, como ejecutar contenedores, listar imágenes, administrar redes, administrar volúmenes y consultar información del sistema.

## Reflexión

Instalar Docker no significa necesariamente que Docker esté funcionando correctamente. La instalación solo confirma que el comando `docker` está disponible, pero también se necesita que el cliente pueda comunicarse con el daemon o servidor de Docker.

El comando `docker info` permite verificar esa comunicación y muestra información útil del entorno, como la versión instalada, el número de contenedores e imágenes, el sistema operativo usado por Docker, el kernel, la arquitectura, la memoria disponible, las redes y los runtimes.

Docker necesita un daemon ejecutándose en segundo plano porque el comando `docker` actúa como cliente. El daemon es el proceso encargado de descargar imágenes, crear contenedores, iniciarlos, detenerlos, administrar redes y manejar volúmenes.

Por eso, antes de continuar con el laboratorio, fue importante verificar no solo que Docker estuviera instalado, sino también que Docker Desktop estuviera funcionando correctamente con WSL2.