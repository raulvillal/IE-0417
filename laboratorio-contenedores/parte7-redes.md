# Parte 12: Redes de Docker

## Objetivo

Crear una red personalizada en Docker y comprobar que dos contenedores conectados a la misma red pueden comunicarse entre sí usando el nombre del contenedor.

## Comandos ejecutados

```bash
docker network create red-lab
docker network ls
docker run -d --name servidor-web --network red-lab nginx
docker run -it --name cliente --network red-lab ubuntu bash
```

Dentro del contenedor `cliente` se ejecutó:

```bash
apt update
apt install -y curl
curl http://servidor-web
exit
```

Finalmente, se limpió el ambiente con:

```bash
docker stop servidor-web
docker rm servidor-web
docker rm cliente
docker network rm red-lab
```

## Creación de la red

## Comando ejecutado

```bash
docker network create red-lab
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker network create red-lab
8b226d46aa8ab9bc16396b01a34457d4c70e0376eda9c77e211e1d7bccded2ee
```

## Explicación

Con este comando se creó una red personalizada llamada `red-lab`. Las redes en Docker permiten que varios contenedores puedan comunicarse entre sí de forma aislada respecto a otros contenedores o redes.

El identificador devuelto confirma que la red fue creada correctamente.

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
8b226d46aa8a   red-lab   bridge    local
```

## Explicación

Con `docker network ls` se listaron las redes disponibles en Docker. Se observó la red personalizada `red-lab`, además de las redes creadas por defecto: `bridge`, `host` y `none`.

La red `red-lab` utiliza el driver `bridge`, lo que permite la comunicación entre contenedores conectados a esa misma red.

## Ejecución del servidor web

## Comando ejecutado

```bash
docker run -d --name servidor-web --network red-lab nginx
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker run -d --name servidor-web --network red-lab nginx
Unable to find image 'nginx:latest' locally
latest: Pulling from library/nginx
9f7bde970101: Pull complete
735e1c628373: Pull complete
834a05acfff4: Pull complete
60ad0c2ccfc6: Pull complete
1bb34ee717a4: Pull complete
030365c1a354: Pull complete
89fc4d629470: Download complete
73d0e4d315b3: Download complete
Digest: sha256:06aa3d7be10bc6307990c81bdca075793132e9163391abc370c015e344e23128
Status: Downloaded newer image for nginx:latest
d3adf88ac8ffe2d0a69be7d39ab83b910e7372075b05329948e3ae570892cdd4
```

## Explicación

Con este comando se ejecutó un contenedor en segundo plano usando la imagen `nginx`.

La opción `--name servidor-web` asignó el nombre `servidor-web` al contenedor. La opción `--network red-lab` conectó el contenedor a la red personalizada `red-lab`.

Como la imagen `nginx:latest` no estaba descargada localmente, Docker la descargó desde Docker Hub antes de crear el contenedor.

## Ejecución del contenedor cliente

## Comando ejecutado

```bash
docker run -it --name cliente --network red-lab ubuntu bash
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker run -it --name cliente --network red-lab ubuntu bash
root@033bd7492376:/#
```

## Explicación

Con este comando se creó un contenedor interactivo llamado `cliente`, basado en la imagen `ubuntu`, conectado a la misma red `red-lab`.

El propósito de este contenedor fue actuar como cliente para probar la comunicación hacia el servidor `nginx`.

## Instalación de `curl`

## Comandos ejecutados dentro del contenedor

```bash
apt update
apt install -y curl
```

## Resultado obtenido

```text
root@033bd7492376:/# apt update
Fetched 23.4 MB in 4s (5258 kB/s)
2 packages can be upgraded. Run 'apt list --upgradable' to see them.

root@033bd7492376:/# apt install -y curl
Installing:
  curl

Installing dependencies:
  bash-completion  ca-certificates  openssl  libcurl4t64  publicsuffix
  ...

