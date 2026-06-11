# Ejercicios Practicos de C para Examen

Coleccion de ejercicios de **programar codigo** (no de test) seleccionados por ser los
que mas caen en examen y en las practicas reales. Cada ejercicio tiene enunciado,
pistas y una **solucion completa comentada**.

Intenta resolverlos en papel o en el editor ANTES de mirar la solucion. En examen
te van a pedir escribir codigo correcto con manejo de errores, asi que acostumbrate a
comprobar el retorno de cada llamada al sistema.

**Compilar:**
```bash
gcc -g -Wall -Wshadow -Wvla -o programa programa.c
# Con hilos:
gcc -g -Wall -o programa programa.c -lpthread
```

Indice:
1. Memoria dinamica: copiar y redimensionar un array
2. Strings: implementar mi_strtok / split
3. Ficheros (POSIX): copiar fichero con open/read/write
4. Ficheros: contar lineas de un fichero (como wc -l)
5. Ficheros: invertir un fichero con lseek
6. Procesos: lanzar N hijos y recoger su codigo de salida
7. Procesos: ejecutar un comando midiendo si fallo o exito
8. Pipes: padre escribe, hijo lee y transforma
9. Pipes + dup2: emular "cmd1 | cmd2"
10. Pipes + dup2: redirigir salida de un hijo a un fichero
11. Señales: contador de SIGINT con manejador
12. Señales: alarma / timeout de un proceso hijo
13. Concurrencia: condicion de carrera y su correccion con mutex
14. Concurrencia: productor/consumidor con semaforos
15. Mini-shell: leer linea, fork, exec

---

## Ejercicio 1: Redimensionar un array dinamico

**Enunciado:** Escribe una funcion `int *anadir(int *v, int *n, int valor)` que añada
`valor` al final de un array dinamico de `*n` enteros, incrementando `*n`. Devuelve el
nuevo puntero (puede cambiar tras realloc). En `main`, lee enteros de la entrada hasta
EOF y al final imprimelos.

**Pistas:**
- Usa `realloc(v, (*n + 1) * sizeof(int))`.
- `realloc` puede devolver NULL: guarda el resultado en una variable temporal antes de
  asignarlo, o perderas el bloque original.
- Comprueba siempre el retorno de `scanf`.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>

int *
anadir(int *v, int *n, int valor)
{
    int *tmp;

    tmp = realloc(v, (*n + 1) * sizeof(int));
    if (tmp == NULL) {
        perror("realloc");
        free(v);
        exit(EXIT_FAILURE);
    }
    tmp[*n] = valor;
    (*n)++;
    return tmp;
}

int
main(void)
{
    int *v = NULL;
    int n = 0;
    int x;
    int i;

    while (scanf("%d", &x) == 1)
        v = anadir(v, &n, x);

    for (i = 0; i < n; i++)
        printf("%d\n", v[i]);

    free(v);
    return 0;
}
```
**Claves de examen:** nunca hagas `v = realloc(v, ...)` directamente (si falla, fuga de
memoria). El array empieza en NULL y `realloc(NULL, ...)` se comporta como `malloc`.

---

## Ejercicio 2: Implementar un split de cadenas

**Enunciado:** Escribe un programa que reciba una cadena por argumento y un caracter
separador, e imprima cada trozo en una linea. No uses `strtok`; hazlo a mano con punteros.

```
$ ./split "uno,dos,tres" ,
uno
dos
tres
```

**Pistas:**
- Recorre con un puntero. Marca el inicio de cada trozo.
- Al encontrar el separador, imprime desde el inicio hasta ese punto y avanza.
- Cuidado con el ultimo trozo (no termina en separador, sino en '\0').

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    char *s;
    char sep;
    char *inicio;
    char *p;

    if (argc != 3 || strlen(argv[2]) != 1) {
        fprintf(stderr, "usage: %s <cadena> <separador>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    s = argv[1];
    sep = argv[2][0];

    inicio = s;
    for (p = s; *p != '\0'; p++) {
        if (*p == sep) {
            fwrite(inicio, 1, (size_t)(p - inicio), stdout);
            putchar('\n');
            inicio = p + 1;
        }
    }
    /* ultimo trozo */
    printf("%s\n", inicio);

    return 0;
}
```
**Clave:** `p - inicio` da la longitud del trozo. `fwrite` imprime exactamente esos bytes
sin necesitar un '\0'.

