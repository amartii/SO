# Simulacro de Examen 5 - PRACTICO (programar codigo)

**Tiempo: 120 minutos | 3 problemas de C + 2 de shell | Se evalua codigo que compile y
maneje errores.**

A diferencia de los simulacros 1-4 (tipo test), este reproduce la parte de PROGRAMAR de la
asignatura, al estilo de las practicas reales (mycopy, searchstr, pipeline, photocol,
catlen). Intenta resolver cada problema en el tiempo indicado ANTES de mirar la solucion.

**Criterio de correccion (lo que puntua en cada ejercicio):**
- Compila sin warnings con `-Wall`.
- Comprueba el numero/validez de argumentos.
- Comprueba el retorno de TODAS las llamadas al sistema (perror + exit).
- El hijo siempre hace exit()/exec(); el padre siempre hace wait().
- Cierra los descriptores y extremos de pipe que no usa.

---

## Problema 1 (C, 25 min): wc propio con tres contadores

Escribe `micwc` que reciba un fichero y muestre el numero de **lineas, palabras y bytes**,
como `wc`. Usa `open`/`read` (no `fopen`). Una "palabra" es una secuencia de caracteres no
blancos separada por espacios, tabuladores o saltos de linea.

```
$ ./micwc /etc/hostname
   1   1   10 /etc/hostname
```

**Pistas:** lleva un flag `en_palabra`. Cuentas palabra cada vez que pasas de blanco a no
blanco. Cuenta '\n' para lineas y todos los bytes leidos para el total.

<details><summary>Solucion</summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define TAM 4096

