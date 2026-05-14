# Preguntas de Examen Organizadas por Tema

Este documento contiene todas las preguntas de examen recopiladas, organizadas por tema. Usa este fichero como repaso diario.

---

## 1. FUNDAMENTOS DE C Y PUNTEROS (15-20% del examen)

**P1.1** Que imprime?
```c
char *p = "hola";
p[2] = '\0';
printf("%zu\n", strlen(p));
```
**R:** 2. El '\0' en posicion 2 acorta la cadena a "ho".

**P1.2** Que imprime sizeof?
```c
int a[5]; int *p = a;
printf("%zu %zu\n", sizeof(a), sizeof(p));
```
**R:** 20 8. sizeof(array en pila) = 5*4 = 20. sizeof(puntero) = 8 en 64 bits.

**P1.3** Array como parametro:
```c
void f(int arr[]) { printf("%zu", sizeof(arr)); }
int main() { int a[5]; f(a); }
```
**R:** 8. El array se degrada a puntero al pasarlo como parametro.

**P1.4** Aritmetica de punteros:
```c
int arr[] = {0,1,2,3,4,5};
int *p = arr + 2;
p = &p[1];
printf("%d", p[2]);
```
**R:** 5. p apunta a arr[2], &p[1] = &arr[3], p[2] = arr[5] = 5.

**P1.5** Que imprime?
```c
unsigned char c = 200;
int i = c;
printf("%d", i);
```
**R:** 200. unsigned char va de 0 a 255, y 200 cabe.

**P1.6** Incremento postfijo:
```c
int x = 5;
int y = x++;
printf("%d %d", x, y);
```
**R:** 6 5. Postfijo: primero asigna (y=5), luego incrementa (x=6).

**P1.7** Que errores tiene?
```c
char *crear() {
    char buf[100];
    strcpy(buf, "hola");
    return buf;
}
```
**R:** Retorna puntero a variable local. buf se destruye al salir de la funcion.

---

## 2. MEMORIA DINAMICA (15% del examen)

**P2.1** Memoria leak:
```c
char *p = malloc(100);
p = "hola";
free(p);
```
**R:** Memory leak + crash. malloc(100) se pierde al reasignar p. free de un literal es comportamiento indefinido.

**P2.2** sizeof incorrecto:
```c
char *p = malloc(100);
memset(p, 0, sizeof(p));
```
**R:** Solo inicializa 8 bytes (sizeof del puntero), no 100.

**P2.3** Use after free:
```c
int *p = malloc(sizeof(int));
*p = 42;
free(p);
printf("%d", *p);
```
**R:** Comportamiento indefinido. Acceso a memoria liberada.

**P2.4** Correcto uso de malloc:
```c
int *arr = malloc(10 * sizeof(int));
if (arr == NULL) exit(1);
for (int i = 0; i < 10; i++) arr[i] = i;
free(arr);
arr = NULL;
```
**R:** Correcto. Comprueba NULL, usa sizeof correcto, libera y pone a NULL.

**P2.5** sizeof de struct:
```c
struct S { char a; int b; };
printf("%zu", sizeof(struct S));
```
**R:** Tipicamente 8 (no 5), por el relleno de alineacion.

**P2.6** Doble free:
```c
int *p = malloc(sizeof(int));
free(p);
free(p);
```
**R:** Comportamiento indefinido. Doble free puede corromper el heap.

---

## 3. PROCESOS Y FORK (15-20% del examen)

**P3.1** Cuantos procesos?
```c
fork(); fork(); fork();
```
**R:** 8 procesos (2^3).

**P3.2** Cuantas veces imprime B?
```c
printf("A"); fork(); fork(); printf("B\n");
```
**R:** A se imprime 1 vez (queda en buffer, puede duplicarse), B se imprime 4 veces.

**P3.3** Que imprime?
```c
pid_t p = fork();
if (p == 0) { printf("hijo\n"); exit(0); }
wait(NULL);
printf("padre\n");
```
**R:** Siempre "hijo" antes que "padre". wait garantiza el orden.

**P3.4** Fork en un for:
```c
for (int i = 0; i < 2; i++) fork();
printf("X\n");
```
**R:** 4 lineas con X (2^2 = 4 procesos).

**P3.5** Getppid:
```c
fork(); fork();
printf("%d\n", getppid());
```
**R:** 4 procesos, algunos comparten padre. Los hermanos tienen el mismo getppid.

---

## 4. LLAMADAS AL SISTEMA (12% del examen)

**P4.1** read devuelve menos bytes: es error?
**R:** No. Read puede devolver menos bytes de los pedidos sin ser error (short read).

**P4.2** exec y continuacion:
```c
execl("/bin/ls", "ls", NULL);
printf("error\n");
```
**R:** printf solo se ejecuta si exec falla. Si tiene exito, el proceso cambia de programa.

**P4.3** Que hace dup2(x, 0)?
**R:** Redirige stdin (descriptor 0) al fichero referenciado por x.

**P4.4** Valor de retorno de fork:
**R:** 0 en el hijo, PID del hijo en el padre, -1 en error.

**P4.5** open dos veces el mismo fichero:
**R:** Dos descriptores diferentes con offsets independientes.

**P4.6** Que hace execl?
**R:** Reemplaza el programa actual. No crea proceso nuevo. No retorna si tiene exito.

