# Parte 3: Imágenes y contenedores

## Objetivo

Comprender la diferencia entre una imagen y un contenedor mediante el uso de una imagen de Ubuntu descargada desde Docker Hub.

## Comandos ejecutados

```bash
docker pull ubuntu
docker images
docker run -it ubuntu bash
```

Dentro del contenedor se ejecutaron los siguientes comandos:

```bash
ls
pwd
cat /etc/os-release
exit
```

Después de salir del contenedor, se ejecutó:

```bash
docker ps -a
```

## Resultado de `docker pull ubuntu`

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker pull ubuntu
Using default tag: latest
latest: Pulling from library/ubuntu
1c24335ddd46: Pull complete
6f5c5aa4e145: Pull complete
9bcf140d7f0f: Download complete
Digest: sha256:f3d28607ddd78734bb7f71f117f3c6706c666b8b76cbff7c9ff6e5718d46ff64
Status: Downloaded newer image for ubuntu:latest
docker.io/library/ubuntu:latest
```

## Explicación de `docker pull`

Con el comando `docker pull ubuntu` se descargó la imagen de Ubuntu desde Docker Hub. Como no se especificó una etiqueta particular, Docker utilizó la etiqueta por defecto `latest`.

Una imagen en Docker funciona como una plantilla que contiene el sistema de archivos y las dependencias necesarias para crear contenedores. En este caso, la imagen descargada corresponde a Ubuntu.

## Resultado de `docker images`

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker images
                                                                             i Info →   U  In Use
IMAGE                ID             DISK USAGE   CONTENT SIZE   EXTRA
hello-world:latest   0e760fdfbc48       25.9kB         9.49kB    U
ubuntu:latest        f3d28607ddd7        160MB         45.3MB
```

## Explicación de `docker images`

Con el comando `docker images` se listaron las imágenes disponibles localmente en el sistema. En la salida aparecen las imágenes `hello-world:latest` y `ubuntu:latest`.

Esto indica que ambas imágenes ya están disponibles en el ambiente local de Docker y pueden utilizarse para crear contenedores sin necesidad de descargarlas nuevamente, salvo que se requiera una versión más reciente.

## Resultado de `docker run -it ubuntu bash`

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker run -it ubuntu bash
root@0d12dbb5b84f:/#
```

## Explicación del modo interactivo

Con el comando `docker run -it ubuntu bash` se creó y ejecutó un contenedor a partir de la imagen `ubuntu`.

La opción `-it` permite ejecutar el contenedor en modo interactivo. Esto significa que se puede escribir comandos dentro del contenedor desde la terminal. Además, se ejecutó `bash`, por lo que se abrió una consola dentro del entorno del contenedor.

El cambio en el prompt a `root@0d12dbb5b84f:/#` indica que la terminal ya no estaba en el sistema anfitrión, sino dentro del contenedor de Ubuntu.

## Comandos ejecutados dentro del contenedor

### Resultado de `ls`

```text
root@0d12dbb5b84f:/# ls
bin   dev  home  lib64  mnt  proc  run   srv  tmp  var
boot  etc  lib   media  opt  root  sbin  sys  usr
```

Con el comando `ls` se listó el contenido del directorio raíz del contenedor. Se observaron carpetas típicas de un sistema Linux, como `bin`, `etc`, `home`, `usr`, `var` y `root`.

### Resultado de `pwd`

```text
root@0d12dbb5b84f:/# pwd
/
```

Con el comando `pwd` se verificó que el directorio actual dentro del contenedor era `/`, es decir, el directorio raíz.

### Resultado de `cat /etc/os-release`

```text
root@0d12dbb5b84f:/# cat /etc/os-release
PRETTY_NAME="Ubuntu 26.04 LTS"
NAME="Ubuntu"
VERSION_ID="26.04"
VERSION="26.04 (Resolute Raccoon)"
VERSION_CODENAME=resolute
ID=ubuntu
ID_LIKE=debian
HOME_URL="https://www.ubuntu.com/"
SUPPORT_URL="https://help.ubuntu.com/"
BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
UBUNTU_CODENAME=resolute
LOGO=ubuntu-logo
```

Con este comando se revisó la información del sistema operativo disponible dentro del contenedor. Se observó que el contenedor utiliza Ubuntu 26.04 LTS.

## Salida del contenedor

```text
root@0d12dbb5b84f:/# exit
exit
```

Con el comando `exit` se salió de la terminal interactiva del contenedor. Al salir, el proceso principal del contenedor terminó, porque en este caso el proceso principal era `bash`.