int
main(int argc, char *argv[])
{
    int fd;
    char buf[TAM];
    ssize_t n;
    int i;
    long lineas = 0, palabras = 0, bytes = 0;
    int en_palabra = 0;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <fichero>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    while ((n = read(fd, buf, TAM)) > 0) {
        bytes += n;
        for (i = 0; i < n; i++) {
            if (buf[i] == '\n')
                lineas++;
            if (isspace((unsigned char)buf[i])) {
                en_palabra = 0;
            } else if (!en_palabra) {
                en_palabra = 1;
                palabras++;
            }
        }
    }
    if (n == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    close(fd);
    printf("%4ld %4ld %4ld %s\n", lineas, palabras, bytes, argv[1]);
    return 0;
}
```
**Por que asi:** el flag `en_palabra` evita contar varios espacios como varias palabras.
`isspace` cubre espacio, tab y newline.
</details>

---

## Problema 2 (C, 35 min): grep paralelo con fork+exec (estilo searchstr)

Escribe `pgrep_multi` que reciba **pares (patron, fichero)** y, por cada par, lance un
proceso hijo que ejecute `grep patron fichero`. Todos los grep corren en paralelo y el
padre espera a todos. Al final el padre imprime cuantos hijos terminaron con codigo 0
(es decir, cuantos ficheros contenian su patron).

```
$ ./pgrep_multi root /etc/passwd xyz /etc/passwd
... (salida de los grep) ...
Coincidencias en 1 de 2 ficheros
```

**Pistas:** valida que el numero de args (sin contar argv[0]) sea par y > 0. fork+execlp de
`grep`. En el padre, `wait(&status)` en bucle y cuenta los `WEXITSTATUS == 0`.

<details><summary>Solucion</summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int i;
    int total;
    int aciertos = 0;
    pid_t pid;
    int status;

    if (argc < 3 || (argc - 1) % 2 != 0) {
        fprintf(stderr, "usage: %s <patron> <fichero> [<patron> <fichero> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    total = (argc - 1) / 2;

    for (i = 1; i < argc; i += 2) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            execlp("grep", "grep", argv[i], argv[i + 1], (char *)NULL);
            perror("execlp");
            exit(2);                 /* exit != 0 y != 1 para distinguir fallo de exec */
        }
    }

    for (i = 0; i < total; i++) {
        if (wait(&status) > 0 && WIFEXITED(status) && WEXITSTATUS(status) == 0)
            aciertos++;
    }
    printf("Coincidencias en %d de %d ficheros\n", aciertos, total);
    return 0;
}
```
**Clave:** `grep` devuelve 0 si encontro coincidencias, 1 si no, 2 si hubo error. Por eso
el padre cuenta los `WEXITSTATUS == 0`.
</details>

---

## Problema 3 (C, 35 min): tuberia "comando1 | comando2" generica

Escribe `mipipe` que reciba **dos** comandos separados por la cadena `:` y los conecte por
una tuberia, como un `cmd1 | cmd2` del shell. Cada comando puede llevar argumentos.

```
$ ./mipipe ls -l : grep .c
# equivale a:  ls -l | grep .c
```

**Pistas:** localiza el `:` en argv para partir en dos vectores (acabados en NULL). Crea el
pipe, dos forks con dup2 (stdout del primero -> pipe, stdin del segundo <- pipe). El padre
cierra ambos extremos y hace dos wait.

<details><summary>Solucion</summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int i, sep = -1;
    int fd[2];
    pid_t p1, p2;

    /* localizar el separador ":" */
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], ":") == 0) {
            sep = i;
            break;
        }
    }
    if (sep < 2 || sep == argc - 1) {
        fprintf(stderr, "usage: %s cmd1 [args] : cmd2 [args]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    argv[sep] = NULL;                 /* corta el primer vector: argv[1..sep-1] */
    /* el segundo comando empieza en argv[sep+1] y ya acaba en el NULL de argv */

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    p1 = fork();
    if (p1 < 0) { perror("fork"); exit(EXIT_FAILURE); }
    if (p1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(argv[1], &argv[1]);
        perror("execvp cmd1");
        exit(EXIT_FAILURE);
    }

    p2 = fork();
    if (p2 < 0) { perror("fork"); exit(EXIT_FAILURE); }
    if (p2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(argv[sep + 1], &argv[sep + 1]);
        perror("execvp cmd2");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);                     /* el padre NO usa el pipe: cerrar ambos */
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
```
**Clave critica:** el padre DEBE cerrar `fd[0]` y `fd[1]`; si no, `cmd2` nunca recibe EOF
(queda un escritor abierto: el padre) y se cuelga. Poner `argv[sep] = NULL` convierte el
primer comando en un vector listo para `execvp`.
</details>

---

## Problema 4 (Shell, 20 min): organizar logs por fecha (estilo photocol/catlen)

Escribe `organizalogs.sh` que reciba un directorio. Para cada fichero `*.log` que contenga,
crea un subdirectorio con la fecha de modificacion del fichero (`AAAA-MM-DD`) y MUEVE el log
alli. Si dos logs son del mismo dia, van al mismo subdirectorio. No toques otros ficheros.

```
$ ./organizalogs.sh /var/midir
# crea /var/midir/2026-06-11/, etc. y mueve los .log dentro
```

**Pistas:** `date -r "$fich" +%F` da la fecha de modificacion en formato AAAA-MM-DD.
`mkdir -p`. Cuidado con que el patron `*.log` no haga match (comprueba `-f`).

<details><summary>Solucion</summary>

```sh
#!/bin/sh

if test $# -ne 1 || test ! -d "$1"
then
    echo "usage: $0 <directorio>" >&2
    exit 1
fi

dir="$1"

for fich in "$dir"/*.log
do
    test -f "$fich" || continue          # si no hay .log, el patron queda literal

    fecha=$(date -r "$fich" +%F)         # fecha de modificacion AAAA-MM-DD
    destino="$dir/$fecha"
    mkdir -p "$destino" || exit 1
    mv -- "$fich" "$destino/"
    echo "movido $(basename "$fich") -> $fecha/"
done
```
**Clave:** `test -f "$fich" || continue` evita procesar el patron literal cuando no hay
ningun `.log`. `date -r fichero +%F` lee la fecha de modificacion (mtime).
</details>

---

## Problema 5 (Shell, 25 min): informe de un CSV con awk

Tienes `notas.csv` con lineas `alumno,asignatura,nota`. Escribe `informe.sh` que reciba el
fichero e imprima, por asignatura: la media, la nota maxima y cuantos suspensos (nota < 5).
Ordena el informe por nombre de asignatura.

```
$ ./informe.sh notas.csv
SO        media=6.50 max=9.00 suspensos=2
Redes     media=7.20 max=8.50 suspensos=0
```

**Pistas:** un solo `awk -F,` con arrays asociativos indexados por `$2` (asignatura):
acumula suma, cuenta, maximo y suspensos; imprime en el bloque `END`; pasa por `sort`.

<details><summary>Solucion</summary>

```sh
#!/bin/sh

if test $# -ne 1 || test ! -f "$1"
then
    echo "usage: $0 <fichero.csv>" >&2
    exit 1
fi

awk -F, '
{
    asig = $2
    nota = $3
    suma[asig] += nota
    cuenta[asig]++
    if (nota > max[asig] || cuenta[asig] == 1)
        max[asig] = nota
    if (nota < 5)
        susp[asig]++
}
END {
    for (a in suma)
        printf "%-10s media=%.2f max=%.2f suspensos=%d\n", \
            a, suma[a] / cuenta[a], max[a], susp[a] + 0
}
' "$1" | sort
```
**Claves:** los arrays asociativos de awk (`suma[asig]`) agrupan por clave. `susp[a] + 0`
fuerza a 0 cuando no hubo suspensos (clave no creada). El `sort` final ordena por asignatura.
</details>

---

## Autoevaluacion

Por cada problema, puntua de 0 a 2:
- 0: no compila / no funciona.
- 1: funciona en el caso bueno pero no valida argumentos o no comprueba errores.
- 2: compila limpio, valida argumentos y comprueba retornos.

| Nota total | Valoracion |
|------------|------------|
| 9-10 | Listo para el examen practico |
| 6-8  | Repasa manejo de errores y cierre de descriptores |
| <6   | Vuelve a `ejercicios-practicos-c.md` y `ejercicios-practicos-shell.md` |