**P4.7** dup2 + exec:
```c
x = open("/tmp/afile", O_RDONLY);
dup2(x, 0); close(x);
execl("/bin/wc", "wc", "-l", NULL);
```
**R:** Escribe por stdout el numero de lineas de /tmp/afile.

**P4.8** wait y zombies:
**R:** Un proceso hijo que termina sin que el padre haga wait se convierte en zombie. signal(SIGCHLD, SIG_IGN) evita zombies.

---

## 5. GESTION DE FICHEROS (10% del examen)

**P5.1** Buffering:
```c
f = fopen("/tmp/x", "w");
fprintf(f, "hi\n");
for(;;) {}
```
**R:** Es muy posible que no se escriba nada. El contenido esta en el buffer.

**P5.2** i-nodo y directorio:
**R:** Una entrada de directorio asocia un nombre con un i-nodo. Puede haber varios nombres (enlaces duros).

**P5.3** unlink y st_nlink:
```bash
echo hola > /tmp/a
ln /tmp/a /tmp/b
unlink("/tmp/a")
```
**R:** El fichero sigue existiendo con st_nlink = 1 (a traves de /tmp/b).

**P5.4** readdir:
**R:** Lee TODAS las entradas de un directorio (ficheros Y directorios).

---

## 6. PIPES (10% del examen)

**P6.1** Pipe basico:
```c
pipe(fd); write(fd[1], &c, 1); read(fd[0], &c, 1); printf("%c", c);
```
**R:** Imprime el caracter escrito.

**P6.2** Write grande en pipe:
```c
char b[32MB]; pipe(fd); write(fd[1], b, sizeof(b)); read(fd[0], b, sizeof(b));
```
**R:** Bloqueado para siempre. Write llena el buffer del pipe y se bloquea.

**P6.3** Write sin lector:
**R:** SIGPIPE (termina el proceso).

**P6.4** Read sin escritor:
**R:** Devuelve 0 (EOF).

---

## 7. SHELL Y VARIABLES (10% del examen)

**P7.1** argv con argc-- y argv++:
```c
argc--; argv++;
for(i=0; i<argc; i++) printf("%s\n", argv[i]);
```
**R:** Imprime todos los argumentos excepto el nombre del programa.

**P7.2** getenv("$PATH"):
**R:** Incorrecto. Debe ser getenv("PATH") sin el dolar.

**P7.3** PATH:
**R:** Rutas donde se buscan ejecutables, separados por ":".

**P7.4** Variable no heredada:
```bash
mipid=20; bash; echo "$mipid"
```
**R:** No imprime nada. Las variables de shell no se heredan sin export.

**P7.5** Script con shift:
```bash
for i in $*; do echo $1; shift; done
```
**R:** Imprime cada argumento en una linea.

---

## 8. MEMORIA VIRTUAL (8% del examen)

**P8.1** Marcos con paginacion bajo demanda:
```c
char a[2MB]; a[0] = 'a';
```
**R:** 1 marco. Solo se asigna el marco de la pagina accedida.

**P8.2** Memoria virtual:
**R:** Permite proteger la memoria de los distintos procesos.

**P8.3** TLB:
**R:** Cache que acelera la traduccion de direccion virtual a fisica.

---

## 9. PLANIFICACION (8% del examen)

**P9.1** Round Robin con cuanto grande:
**R:** Degenera en FCFS y causa efecto convoy.

**P9.2** Cambios de contexto mas lentos afectan mas a:
**R:** Round Robin con cuanto pequeño (mas cambios de contexto).

**P9.3** renice:
**R:** Cambia la prioridad (niceness) con valores entre -20 y 19.

---

## 10. CONCURRENCIA (8% del examen)

**P10.1** Comprobacion fuera del mutex:
```c
if (contador > 0) { lock(); contador--; unlock(); }
```
**R:** Condicion de carrera. La comprobacion debe estar dentro del lock.

**P10.2** Spinlocks:
**R:** No usar con contencion alta (desperdician CPU).

**P10.3** x puede superar Maxcont:
```c
if (x < Maxcont) { spin_lock(); x++; spin_unlock(); }
```
**R:** Si. La comprobacion esta fuera del lock.

**P10.4** mlock:
**R:** Evita que la memoria vaya a swap (no sincroniza).

**P10.5** flock:
**R:** Lock de lectores/escritores para FICHEROS.

---

## 11. ELF Y ENLAZADO (7% del examen)

**P11.1** Seccion de instrucciones: **R:** .text

**P11.2** ELF NO contiene: **R:** Tipo de planificador.

**P11.3** Lazy binding: **R:** Resuelve en la primera llamada.

**P11.4** RELRO: **R:** Resuelve al inicio de ejecucion.

**P11.5** ldd: **R:** Muestra bibliotecas dinamicas de un binario ELF.

---

## 12. SISTEMAS DE FICHEROS (7% del examen)

**P12.1** FAT: **R:** Nombres en entradas de directorio, FAT tiene punteros a clusters.

**P12.2** i-nodos: **R:** Asignacion indexada con esquema combinado.

---

## 13. SEÑALES (5% del examen)

**P13.1** Mascara de señales: **R:** Indica señales bloqueadas (no ignoradas).

**P13.2** SIGKILL: **R:** Mata proceso, no puede ser ignorada. No es Ctrl+C (eso es SIGINT).
