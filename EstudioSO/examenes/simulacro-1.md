# Simulacro de Examen 1 - Sistemas Operativos

**Tiempo: 90 minutos | 20 preguntas | No mirar las respuestas hasta terminar**

---

### Pregunta 1
```c
int a[10];
int *p = a;
printf("%zu %zu\n", sizeof(a), sizeof(p));
```
Que imprime en un sistema de 64 bits?
- a) 10 10
- b) 40 8
- c) 40 40
- d) 10 8

---

### Pregunta 2
```c
char *p = malloc(50);
memset(p, 'A', sizeof(p));
printf("%c%c%c\n", p[0], p[7], p[8]);
```
Que imprime?
- a) AAA
- b) AA y luego basura en la tercera posicion
- c) Segmentation fault
- d) Error de compilacion

---

### Pregunta 3
Cuantas lineas con "X" imprime este programa?
```c
fork(); fork();
printf("X\n");
```
- a) 2
- b) 3
- c) 4
- d) 8

---

### Pregunta 4
```c
printf("A");
fork();
printf("B\n");
```
Cuantas veces se imprime A?
- a) 1
- b) 2
- c) 4
- d) Depende del sistema

---

### Pregunta 5
```c
execl("/bin/echo", "echo", "hola", NULL);
printf("mundo\n");
```
Que imprime si execl tiene exito?
- a) hola mundo
- b) hola
- c) mundo
- d) Nada

---

### Pregunta 6
Que hace read() cuando lee de un pipe vacio sin escritores?
- a) Se bloquea para siempre
- b) Devuelve 0
- c) Recibe SIGPIPE
- d) Devuelve -1

---

### Pregunta 7
Que pasa al escribir en un pipe sin lectores?
- a) Write devuelve 0
- b) Write devuelve -1
- c) SIGPIPE
- d) Se bloquea

---

### Pregunta 8
```c
char b[32*1024*1024];
int fd[2];
pipe(fd);
write(fd[1], b, sizeof(b));
read(fd[0], b, sizeof(b));
```
Que pasa?
- a) Funciona correctamente
- b) SIGPIPE
- c) Bloqueado para siempre
- d) Segmentation fault

---

### Pregunta 9
```bash
$ mipid=20
$ bash
$ echo "$mipid"
```
Que imprime?
- a) 20
- b) Nada (linea vacia)
- c) Error
- d) $mipid

---

### Pregunta 10
La TLB es:
- a) Cache de instrucciones
- b) Cache de datos
- c) Cache de traducciones virtual a fisica
- d) Cache de traducciones fisica a virtual

---

### Pregunta 11
Con paginacion bajo demanda, un array global de 2MB donde solo escribes en a[0]:
- a) Usa 512 marcos
- b) Usa 2048 marcos
- c) Usa 1 marco
- d) Usa 0 marcos

---

### Pregunta 12
Round Robin con cuanto muy grande degenera en:
- a) SJF
- b) FCFS
- c) LRU
- d) SSTF

---

### Pregunta 13
```c
void dec() {
    if (x > 0) {
        pthread_mutex_lock(&m);
        x--;
        pthread_mutex_unlock(&m);
    }
}
```
- a) Correcto
- b) Condicion de carrera
- c) Deadlock
- d) Error de compilacion

---

### Pregunta 14
SIGKILL...
- a) Se puede ignorar con signal()
- b) Se envia con Ctrl+C
- c) No se puede ignorar ni capturar
- d) Para el proceso temporalmente

---

### Pregunta 15
La seccion .text de un ELF contiene:
- a) Datos inicializados
- b) Datos no inicializados
- c) Instrucciones del programa
- d) La tabla de simbolos

---

### Pregunta 16
flock() sirve para:
- a) Lock de variables compartidas
- b) Lock de lectores/escritores en ficheros
- c) Evitar que memoria vaya a swap
- d) No existe

---

### Pregunta 17
mlock() sirve para:
- a) Exclusion mutua
- b) Evitar que la memoria vaya a swap
- c) Lock de ficheros
- d) Bloquear señales

---

### Pregunta 18
Con lazy binding, la direccion de una funcion se resuelve:
- a) En compilacion
- b) Al inicio del programa
- c) En la primera llamada
- d) Al terminar el programa

---

### Pregunta 19
getenv("$HOME") es:
- a) Correcto
- b) Incorrecto, debe ser getenv("HOME")
- c) Incorrecto, debe ser getenv("home")
- d) Incorrecto, debe ser getenv($HOME)

---

### Pregunta 20
```c
FILE *f = fopen("/tmp/x", "w");
fprintf(f, "datos");
for(;;) {}
```
Que contiene /tmp/x?
- a) "datos"
- b) Probablemente nada
- c) Error al crear el fichero
- d) "datos" parcialmente

---

# RESPUESTAS

1. b) 40 8
2. b) AA y basura (sizeof(p)=8, solo pinta 8 bytes de 'A')
3. c) 4
4. b) 2 (A queda en buffer, fork lo copia)
5. b) hola (printf("mundo") no se ejecuta)
6. b) Devuelve 0 (EOF)
7. c) SIGPIPE
8. c) Bloqueado para siempre (deadlock)
9. b) Nada (variable no exportada)
10. c) Cache virtual a fisica
11. c) 1 marco
12. b) FCFS
13. b) Condicion de carrera (if fuera del lock)
14. c) No se puede ignorar ni capturar
15. c) Instrucciones
16. b) Lock lectores/escritores en ficheros
17. b) Evitar swap
18. c) En la primera llamada
19. b) getenv("HOME") sin dolar
20. b) Probablemente nada (buffering)