---

## Ejercicio 3: Copiar un fichero con llamadas POSIX (mycopy)

**Enunciado:** Reescribe `cp`. Recibe origen y destino, copia byte a byte usando
`open`, `read`, `write`, `close`. Crea el destino con permisos 0644. Es el ejercicio
mas tipico de practica.

**Pistas:**
- Origen: `open(orig, O_RDONLY)`.
- Destino: `open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644)`.
- Bucle: `while ((n = read(...)) > 0) write(...)`. Cuidado: write puede escribir menos.
- Comprueba TODOS los retornos.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TAM 4096

int
main(int argc, char *argv[])
{
    int fd_in, fd_out;
    char buf[TAM];
    ssize_t leidos, escritos, total;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <origen> <destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        perror("open origen");
        exit(EXIT_FAILURE);
    }
    fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1) {
        perror("open destino");
        exit(EXIT_FAILURE);
    }

    while ((leidos = read(fd_in, buf, TAM)) > 0) {
        total = 0;
        while (total < leidos) {
            escritos = write(fd_out, buf + total, (size_t)(leidos - total));
            if (escritos == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            total += escritos;
        }
    }
    if (leidos == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    close(fd_in);
    close(fd_out);
    return 0;
}
```
**Clave:** `read` devuelve 0 en EOF, >0 con los bytes leidos, -1 en error. `write` puede
hacer un "short write": por eso el bucle interno repite hasta escribir todo lo leido.

---

## Ejercicio 4: Contar lineas (mi wc -l)

**Enunciado:** Cuenta los saltos de linea de un fichero pasado por argumento, usando
`read` con buffer. Imprime el numero.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TAM 4096

int
main(int argc, char *argv[])
{
    int fd;
    char buf[TAM];
    ssize_t n;
    long lineas = 0;
    int i;

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
        for (i = 0; i < n; i++) {
            if (buf[i] == '\n')
                lineas++;
        }
    }
    if (n == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    close(fd);
    printf("%ld\n", lineas);
    return 0;
}
```
**Clave:** contar '\n', no caracteres. Si el fichero no termina en '\n', la ultima linea
no se cuenta (igual que el `wc -l` real).

---

## Ejercicio 5: Tamaño de fichero con lseek

**Enunciado:** Sin usar `stat`, calcula el tamaño de un fichero. Pista: `lseek` al final
devuelve el offset, que es el tamaño.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int fd;
    off_t tam;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <fichero>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    tam = lseek(fd, 0, SEEK_END);
    if (tam == (off_t)-1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    close(fd);
    printf("%lld bytes\n", (long long)tam);
    return 0;
}
```
**Clave:** `SEEK_END` con offset 0 posiciona al final; el valor devuelto es el tamaño.
`SEEK_SET` = inicio, `SEEK_CUR` = posicion actual.

---

## Ejercicio 6: Lanzar N hijos y recoger su codigo de salida

**Enunciado:** Recibe N por argumento. Lanza N hijos. El hijo i hace `exit(i)`. El padre
espera a todos e imprime el PID y el codigo de salida de cada uno.

**Pistas:**
- El hijo SIEMPRE debe hacer `exit()` para no seguir el bucle del padre.
- `wait(&status)` y `WEXITSTATUS(status)`.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int n, i;
    pid_t pid;
    int status;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    n = atoi(argv[1]);

    for (i = 0; i < n; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            printf("Hijo %d, PID=%d\n", i, getpid());
            exit(i);                /* imprescindible: corta el bucle en el hijo */
        }
    }

    for (i = 0; i < n; i++) {
        pid = wait(&status);
        if (pid > 0 && WIFEXITED(status))
            printf("Hijo PID=%d termino con codigo %d\n", pid, WEXITSTATUS(status));
    }
    return 0;
}
```
**Clave de examen:** sin el `exit(i)` del hijo, cada hijo continuaria el bucle `for` y
crearia mas hijos -> explosion exponencial de procesos.

---

## Ejercicio 7: Ejecutar un comando y reportar si fallo

**Enunciado:** Recibe un comando con sus argumentos (`./run ls -l /tmp`). Hazle fork+exec
y reporta si el comando termino bien (codigo 0), con error (codigo != 0) o por una señal.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    pid_t pid;
    int status;

    if (argc < 2) {
        fprintf(stderr, "usage: %s comando [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        execvp(argv[1], &argv[1]);   /* &argv[1] es el array de args ya con NULL al final */
        perror("execvp");
        exit(127);                   /* solo se llega aqui si exec falla */
    }

    if (wait(&status) == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status))
        printf("Termino normal, codigo %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("Terminado por señal %d\n", WTERMSIG(status));

    return 0;
}
```
**Clave:** `execvp` recibe un array de argumentos terminado en NULL; `argv` ya lo esta,
asi que `&argv[1]` sirve directamente. Tras un exec con exito NO se vuelve.

---

## Ejercicio 8: Padre escribe, hijo lee del pipe

**Enunciado:** El padre escribe una linea de texto en un pipe; el hijo la lee y la
imprime en mayusculas.

**Pistas:**
- Crea el pipe ANTES del fork.
- Cierra el extremo que no usas en cada proceso.
- El hijo detecta EOF (read devuelve 0) cuando el padre cierra el extremo de escritura.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

int
main(void)
{
    int fd[2];
    pid_t pid;
    const char *msg = "hola mundo\n";
    char buf[256];
    ssize_t n;
    int i;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* hijo: lee */
        close(fd[1]);
        while ((n = read(fd[0], buf, sizeof(buf))) > 0) {
            for (i = 0; i < n; i++)
                putchar(toupper((unsigned char)buf[i]));
        }
        close(fd[0]);
        exit(EXIT_SUCCESS);
    }

    /* padre: escribe */
    close(fd[0]);
    write(fd[1], msg, 11);
    close(fd[1]);              /* cerrar provoca el EOF en el hijo */
    wait(NULL);
    return 0;
}
```
**Clave:** si el padre no cierra `fd[1]`, el hijo se queda bloqueado en `read` esperando
mas datos para siempre. El cierre de TODOS los escritores genera el EOF.

---

## Ejercicio 9: Emular "cmd1 | cmd2" (ej: ls | sort)

**Enunciado:** Implementa una tuberia entre dos comandos fijos: `ls | sort`. Usa pipe,
dos forks y dup2.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(void)
{
    int fd[2];
    pid_t p1, p2;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    p1 = fork();
    if (p1 == 0) {
        /* escribe en el pipe -> su stdout es fd[1] */
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    p2 = fork();
    if (p2 == 0) {
        /* lee del pipe -> su stdin es fd[0] */
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("sort", "sort", (char *)NULL);
        perror("execlp sort");
        exit(EXIT_FAILURE);
    }

    /* el padre NO usa el pipe: debe cerrar ambos extremos */
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
```
**Clave critica:** el padre tiene que cerrar `fd[0]` y `fd[1]`. Si no lo hace, `sort`
nunca recibe EOF (sigue habiendo un escritor abierto: el padre) y se cuelga.

---

## Ejercicio 10: Redirigir la salida de un hijo a un fichero (como ">")

**Enunciado:** Lanza `date` pero con su salida estandar redirigida a un fichero
`salida.txt`. Equivale a `date > salida.txt`.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(void)
{
    pid_t pid;
    int fd;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        fd = open("salida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);   /* stdout ahora apunta al fichero */
        close(fd);
        execlp("date", "date", (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    return 0;
}
```
**Clave:** `dup2(fd, 1)` hace que el descriptor 1 (stdout) sea una copia de `fd`. Tras eso
`fd` ya no se necesita y se cierra. El comando ejecutado no sabe que escribe a un fichero.

---

## Ejercicio 11: Contar pulsaciones de Ctrl+C (SIGINT)

**Enunciado:** Captura SIGINT. Cada vez que llega, incrementa un contador e imprime
cuantas van. Al recibir SIGTERM, imprime el total y termina.

**Pistas:**
- La variable del contador debe ser `volatile sig_atomic_t`.
- Usa `sigaction` (preferible a `signal`).
- En el manejador solo haz lo minimo (incrementar / write).

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static volatile sig_atomic_t contador = 0;
static volatile sig_atomic_t fin = 0;

static void
manejador_int(int sig)
{
    (void)sig;
    contador++;
}

static void
manejador_term(int sig)
{
    (void)sig;
    fin = 1;
}

int
main(void)
{
    struct sigaction sa;

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sa.sa_handler = manejador_int;
    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = manejador_term;
    sigaction(SIGTERM, &sa, NULL);

    printf("Pulsa Ctrl+C varias veces. Mata con: kill %d\n", getpid());
    while (!fin)
        pause();                 /* duerme hasta que llegue una señal */

    printf("\nTotal de SIGINT recibidas: %d\n", contador);
    return 0;
}
```
**Clave:** `sig_atomic_t volatile` evita problemas de concurrencia entre el flujo normal y
el manejador. `pause()` despierta con cada señal. SIGKILL/SIGSTOP no se pueden capturar.

---

## Ejercicio 12: Timeout de un proceso hijo con alarm

**Enunciado:** Lanza un comando (fork+exec). Si tarda mas de N segundos, el padre lo mata
con SIGKILL. Equivale a un `timeout N comando`.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    unsigned segundos;

    if (argc < 3) {
        fprintf(stderr, "usage: %s <segundos> comando [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    segundos = (unsigned)atoi(argv[1]);

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        execvp(argv[2], &argv[2]);
        perror("execvp");
        exit(127);
    }

    /* padre: arma alarma; si vence antes del wait, mata al hijo */
    alarm(segundos);
    if (waitpid(pid, &status, 0) == -1) {
        /* alarm interrumpio el wait con SIGALRM (no manejada -> mataria al padre)
           Mejor: usar manejador. Version simple a continuacion. */
    }
    return 0;
}
```
**Version robusta con manejador de SIGALRM:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

static pid_t hijo;

static void
on_alarm(int sig)
{
    (void)sig;
    kill(hijo, SIGKILL);
}

int
main(int argc, char *argv[])
{
    int status;
    struct sigaction sa;

    if (argc < 3) {
        fprintf(stderr, "usage: %s <segundos> comando [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    hijo = fork();
    if (hijo < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (hijo == 0) {
        execvp(argv[2], &argv[2]);
        perror("execvp");
        exit(127);
    }

    sa.sa_handler = on_alarm;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);
    alarm((unsigned)atoi(argv[1]));

    waitpid(hijo, &status, 0);
    if (WIFSIGNALED(status))
        printf("El comando fue terminado (timeout)\n");
    else
        printf("El comando termino a tiempo, codigo %d\n", WEXITSTATUS(status));
    return 0;
}
```
**Clave:** `alarm(n)` envia SIGALRM tras n segundos. El manejador mata al hijo. Si el hijo
acaba antes, `waitpid` retorna y la alarma pendiente no hace daño (o se cancela con
`alarm(0)`).

---

## Ejercicio 13: Condicion de carrera y su correccion

**Enunciado:** Tienes un contador global que 4 hilos incrementan 100000 veces cada uno. Sin
proteccion el resultado es erroneo. Corrigelo con un mutex y comprueba que da 400000.

**Solucion (correcta, con mutex):**
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define HILOS 4
#define VECES 100000

static long contador = 0;
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

static void *
trabajo(void *arg)
{
    int i;
    (void)arg;
    for (i = 0; i < VECES; i++) {
        pthread_mutex_lock(&m);
        contador++;                 /* la seccion critica completa va dentro del lock */
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int
main(void)
{
    pthread_t t[HILOS];
    int i;

    for (i = 0; i < HILOS; i++)
        pthread_create(&t[i], NULL, trabajo, NULL);
    for (i = 0; i < HILOS; i++)
        pthread_join(t[i], NULL);

    printf("contador = %ld (esperado %d)\n", contador, HILOS * VECES);
    return 0;
}
```
**Clave de examen:** `contador++` NO es atomico (load, add, store). Sin mutex dos hilos
pueden leer el mismo valor y perder incrementos. La regla de oro: si compruebas o modificas
un recurso compartido, hazlo TODO dentro del lock.

---

## Ejercicio 14: Productor/consumidor con semaforos

**Enunciado:** Un productor mete numeros 1..10 en un buffer circular de tamaño 4; un
consumidor los saca y suma. Usa semaforos para vacios/llenos y un mutex para el buffer.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 4
#define ITEMS 10

static int buffer[N];
static int in = 0, out = 0;
static sem_t vacios;      /* huecos libres */
static sem_t llenos;      /* elementos disponibles */
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

static void *
productor(void *arg)
{
    int i;
    (void)arg;
    for (i = 1; i <= ITEMS; i++) {
        sem_wait(&vacios);
        pthread_mutex_lock(&m);
        buffer[in] = i;
        in = (in + 1) % N;
        pthread_mutex_unlock(&m);
        sem_post(&llenos);
    }
    return NULL;
}

static void *
consumidor(void *arg)
{
    int i, x;
    long suma = 0;
    (void)arg;
    for (i = 0; i < ITEMS; i++) {
        sem_wait(&llenos);
        pthread_mutex_lock(&m);
        x = buffer[out];
        out = (out + 1) % N;
        pthread_mutex_unlock(&m);
        sem_post(&vacios);
        suma += x;
    }
    printf("suma = %ld (esperado 55)\n", suma);
    return NULL;
}

int
main(void)
{
    pthread_t tp, tc;

    sem_init(&vacios, 0, N);   /* al principio hay N huecos */
    sem_init(&llenos, 0, 0);   /* y 0 elementos */

    pthread_create(&tp, NULL, productor, NULL);
    pthread_create(&tc, NULL, consumidor, NULL);
    pthread_join(tp, NULL);
    pthread_join(tc, NULL);

    sem_destroy(&vacios);
    sem_destroy(&llenos);
    return 0;
}
```
Compila con `-lpthread`.
**Clave:** dos semaforos contador (huecos y elementos) + un mutex que protege los indices.
`sem_wait` baja (bloquea si 0), `sem_post` sube.

---

## Ejercicio 15: Mini-shell (leer linea, fork, exec)

**Enunciado:** Lee comandos de la entrada, uno por linea, y ejecutalos (sin pipes ni
redirecciones). Termina con `exit` o EOF. Es la sintesis de fork+exec+wait.

**Solucion:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARGS 64

int
main(void)
{
    char linea[1024];
    char *args[MAXARGS];
    int n;
    char *tok;
    pid_t pid;

    while (1) {
        printf("$ ");
        fflush(stdout);
        if (fgets(linea, sizeof(linea), stdin) == NULL)
            break;                       /* EOF (Ctrl+D) */
        linea[strcspn(linea, "\n")] = '\0';

        /* trocear en palabras */
        n = 0;
        tok = strtok(linea, " \t");
        while (tok != NULL && n < MAXARGS - 1) {
            args[n++] = tok;
            tok = strtok(NULL, " \t");
        }
        args[n] = NULL;
        if (n == 0)
            continue;
        if (strcmp(args[0], "exit") == 0)
            break;

        pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(127);
        }
        wait(NULL);
    }
    return 0;
}
```
**Clave:** `execvp` busca el ejecutable en el PATH. El array de args debe terminar en NULL.
`strcspn(linea, "\n")` sirve para quitar el salto de linea que deja `fgets`.

---

## Tabla rapida de valores de retorno (memorizar)

| Llamada | Exito | EOF / fin | Error |
|---------|-------|-----------|-------|
| `fork()` | PID hijo (padre), 0 (hijo) | - | -1 |
| `read()` | nº bytes (>0) | 0 | -1 |
| `write()` | nº bytes escritos | - | -1 |
| `open()` | descriptor (>=0) | - | -1 |
| `wait()` | PID del hijo | - | -1 |
| `exec*()` | NO retorna | - | -1 |
| `malloc()` | puntero | - | NULL |
| `pipe()` | 0 | - | -1 |

Regla: comprueba SIEMPRE el retorno y usa `perror` + `exit(EXIT_FAILURE)` en error.
