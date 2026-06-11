# Simulacro de Examen 4 - Sistemas Operativos

**Formato fiel al examen real (TEST1): 17 preguntas tipo test con 5 opciones (a-e).**
**Tiempo: 75 minutos | No mirar las respuestas hasta terminar.**

> Este simulacro carga el peso en los temas de la segunda mitad (señales, planificacion,
> concurrencia, ELF, sistemas de ficheros, memoria virtual), tambien presentes en el banco
> real (`clase/apuntes`). Una sola opcion correcta.

---

### Pregunta 1
```c
int a, b;
a = 3;
b = ++a;
b -= 2;
a = b++;
printf("%d %d\n", a, b);
```
Que imprime?
- [ ] a) 2 3
- [ ] b) 1 2
- [ ] c) 4 5
- [ ] d) 2 2
- [ ] e) 3 4

---

### Pregunta 2
Que hace el operador `->` en C?
- [ ] a) Suma 1 a un puntero
- [ ] b) Atraviesa un puntero y accede al campo de un registro (struct)
- [ ] c) Accede al indice de un array a traves de un puntero
- [ ] d) Solo funciona sobre punteros a entero
- [ ] e) Es lo mismo que el operador `&`

---

### Pregunta 3
```c
void *p;
char *s;
int i;
p = malloc(100 * sizeof(char *));
s = (char *)p;
for (i = 0; i < 100; i++)
    s[i] = 'c';
```
Sobre esta reserva:
- [ ] a) Es exacta: reserva justo 100 bytes
- [ ] b) Compila y puede ejecutar, pero reserva mas memoria de la necesaria
- [ ] c) Error de tipos en el cast
- [ ] d) No compila
- [ ] e) Provoca SIGSEGV en el bucle

---

### Pregunta 4
```c
for (i = 0; i < 3; i++)
    fork();
fprintf(stderr, "hola\n");
```
Cuantas lineas "hola" se escriben y por que salida?
- [ ] a) 3, por stdout
- [ ] b) 3, por stderr
- [ ] c) 8, por stderr
- [ ] d) 8, por stdout
- [ ] e) 4, por stderr

---

### Pregunta 5
```c
void f(void) {
    fork();
    fork();
    printf("%d\n", getppid());
}
```
Que se puede afirmar de los 4 numeros impresos?
- [ ] a) Siempre los 4 distintos
- [ ] b) Siempre los 4 iguales
- [ ] c) Siempre dos iguales y dos distintos (hermanos comparten padre)
- [ ] d) Siempre en el mismo orden
- [ ] e) Solo imprime 3 numeros

---

### Pregunta 6
La señal SIGKILL (9):
- [ ] a) Mata el proceso pero se puede ignorar con signal()
- [ ] b) Es la que envia Ctrl+C
- [ ] c) No se puede capturar ni ignorar, y no es Ctrl+C
- [ ] d) Solo detiene temporalmente el proceso
- [ ] e) Equivale a Ctrl+Z

---

### Pregunta 7
La mascara de señales de un proceso indica:
- [ ] a) Las señales que el proceso ignora
- [ ] b) Los manejadores instalados
- [ ] c) Las señales que tiene bloqueadas (quedan pendientes)
- [ ] d) La tabla de descriptores de fichero
- [ ] e) Las señales ya entregadas

---

### Pregunta 8
Al escribir con write en un pipe cuyo extremo de lectura NO tiene ningun proceso abierto:
- [ ] a) write devuelve 0
- [ ] b) El proceso recibe SIGPIPE
- [ ] c) Se bloquea para siempre
- [ ] d) Los datos se escriben igualmente
- [ ] e) write devuelve los bytes pero se pierden

---

### Pregunta 9
En un planificador Round-Robin, si aumentamos mucho el cuanto:
- [ ] a) Se beneficia a los procesos interactivos
- [ ] b) Degenera en FCFS y puede provocar efecto convoy
- [ ] c) Degenera en SJF y provoca hambruna
- [ ] d) Round-Robin no usa cuanto
- [ ] e) Aumentan los cambios de contexto

---

### Pregunta 10
Si una modificacion encarece (hace mas lento) cada cambio de contexto, la politica mas
perjudicada es:
- [ ] a) FCFS
- [ ] b) SJF
- [ ] c) Round-Robin con cuanto grande
- [ ] d) Round-Robin con cuanto pequeño
- [ ] e) Afecta por igual a todas

---

