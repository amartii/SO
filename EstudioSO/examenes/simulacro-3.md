# Simulacro de Examen 3 - Sistemas Operativos

**Formato fiel al examen real (TEST1): 17 preguntas tipo test con 5 opciones (a-e).**
**Tiempo: 75 minutos | No mirar las respuestas hasta terminar.**

> Preguntas nuevas inspiradas en el banco real de examenes (Popurri de examenes,
> `clase/apuntes`), con variaciones sobre los enunciados de 2015-2023. Una sola opcion
> correcta por pregunta.

---

### Pregunta 1
```c
int main(int argc, char *argv[]) {
    int i;
    for (i = 0; i < 6; i++) {
        if (i == 1)
            continue;
        if (i == 4)
            break;
        printf("%d", i);
    }
}
```
Que imprime?
- a) 0123
- b) 023
- c) 0234
- d) 01234
- e) 02

---

### Pregunta 2
```c
int arr[8];
int *p;
int i;
for (i = 0; i < 8; i++)
    arr[i] = i * 10;
p = arr + 3;
p = &(p[2]);
printf("%d\n", *p);
```
Que imprime?
- a) 30
- b) 50
- c) 60
- d) Un valor indeterminado
- e) No compila

---

### Pregunta 3
```c
char p[6] = "linux";
p[0] = 'L';
p[3] = 0;
printf("%zu\n", strlen(p));
```
Que imprime?
- a) 5
- b) 4
- c) 3
- d) 6
- e) No compila

---

### Pregunta 4
```c
char *crear(void) {
    char buf[64];
    snprintf(buf, sizeof(buf), "dato");
    return buf;
}
int main(void) { printf("%s\n", crear()); }
```
Que ocurre?
- a) Imprime "dato" siempre
- b) Comportamiento indefinido: se devuelve un puntero a variable local
- c) Error de compilacion seguro
- d) Fuga de memoria pero imprime bien
- e) Segmentation fault garantizado en todas las maquinas

---

### Pregunta 5
```c
int *v;
v = malloc(50 * sizeof(int));
if (v == NULL)
    err(1, "malloc");
memset(v, 0, sizeof(v));
```
Cuantos bytes inicializa el memset?
- a) 50
- b) 200
- c) 8 (en 64 bits)
- d) 50 * sizeof(int)
- e) 0, el memset no hace nada

---

### Pregunta 6
```c
Punto *new_punto(int x) {
    Punto *q = malloc(sizeof(Punto));
    q->x = x;
    return q;
}
int main(void) {
    Punto *s = new_punto(5);
    s = malloc(sizeof(Punto));
    printf("%d\n", s->x);
    free(s);
}
```
Cual es el problema principal?
- a) Es totalmente correcto
- b) Segmentation fault seguro
- c) Funciona, pero hay una fuga de memoria (la de new_punto)
- d) Doble free
- e) No compila

---

### Pregunta 7
```c
printf("X");
fork();
fork();
fork();
printf("Y");
```
Cuantas X y cuantas Y se imprimen (suponiendo stdout con buffer)?
- a) 1 X y 3 Y
- b) 1 X y 8 Y
- c) 8 X y 8 Y
- d) 1 X y 4 Y
- e) 4 X y 8 Y

---

### Pregunta 8
```c
int sts;
if (fork() == 0) {
    printf("hijo\n");
    exit(0);
} else {
    wait(&sts);
    printf("padre\n");
}
```
Sobre el orden de las dos lineas:
- a) Imprime las dos pero el orden no esta garantizado
- b) Siempre imprime "hijo" antes que "padre"
- c) Siempre imprime "padre" antes que "hijo"
- d) Solo imprime "padre"
- e) Solo imprime "hijo"

---

### Pregunta 9
```c
res = execv(cmd, argv);
if (res < 0)
    err(1, "exec fallo");
printf("exec ok\n");
```
Que ocurre con "exec ok"?
- a) Siempre se imprime
- b) Nunca se imprime
- c) Se imprime solo si exec tiene exito
- d) Se imprime una vez por cada argumento
- e) El codigo no compila

---

### Pregunta 10
```c
nw = write(fd, buf, N);
if (nw < 0)
    err(1, "write");
```
Sobre la comprobacion de error:
- a) Es perfecta, write siempre devuelve N o -1
- b) write puede devolver menos de N sin ser error; deberia tratarse ese caso
- c) La condicion deberia ser nw <= 0
- d) write nunca devuelve negativo
- e) Falta llamar a fork antes

---