## Resultado de `docker ps -a`

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker ps -a
CONTAINER ID   IMAGE         COMMAND    CREATED         STATUS                      PORTS     NAMES
0d12dbb5b84f   ubuntu        "bash"     8 minutes ago   Exited (0) 11 seconds ago             awesome_elion
9701e13e739d   hello-world   "/hello"   3 hours ago     Exited (0) 3 hours ago                eloquent_agnesi
cbf788acd21c   hello-world   "/hello"   4 hours ago     Exited (0) 4 hours ago                unruffled_brahmagupta
```

## Explicación de `docker ps -a`

Con el comando `docker ps -a` se listaron todos los contenedores existentes, incluyendo los que ya estaban detenidos.

En la salida aparece el contenedor creado a partir de la imagen `ubuntu`, con el comando `"bash"` y el estado `Exited (0)`. Esto indica que el contenedor finalizó correctamente después de salir de la consola interactiva.

También se observan los contenedores anteriores creados a partir de la imagen `hello-world`.

## Diferencia entre imagen y contenedor

Una imagen es una plantilla inmutable que contiene los archivos y configuraciones necesarios para crear contenedores. Por ejemplo, `ubuntu:latest` es una imagen.

Un contenedor es una instancia creada a partir de una imagen. En este caso, el contenedor con ID `0d12dbb5b84f` fue creado a partir de la imagen `ubuntu`.

Por eso, una misma imagen puede utilizarse para crear varios contenedores diferentes.

## Observaciones dentro del contenedor Ubuntu

Dentro del contenedor se observó un entorno similar a un sistema Linux tradicional. Se podían ejecutar comandos como `ls`, `pwd` y `cat`, y existían directorios típicos como `/bin`, `/etc`, `/usr` y `/var`.

Sin embargo, esto no significa que se haya ejecutado una máquina virtual completa. El contenedor proporciona un entorno aislado de usuario, pero comparte el kernel con el sistema anfitrión mediante Docker Desktop y WSL2.

## Reflexión

La imagen de Ubuntu en Docker no es lo mismo que una máquina virtual Ubuntu. La imagen funciona como una plantilla para crear contenedores, mientras que una máquina virtual ejecuta un sistema operativo completo con su propio kernel.

El contenedor puede parecer un sistema Linux porque incluye directorios, archivos de configuración y herramientas comunes como `bash`, `ls` y `cat`. Sin embargo, no es una máquina virtual completa, ya que comparte el kernel con el sistema anfitrión.

Que el contenedor comparta el kernel con el host significa que no ejecuta un kernel propio. Esto hace que los contenedores sean más ligeros y rápidos que las máquinas virtuales.

Finalmente, una imagen descargada permanece almacenada localmente y puede usarse varias veces. En cambio, un contenedor es una instancia concreta creada a partir de esa imagen, con su propio estado y ciclo de vida.

## Parte 4: Administración básica de contenedores
## Administración de contenedores

## Objetivo

Aprender a crear, nombrar, detener, iniciar, acceder y eliminar contenedores usando comandos básicos de administración en Docker.

## Comandos ejecutados

```bash
docker run -it --name mi-ubuntu ubuntu bash
```

Dentro del contenedor se ejecutó:

```bash
echo "Hola desde el contenedor" > mensaje.txt
cat mensaje.txt
exit
```

Luego, desde la terminal del sistema anfitrión, se ejecutó:

```bash
docker ps -a
docker start mi-ubuntu
docker exec -it mi-ubuntu bash
```

Dentro del contenedor reiniciado se ejecutó:

```bash
cat mensaje.txt
exit
```

Finalmente, desde el sistema anfitrión, se ejecutó:

```bash
docker stop mi-ubuntu
docker rm mi-ubuntu
docker ps -a
```

## Resultado de creación del contenedor con nombre

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker run -it --name mi-ubuntu ubuntu bash
root@978461f4bb69:/# echo "Hola desde el contenedor" > mensaje.txt
root@978461f4bb69:/# cat mensaje.txt
Hola desde el contenedor
root@978461f4bb69:/# exit
exit
```

## Explicación de `--name`

Con la opción `--name mi-ubuntu` se asignó un nombre específico al contenedor. Esto permite administrarlo de forma más clara, ya que se puede hacer referencia al contenedor usando `mi-ubuntu` en lugar de usar su ID.

En este caso, el contenedor fue creado a partir de la imagen `ubuntu` y se abrió una terminal interactiva con `bash`.

Dentro del contenedor se creó el archivo `mensaje.txt` con el contenido `Hola desde el contenedor`. Luego, con `cat mensaje.txt`, se verificó que el archivo existía y que el contenido había sido guardado correctamente.

