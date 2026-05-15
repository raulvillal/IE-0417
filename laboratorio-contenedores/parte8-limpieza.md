# Parte 14: Limpieza del ambiente

## Objetivo

Aprender a revisar y limpiar recursos de Docker que ya no se utilizan, como contenedores detenidos, imágenes, volúmenes, redes y caché de construcción.

## Comandos ejecutados

```bash
docker ps -a
docker images
docker volume ls
docker network ls
docker container prune
docker image prune
docker volume prune
docker system df
docker system prune
```

## Lista de contenedores

## Comando ejecutado

```bash
docker ps -a
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker ps -a
CONTAINER ID   IMAGE         COMMAND    CREATED        STATUS                    PORTS     NAMES
0d12dbb5b84f   ubuntu        "bash"     12 hours ago   Exited (0) 12 hours ago             awesome_elion
9701e13e739d   hello-world   "/hello"   15 hours ago   Exited (0) 15 hours ago             eloquent_agnesi
cbf788acd21c   hello-world   "/hello"   16 hours ago   Exited (0) 16 hours ago             unruffled_brahmagupta
```

## Explicación

Con `docker ps -a` se listaron todos los contenedores existentes, incluyendo los detenidos. En este caso, quedaron tres contenedores detenidos: uno creado a partir de `ubuntu` y dos creados a partir de `hello-world`.

## Lista de imágenes

## Comando ejecutado

```bash
docker images
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker images
                                                                             i Info →   U  In Use
IMAGE                   ID             DISK USAGE   CONTENT SIZE   EXTRA
hello-world:latest      0e760fdfbc48       25.9kB         9.49kB    U
laboratorio-flask:1.0   66ec6506feef        234MB         56.4MB
nginx:latest            06aa3d7be10b        240MB         65.9MB
redis:latest            0c341492924c        204MB         55.3MB
ubuntu:latest           f3d28607ddd7        160MB         45.3MB    U
```

## Explicación

Con `docker images` se listaron las imágenes disponibles localmente. Se observaron imágenes usadas durante el laboratorio, como `hello-world`, `ubuntu`, `laboratorio-flask`, `nginx` y `redis`.

Estas imágenes ocupan espacio en disco aunque no haya contenedores ejecutándose en ese momento.

## Lista de volúmenes

## Comando ejecutado

```bash
docker volume ls
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker volume ls
DRIVER    VOLUME NAME
local     datos-lab
```

## Explicación

Con `docker volume ls` se verificó que seguía existiendo el volumen `datos-lab`, creado durante la parte de persistencia con volúmenes.

## Lista de redes

## Comando ejecutado

```bash
docker network ls
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker network ls
NETWORK ID     NAME      DRIVER    SCOPE
d2454c819149   bridge    bridge    local
4c8fcf409d4d   host      host      local
b5df90643193   none      null      local
```

## Explicación

Con `docker network ls` se listaron las redes existentes. Solo aparecieron las redes por defecto de Docker: `bridge`, `host` y `none`.

Las redes personalizadas usadas anteriormente, como `red-lab` y `red-app`, ya habían sido eliminadas en sus respectivas partes.

## Limpieza de contenedores detenidos

## Comando ejecutado

```bash
docker container prune
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker container prune
WARNING! This will remove all stopped containers.
Are you sure you want to continue? [y/N] y
Deleted Containers:
0d12dbb5b84f8eedb8d3881649a39fc492a1e0722fe67a7dabfd7f0db83cd912
9701e13e739d7ca01dce6b1a96c55c4f7c5ab65bcd9bfa391be437d5f7b4fe3a
cbf788acd21c36615b09f98fcdea1ee53b9c235da2ec7905ded9ab7bfdf8cc3c

Total reclaimed space: 20.48kB
```

## Explicación

Con `docker container prune` se eliminaron todos los contenedores detenidos. En este caso, se eliminaron los contenedores restantes de `ubuntu` y `hello-world`.

Este comando no elimina imágenes, volúmenes ni redes; solamente elimina contenedores detenidos.

## Limpieza de imágenes no utilizadas

## Comando ejecutado

