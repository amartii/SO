# Simulacro de Examen 2 - Sistemas Operativos

**Tiempo: 90 minutos | 20 preguntas | No mirar las respuestas hasta terminar**

---

### Pregunta 1
```c
char *crear() {
    char buf[50];
    snprintf(buf, 50, "hola");
    return buf;
}
int main() { printf("%s\n", crear()); }
```
- a) Imprime "hola"
- b) Comportamiento indefinido (puntero a variable local)
- c) Error de compilacion
- d) Imprime basura siempre

---

### Pregunta 2
```c
int *p = malloc(100 * sizeof(int));
free(p);
p[0] = 42;
```
- a) Funciona correctamente
- b) Use-after-free (comportamiento indefinido)
- c) Error de compilacion
- d) Segmentation fault siempre

---

### Pregunta 3
```c
fork(); fork(); fork();
printf("Z\n");
```
Cuantas Z se imprimen?
- a) 3
- b) 6
- c) 8
- d) 7

---

### Pregunta 4
```c
pid_t p = fork();
if (p == 0) {
    execlp("ls", "ls", NULL);
    fprintf(stderr, "ERROR\n");
}
wait(NULL);
printf("FIN\n");
```
Si exec tiene exito, que imprime el padre?
- a) ERROR FIN
- b) FIN
- c) Nada
- d) ERROR

---

### Pregunta 5
En un sistema Unix con i-nodos:
- a) Se usa asignacion contigua
- b) Se usa FAT
- c) Se usa asignacion indexada con esquema combinado
- d) Se usa lista enlazada simple

---

### Pregunta 6
```bash
echo hola > /tmp/a
ln /tmp/a /tmp/b
rm /tmp/a
```
El fichero con el i-nodo original:
- a) Se borro completamente
- b) Sigue existiendo con st_nlink = 1
- c) Sigue existiendo con st_nlink = 2
- d) Es un enlace simbolico roto

---

### Pregunta 7
La mascara de señales de un proceso:
- a) Indica que señales ignora
- b) Indica que manejadores tiene
- c) Indica que señales tiene bloqueadas
- d) Es la tabla de descriptores

---

### Pregunta 8
Los spinlocks no se deben usar cuando:
- a) La contencion es baja
- b) La contencion es alta
- c) La seccion critica es pequeña
- d) Siempre son peores que mutex

---

### Pregunta 9
Si Round Robin tiene cambios de contexto mas lentos, la politica mas afectada es:
- a) FCFS
- b) SJF
- c) Round Robin con cuanto grande
- d) Round Robin con cuanto pequeño

---

### Pregunta 10
```c
void incr() {
    if (x < MAX) {
        pthread_spin_lock(&lk);
        x++;
        pthread_spin_unlock(&lk);
    }
}
```
- a) x nunca superara MAX
- b) x puede ser mayor que MAX
- c) Hay un deadlock
- d) El codigo es correcto

---

### Pregunta 11
El comando ldd muestra:
- a) Bibliotecas estaticas
- b) Bibliotecas dinamicas de un binario ELF
- c) La GOT y PLT
- d) Los simbolos de un binario

---

### Pregunta 12
En FAT, los nombres de ficheros estan en:
- a) La tabla FAT
- b) Los clusters de datos
- c) Las entradas de directorio
- d) El MBR

---

### Pregunta 13
```c
int fd[2];
char c = 'A';
pipe(fd);
write(fd[1], &c, 1);
read(fd[0], &c, 1);
printf("%c\n", c);
```
- a) Bloqueado para siempre
- b) Imprime A
- c) SIGPIPE
- d) Error

---

### Pregunta 14
Ctrl+C envia:
- a) SIGKILL
- b) SIGTERM
- c) SIGINT
- d) SIGSTOP

---

### Pregunta 15
Con RELRO, los simbolos se resuelven:
- a) En compilacion
- b) Al inicio de la ejecucion
- c) En la primera llamada
- d) Al terminar

---

### Pregunta 16
opendir + readdir lista:
- a) Solo ficheros regulares
- b) Solo directorios
- c) Todas las entradas (ficheros y directorios)
- d) Solo ficheros no ocultos

---

### Pregunta 17
```c
char *p = malloc(5);
p = "hola";
free(p);
```
- a) Correcto
- b) Memory leak + crash en free
- c) Solo memory leak
- d) Solo crash en free

---

### Pregunta 18
Copy-on-write en fork significa que:
- a) El hijo copia toda la memoria inmediatamente
- b) Padre e hijo comparten paginas hasta que uno escriba
- c) Solo el hijo tiene memoria
- d) No se usa memoria fisica

---

### Pregunta 19
La variable PATH contiene:
- a) La ruta actual del shell
- b) Los HOME de los usuarios
- c) Las rutas donde se buscan ejecutables, separados por ":"
- d) Las rutas de bibliotecas

---

### Pregunta 20
Diferencia entre mutex y semaforo:
- a) Son lo mismo
- b) Mutex es binario, semaforo es contador
- c) Semaforo es binario, mutex es contador
- d) Mutex usa espera activa siempre

---

# RESPUESTAS

1. b) Comportamiento indefinido (puntero a variable local)
2. b) Use-after-free
3. c) 8 (2^3)
4. b) FIN (exec reemplaza al hijo, el padre no ve ERROR)
5. c) Asignacion indexada con esquema combinado
6. b) Sigue existiendo con st_nlink = 1
7. c) Indica señales bloqueadas
8. b) Contencion alta
9. d) Round Robin con cuanto pequeño
10. b) x puede ser mayor que MAX (if fuera del lock)
11. b) Bibliotecas dinamicas
12. c) Entradas de directorio
13. b) Imprime A
14. c) SIGINT
15. b) Al inicio de la ejecucion
16. c) Todas las entradas
17. b) Memory leak + crash en free
18. b) Comparten paginas hasta que uno escriba
19. c) Rutas de ejecutables separados por ":"
20. b) Mutex binario, semaforo contador