Setting up curl (8.18.0-1ubuntu2.1) ...
Processing triggers for libc-bin (2.43-2ubuntu2) ...
Processing triggers for ca-certificates (20260223) ...
done.
```

## Explicación

Dentro del contenedor `cliente` se instaló `curl` para poder hacer una solicitud HTTP hacia el contenedor `servidor-web`.

La salida completa de instalación fue extensa, por lo que se documentó solamente una parte representativa donde se observa que `curl` fue instalado correctamente.

## Prueba de comunicación entre contenedores

## Comando ejecutado dentro del contenedor cliente

```bash
curl http://servidor-web
```

## Resultado obtenido

```text
root@033bd7492376:/# curl http://servidor-web
<!DOCTYPE html>
<html>
<head>
<title>Welcome to nginx!</title>
<style>
html { color-scheme: light dark; }
body { width: 35em; margin: 0 auto;
font-family: Tahoma, Verdana, Arial, sans-serif; }
</style>
</head>
<body>
<h1>Welcome to nginx!</h1>
<p>If you see this page, nginx is successfully installed and working.
Further configuration is required for the web server, reverse proxy,
API gateway, load balancer, content cache, or other features.</p>

<p><em>Thank you for using nginx.</em></p>
</body>
</html>
```

## Explicación

Con `curl http://servidor-web` se realizó una solicitud HTTP desde el contenedor `cliente` hacia el contenedor `servidor-web`.

La respuesta obtenida fue la página HTML de bienvenida de Nginx. Esto confirma que ambos contenedores pudieron comunicarse correctamente dentro de la red `red-lab`.

También se comprobó que fue posible usar el nombre `servidor-web` en lugar de una dirección IP. Esto ocurre porque Docker proporciona resolución de nombres para los contenedores conectados a una misma red personalizada.

## Limpieza del ambiente

## Comandos ejecutados

```bash
docker stop servidor-web
docker rm servidor-web
docker rm cliente
docker network rm red-lab
```

## Resultado obtenido

```text
root@033bd7492376:/# exit
exit
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker stop servidor-web
servidor-web
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker rm servidor-web
servidor-web
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker rm cliente
cliente
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker network rm red-lab
red-lab
```

## Explicación

Después de finalizar la prueba, se salió del contenedor `cliente`, se detuvo el contenedor `servidor-web`, se eliminaron ambos contenedores y finalmente se eliminó la red `red-lab`.

Esto dejó limpio el ambiente para continuar con las siguientes partes del laboratorio.

## Reflexión

Los contenedores necesitan redes para comunicarse entre sí y con otros servicios. En esta parte, la red `red-lab` permitió que el contenedor `cliente` accediera al servidor Nginx ejecutado en el contenedor `servidor-web`.

Usar nombres de contenedor en lugar de direcciones IP es ventajoso porque los nombres son más fáciles de recordar y no dependen de una dirección que podría cambiar cuando se recrea un contenedor.

Publicar un puerto hacia el host y comunicarse dentro de una red Docker son operaciones distintas. Publicar un puerto permite acceder a un contenedor desde la máquina anfitriona, mientras que una red Docker permite la comunicación interna entre contenedores.

Un ejemplo real de uso sería una aplicación web conectada a una base de datos. Ambos servicios podrían estar en contenedores separados, pero conectados a una misma red Docker para comunicarse entre sí sin exponer todos sus puertos al host.

# Parte 13: Comunicación entre servicios

## Objetivo

Comprender cómo una aplicación o servicio puede comunicarse con otro contenedor dentro de una misma red Docker, sin exponer necesariamente el servicio hacia la máquina anfitriona.

## Comandos ejecutados

```bash
docker network create red-app
docker run -d --name redis-lab --network red-app redis
docker ps
docker run -it --name cliente-redis --network red-app redis redis-cli -h redis-lab
```

Dentro del cliente Redis se ejecutó:

```bash
ping
set curso IE0417
get curso
exit
```

Finalmente, se limpió el ambiente con:

```bash
docker stop redis-lab
docker rm redis-lab
docker rm cliente-redis
docker network rm red-app
```

## Creación de la red

## Comando ejecutado

```bash
docker network create red-app
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker network create red-app
f7aaa8ba88a9b4ed5e2c0bdd32bea7088480b67f69567d18dcb35545a00f24d7
```

## Explicación

Con este comando se creó una red personalizada llamada `red-app`. Esta red permitió conectar varios contenedores para que pudieran comunicarse entre sí usando sus nombres.

## Ejecución del contenedor Redis

## Comando ejecutado

```bash
docker run -d --name redis-lab --network red-app redis
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker run -d --name redis-lab --network red-app redis
Unable to find image 'redis:latest' locally
latest: Pulling from library/redis
66c3033571c5: Pull complete
0e422956e4a5: Pull complete
188c6fff82e6: Pull complete
39932f0416f7: Pull complete
4f4fb700ef54: Pull complete
c3fb1988805d: Pull complete
78c6b874f46d: Download complete
f62aa748d96d: Download complete
Digest: sha256:0c341492924cad6f5483f9133e43bd6c51ecdecbcadfac5b51657393b6a7936c
Status: Downloaded newer image for redis:latest
dce598711efa411df4f14894dda8cf2dbfb37bcde3d11f424ea1cded5bf81c6c
```