```bash
docker image prune
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker image prune
WARNING! This will remove all dangling images.
Are you sure you want to continue? [y/N] y
Total reclaimed space: 0B
```

## Explicación

Con `docker image prune` se intentó eliminar imágenes colgantes o sin etiqueta. En este caso, no se recuperó espacio porque no había imágenes de ese tipo.

Este comando no elimina necesariamente todas las imágenes no usadas; para una limpieza más agresiva existe `docker image prune -a`, pero debe usarse con cuidado.

## Limpieza de volúmenes no utilizados

## Comando ejecutado

```bash
docker volume prune
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker volume prune
WARNING! This will remove anonymous local volumes not used by at least one container.
Are you sure you want to continue? [y/N] y
Total reclaimed space: 0B
```

## Explicación

Con `docker volume prune` se intentó limpiar volúmenes locales anónimos que no estuvieran siendo usados por contenedores.

En este caso, no se recuperó espacio. El volumen nombrado `datos-lab` permaneció disponible, por lo que no fue eliminado por este comando.

## Revisión del espacio usado por Docker

## Comando ejecutado

```bash
docker system df
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker system df
TYPE            TOTAL     ACTIVE    SIZE      RECLAIMABLE
Images          5         0         661.2MB   577.2MB (87%)
Containers      0         0         0B        0B
Local Volumes   1         0         33B       33B (100%)
Build Cache     11        0         253.3MB   18.78MB
```

## Explicación

Con `docker system df` se revisó el espacio utilizado por Docker. La salida muestra el espacio ocupado por imágenes, contenedores, volúmenes locales y caché de construcción.

Se observó que ya no quedaban contenedores, pero todavía existían imágenes, un volumen local y caché de construcción.

## Limpieza general del sistema

## Comando ejecutado

```bash
docker system prune
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker system prune
WARNING! This will remove:
  - all stopped containers
  - all networks not used by at least one container
  - all dangling images
  - unused build cache

Are you sure you want to continue? [y/N] y
Deleted build cache objects:
n5yarb64ujgsbzcy376txsdmp
uvnr31qo34z1bdqyx53gbmlcr
1mtf57n4i9rdeo3bm5r7qgncc

Total reclaimed space: 18.78MB
```

## Explicación

Con `docker system prune` se realizó una limpieza general de recursos no utilizados. Este comando puede eliminar contenedores detenidos, redes no utilizadas, imágenes colgantes y caché de construcción no utilizada.

En este caso, se eliminaron objetos de caché de construcción y se recuperaron `18.78MB`.

No se ejecutó `docker system prune -a`, ya que esa opción puede eliminar más imágenes, incluyendo imágenes no utilizadas que podrían necesitarse después.

## Diferencia entre limpiar contenedores, imágenes y volúmenes

Limpiar contenedores elimina instancias de ejecución creadas a partir de imágenes. Esto no elimina las imágenes originales.

Limpiar imágenes elimina plantillas usadas para crear contenedores. Si una imagen se elimina, puede ser necesario volver a descargarla o reconstruirla para crear nuevos contenedores.

Limpiar volúmenes elimina datos persistentes. Esta operación requiere más cuidado, porque puede borrar información creada por aplicaciones o bases de datos.

## Reflexión

Docker puede consumir mucho espacio en disco porque guarda imágenes, capas de construcción, contenedores detenidos, volúmenes y caché. Aunque los contenedores no estén activos, esos recursos pueden seguir ocupando almacenamiento.

Eliminar un contenedor no es lo mismo que eliminar una imagen. El contenedor es una instancia creada a partir de una imagen, mientras que la imagen es la plantilla usada para crear nuevas instancias.

Se debe tener cuidado al eliminar volúmenes porque pueden contener datos persistentes importantes. A diferencia de un contenedor, un volumen puede guardar información que se desea conservar aunque la aplicación se detenga o se vuelva a crear.

Como buena práctica, conviene revisar periódicamente `docker ps -a`, `docker images`, `docker volume ls`, `docker network ls` y `docker system df`. También es recomendable eliminar contenedores detenidos y recursos que ya no se usan, pero evitando comandos destructivos como `docker system prune -a` si no se entienden sus consecuencias.