## Resultado de `docker ps -a`

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker ps -a
CONTAINER ID   IMAGE         COMMAND    CREATED          STATUS                     PORTS     NAMES
978461f4bb69   ubuntu        "bash"     38 seconds ago   Exited (0) 9 seconds ago             mi-ubuntu
0d12dbb5b84f   ubuntu        "bash"     15 minutes ago   Exited (0) 7 minutes ago             awesome_elion
9701e13e739d   hello-world   "/hello"   3 hours ago      Exited (0) 3 hours ago               eloquent_agnesi
cbf788acd21c   hello-world   "/hello"   4 hours ago      Exited (0) 4 hours ago               unruffled_brahmagupta
```

## Explicación de `docker ps -a`

Con el comando `docker ps -a` se verificó que el contenedor `mi-ubuntu` existía, aunque ya no estaba en ejecución. El estado `Exited (0)` indica que el proceso principal del contenedor terminó correctamente después de salir de la consola con `exit`.

## Resultado de reinicio y acceso al contenedor

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker start mi-ubuntu
mi-ubuntu
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker exec -it mi-ubuntu bash
root@978461f4bb69:/# cat mensaje.txt
Hola desde el contenedor
root@978461f4bb69:/# exit
exit
```

## Diferencia entre `docker start` y `docker run`

El comando `docker run` crea un contenedor nuevo a partir de una imagen y lo ejecuta. En cambio, `docker start` inicia un contenedor que ya existe previamente.

En este caso, no se creó otro contenedor nuevo, sino que se reinició el contenedor llamado `mi-ubuntu`.

## Uso de `docker exec`

El comando `docker exec -it mi-ubuntu bash` permitió entrar a un contenedor que ya estaba en ejecución. La opción `-it` permitió interactuar con la terminal del contenedor, y `bash` indicó que se quería abrir una consola dentro de él.

Al ingresar nuevamente al contenedor, se ejecutó `cat mensaje.txt` y se verificó que el archivo creado anteriormente seguía existiendo. Esto ocurrió porque el contenedor no había sido eliminado, solamente se había detenido al salir de la consola.

## Resultado de detener y eliminar el contenedor

```text
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker stop mi-ubuntu
mi-ubuntu
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker rm mi-ubuntu
mi-ubuntu
raul@PC-Giorgio:~/bretes_raul/IE-0417/laboratorio-contenedores$ docker ps -a
CONTAINER ID   IMAGE         COMMAND    CREATED          STATUS                     PORTS     NAMES
0d12dbb5b84f   ubuntu        "bash"     17 minutes ago   Exited (0) 8 minutes ago             awesome_elion
9701e13e739d   hello-world   "/hello"   3 hours ago      Exited (0) 3 hours ago               eloquent_agnesi
cbf788acd21c   hello-world   "/hello"   4 hours ago      Exited (0) 4 hours ago               unruffled_brahmagupta
```

## Diferencia entre detener y eliminar un contenedor

Detener un contenedor significa parar su ejecución, pero mantenerlo existente en el sistema. Por eso, después de detenerlo, todavía puede reiniciarse con `docker start`.

Eliminar un contenedor significa borrar esa instancia del sistema Docker. Después de ejecutar `docker rm mi-ubuntu`, el contenedor dejó de aparecer en `docker ps -a`.

## ¿Qué pasó con el archivo creado dentro del contenedor?

El archivo `mensaje.txt` permaneció dentro del contenedor mientras este no fue eliminado. Esto se comprobó al reiniciar `mi-ubuntu` y acceder nuevamente con `docker exec`.

Sin embargo, al eliminar el contenedor con `docker rm mi-ubuntu`, también se eliminó el sistema de archivos propio de ese contenedor. Por lo tanto, el archivo creado dentro de él ya no se conserva en esa instancia.

## Reflexión

Asignar nombres a los contenedores facilita su administración, porque permite usar comandos como `docker start mi-ubuntu`, `docker stop mi-ubuntu` o `docker rm mi-ubuntu` sin depender del ID del contenedor.

Crear un contenedor nuevo no es lo mismo que reiniciar uno existente. Con `docker run` se crea una nueva instancia a partir de una imagen, mientras que con `docker start` se vuelve a iniciar un contenedor que ya existía.

Los datos creados dentro del contenedor se conservan mientras el contenedor exista. Sin embargo, si el contenedor se elimina, esos datos también se pierden, a menos que se haya usado un volumen o un bind mount.

Por eso se dice que los contenedores son desechables: pueden crearse, detenerse, eliminarse y volver a generarse fácilmente desde una imagen. En una aplicación real, el contenedor no debería ser el lugar principal para guardar información importante.