### Pregunta 11
```c
int eliminar(Cliente *c) {
    if (existe(c, lista)) {
        pthread_mutex_lock(&m);
        borrar(c, lista);
        pthread_mutex_unlock(&m);
        return 0;
    }
    return -1;
}
```
Que problema tiene?
- [ ] a) Ninguno, es correcto
- [ ] b) Deadlock
- [ ] c) Condicion de carrera: existe() esta fuera del lock
- [ ] d) Falta inicializar el mutex
- [ ] e) No compila

---

### Pregunta 12
La llamada `mlock()`:
- [ ] a) Sincroniza acceso a variables compartidas
- [ ] b) Evita que la memoria de un proceso vaya a swap
- [ ] c) Bloquea ficheros (lectores/escritores)
- [ ] d) Bloquea señales
- [ ] e) No existe

---

### Pregunta 13
`flock()` sirve para:
- [ ] a) Sincronizar variables en memoria
- [ ] b) Bloqueo de lectores/escritores sobre FICHEROS
- [ ] c) Evitar el swap
- [ ] d) Hacer escrituras en modo append
- [ ] e) Vaciar el buffer

---

### Pregunta 14
La seccion `.text` de un ELF contiene:
- [ ] a) Datos inicializados
- [ ] b) Datos no inicializados
- [ ] c) Las instrucciones (codigo maquina)
- [ ] d) La GOT y la PLT
- [ ] e) La tabla de simbolos

---

### Pregunta 15
Marca la opcion INCORRECTA. Un fichero ELF contiene informacion sobre:
- [ ] a) El punto de entrada del programa
- [ ] b) La arquitectura objetivo
- [ ] c) El tipo de planificador que usara el kernel
- [ ] d) El enlazado
- [ ] e) Los datos inicializados

---

### Pregunta 16
Con lazy binding, la direccion de una funcion de biblioteca se resuelve:
- [ ] a) Al compilar
- [ ] b) Al enlazar con gcc
- [ ] c) En la primera llamada a esa funcion
- [ ] d) Al inicio del programa (antes de main)
- [ ] e) Al terminar el programa

---

### Pregunta 17
En un sistema de ficheros estilo Unix con i-nodos, la asignacion de bloques es:
- [ ] a) Contigua
- [ ] b) Lista enlazada simple
- [ ] c) Lista enlazada con tabla (estilo FAT)
- [ ] d) Indexada con esquema combinado (directos + indirectos)
- [ ] e) Indexada de exactamente 4 niveles siempre

---

# RESPUESTAS

1. **a) 2 3** — a=3; ++a->a=4,b=4; b-=2->b=2; a=b++ asigna 2 a `a` y luego b pasa a 3. Resultado: a=2, b=3.
2. **b) Atraviesa un puntero y accede al campo de un struct** — `p->c` equivale a `(*p).c`.
3. **b) Reserva mas memoria de la necesaria** — `100*sizeof(char*)` ≈ 800 bytes para 100 chars; valido pero incorrecto.
4. **c) 8 lineas por stderr** — 3 forks -> 2^3 = 8 procesos; cada uno escribe en stderr.
5. **c) Dos iguales y dos distintos** — los hermanos comparten el mismo padre (getppid igual); el otro par tiene otro padre.
6. **c) No se puede capturar ni ignorar, y no es Ctrl+C** — Ctrl+C es SIGINT; SIGKILL/SIGSTOP son incapturables.
7. **c) Señales bloqueadas** — la mascara bloquea (deja pendientes), no "ignora".
8. **b) SIGPIPE** — escribir sin lectores genera SIGPIPE (por defecto mata el proceso).
9. **b) Degenera en FCFS y efecto convoy** — con cuanto enorme casi nunca hay desalojo.
10. **d) Round-Robin con cuanto pequeño** — es el que mas cambios de contexto hace.
11. **c) Condicion de carrera** — entre `existe()` (fuera del lock) y `borrar()` otro hilo puede modificar la lista.
12. **b) Evita que la memoria vaya a swap** — fija paginas en RAM; no sincroniza.
13. **b) Bloqueo de lectores/escritores sobre ficheros** — LOCK_SH / LOCK_EX.
14. **c) Las instrucciones** — `.text` = codigo; `.data` datos inicializados; `.bss` no inicializados.
15. **c) El planificador** — el ELF no fija el planificador; lo decide el kernel.
16. **c) En la primera llamada** — lazy binding resuelve via PLT al primer uso.
17. **d) Indexada con esquema combinado** — bloques directos para ficheros pequeños + indirectos para grandes.