## Explicación

Con este comando se ejecutó un contenedor llamado `redis-lab` usando la imagen `redis`. El contenedor fue conectado a la red `red-app`.

Redis representa en este ejemplo un servicio externo con el que otra aplicación podría comunicarse. En un caso real, podría ser una base de datos, una caché o un servicio auxiliar.

Como la imagen `redis:latest` no estaba descargada localmente, Docker la obtuvo desde Docker Hub antes de iniciar el contenedor.

## Verificación del contenedor en ejecución

## Comando ejecutado

```bash
docker ps
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker ps
CONTAINER ID   IMAGE     COMMAND                  CREATED         STATUS         PORTS      NAMES
dce598711efa   redis     "docker-entrypoint.s…"   7 seconds ago   Up 6 seconds   6379/tcp   redis-lab
```

## Explicación

Con `docker ps` se verificó que el contenedor `redis-lab` estaba en ejecución. La salida muestra que Redis utiliza internamente el puerto `6379/tcp`, que es el puerto típico de este servicio.

## Ejecución del cliente Redis

## Comando ejecutado

```bash
docker run -it --name cliente-redis --network red-app redis redis-cli -h redis-lab
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker run -it --name cliente-redis --network red-app redis redis-cli -h redis-lab
redis-lab:6379>
```

## Explicación

Con este comando se creó un segundo contenedor llamado `cliente-redis`, conectado a la misma red `red-app`.

Este contenedor ejecutó directamente `redis-cli`, que es el cliente de línea de comandos de Redis. La opción `-h redis-lab` indicó que el cliente debía conectarse al servidor Redis llamado `redis-lab`.

La conexión funcionó porque ambos contenedores estaban en la misma red Docker.

## Prueba de conexión con Redis

## Comandos ejecutados dentro del cliente

```bash
ping
set curso IE0417
get curso
exit
```

## Resultado obtenido

```text
redis-lab:6379> ping
PONG
redis-lab:6379> set curso IE0417
OK
redis-lab:6379> get curso
"IE0417"
redis-lab:6379> exit
```

## Explicación

Con el comando `ping` se comprobó la conexión entre el cliente y el servidor Redis. La respuesta `PONG` indica que el servidor respondió correctamente.

Luego, con `set curso IE0417`, se guardó el valor `IE0417` asociado a la clave `curso`. La respuesta `OK` confirmó que el dato fue almacenado.

Finalmente, con `get curso`, se recuperó el valor guardado. La respuesta `"IE0417"` confirmó que el cliente pudo comunicarse correctamente con el servicio Redis dentro de la red Docker.

## Limpieza del ambiente

## Comandos ejecutados

```bash
docker stop redis-lab
docker rm redis-lab
docker rm cliente-redis
docker network rm red-app
```

## Resultado obtenido

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker stop redis-lab
redis-lab
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker rm redis-lab
redis-lab
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker rm cliente-redis
cliente-redis
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker network rm red-app
red-app
```

## Explicación

Después de finalizar la prueba, se detuvo y eliminó el contenedor `redis-lab`, se eliminó el contenedor `cliente-redis` y finalmente se eliminó la red `red-app`.

Esto permitió limpiar los recursos creados durante la práctica.

## Reflexión

Una aplicación web puede necesitar comunicarse con una base de datos, una caché u otro servicio para guardar, consultar o procesar información. En esta parte, Redis representó ese servicio externo.

Ambos contenedores debían estar en la misma red Docker para poder comunicarse usando el nombre `redis-lab`. Esto evita depender de direcciones IP internas que pueden cambiar cuando los contenedores se eliminan y se vuelven a crear.

Separar servicios en contenedores distintos permite organizar mejor una aplicación. Por ejemplo, una aplicación web puede ejecutarse en un contenedor y la base de datos en otro, manteniendo responsabilidades separadas.

La limitación de hacerlo manualmente con varios comandos `docker run` es que el proceso se vuelve repetitivo y propenso a errores cuando hay muchos servicios. En proyectos más grandes, herramientas como Docker Compose ayudan a definir redes, servicios y configuraciones en un solo archivo.