### Pregunta 11
```c
int x = open("/tmp/datos", O_RDONLY);
if (x < 0) err(1, "open");
dup2(x, 0);
close(x);
execlp("wc", "wc", "-l", NULL);
```
Que hace si /tmp/datos existe?
- a) Lee del teclado y cuenta lineas
- b) Escribe en /tmp/datos el numero de lineas
- c) Escribe por stdout el numero de lineas de /tmp/datos
- d) Falla porque deberia ser execv
- e) Segmentation fault

---

### Pregunta 12
```c
f = fopen("/tmp/y", "w");
fprintf(f, "abc\n");
for (;;) { }
```
Que contiene /tmp/y mientras el bucle gira?
- a) "abc\n" (4 bytes)
- b) "abc" (3 bytes)
- c) Probablemente nada (sigue en el buffer)
- d) Error: no se puede abrir
- e) Basura

---

### Pregunta 13
```bash
$ rm -f /tmp/a
$ echo hola > /tmp/a
$ ln /tmp/a /tmp/b
$ rm /tmp/a
```
Tras el ultimo `rm`, el i-nodo original:
- a) Se borro, ya no existe
- b) Sigue existiendo con st_nlink = 2
- c) Sigue existiendo con st_nlink = 1 (a traves de /tmp/b)
- d) Queda como enlace simbolico roto
- e) Se borra el contenido pero queda el nombre

---

### Pregunta 14
```c
int fd[2];
char b[64 * 1024 * 1024];
pipe(fd);
write(fd[1], b, sizeof(b));
read(fd[0], b, sizeof(b));
```
Que ocurre (un solo proceso)?
- a) Funciona perfectamente
- b) SIGPIPE
- c) Se bloquea para siempre (deadlock)
- d) read devuelve 0
- e) Segmentation fault

---

### Pregunta 15
```bash
$ var=hola
$ sh
$ echo "$var"
```
Que imprime el ultimo echo?
- a) hola
- b) Una linea vacia (la variable no se exporto)
- c) $var
- d) Error de sintaxis
- e) El PID del shell

---

### Pregunta 16
Con paginacion bajo demanda (overcommit), un global `char a[8*1024*1024]` del que solo
se escribe `a[0]`. Cuantos marcos de pagina usa para ese dato?
- a) 2048
- b) 1
- c) 0
- d) 8388608
- e) 512

---

### Pregunta 17
```c
void incr(void) {
    if (x < MAX) {
        pthread_mutex_lock(&m);
        x++;
        pthread_mutex_unlock(&m);
    }
}
```
Varios hilos ejecutan incr(). Que afirmacion es cierta?
- a) Es correcto, x nunca supera MAX
- b) Hay condicion de carrera: x puede acabar mayor que MAX
- c) Hay un deadlock
- d) No compila por falta de init
- e) El lock sobra, x++ ya es atomico

---

# RESPUESTAS

1. **b) 023** — i=0 imprime 0; i=1 continue; i=2 imprime 2; i=3 imprime 3; i=4 break.
2. **b) 50** — p=arr+3 (apunta a arr[3]); p=&p[2] -> &arr[5]; *p = arr[5] = 50.
3. **c) 3** — "Linux" con p[3]=0 queda "Lin", strlen = 3.
4. **b) Comportamiento indefinido** — `buf` es local; al volver, su memoria deja de ser valida.
5. **c) 8 bytes** — `sizeof(v)` es el tamaño del puntero, no del bloque. Deberia ser 50*sizeof(int).
6. **c) Fuga de memoria** — el segundo malloc reasigna `s` sin liberar el bloque de new_punto.
7. **b) 1 X y 8 Y** — la X va antes del primer fork (1 vez). 3 forks -> 2^3 = 8 procesos -> 8 Y.
8. **b) Siempre hijo antes que padre** — `wait` bloquea al padre hasta que el hijo termina.
9. **b) Nunca se imprime** — si exec funciona, reemplaza el proceso; si falla, entra en el if y err() termina.
10. **b) Puede devolver menos de N sin ser error** — short write; solo -1 es error real.
11. **c) Escribe por stdout el numero de lineas de /tmp/datos** — dup2(x,0) redirige stdin al fichero; wc -l cuenta.
12. **c) Probablemente nada** — fprintf bufferiza; sin flush ni fin de programa no llega a disco.
13. **c) st_nlink = 1** — `ln` lo subio a 2; `rm /tmp/a` lo baja a 1; el i-nodo vive mientras nlink > 0.
14. **c) Deadlock** — el write llena el buffer del pipe (limitado) y se bloquea; el read nunca se alcanza.
15. **b) Linea vacia** — las variables de shell no se heredan sin `export`.
16. **b) 1 marco** — solo se asigna el marco de la pagina realmente accedida.
17. **b) Condicion de carrera** — el `if` esta FUERA del lock; varios hilos pueden pasarlo a la vez.
