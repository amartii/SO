# Ejercicios Interactivos de C - Dia 5: Pipes y Senales

---

## Ejercicio 5.1: Pipe simple padre-hijo

**Enunciado:** Escribe un programa donde el padre envie un mensaje al hijo a traves de un pipe. El hijo lee el mensaje y lo imprime.

**Ejemplo:**
```
Hijo recibio: Mensaje del padre
```

**Pistas:**
- Crea el pipe ANTES del fork
- El padre cierra fd[0] (lectura) y escribe en fd[1]
- El hijo cierra fd[1] (escritura) y lee de fd[0]
- El padre hace wait

**Solucion:** Ver `../soluciones/05-01-pipe.c`

---

## Ejercicio 5.2: Simular "ps aux | wc -l"

**Enunciado:** Escribe un programa que simule el pipeline del shell `ps aux | wc -l` usando pipe, fork, dup2 y exec. Crea dos hijos: uno ejecuta ps aux y otro ejecuta wc -l, conectados por un pipe.

**Pistas:**
- Crea un pipe
- Hijo 1: cierra fd[0], dup2(fd[1], STDOUT_FILENO), cierra fd[1], execlp("ps", ...)
- Hijo 2: cierra fd[1], dup2(fd[0], STDIN_FILENO), cierra fd[0], execlp("wc", ...)
- Padre: cierra ambos extremos y espera a los dos hijos

**Solucion:** Ver `../soluciones/05-02-pipeline.c`

---

## Ejercicio 5.3: Manejador de SIGINT

**Enunciado:** Escribe un programa que registre un manejador para SIGINT (Ctrl+C). El manejador imprime "Ctrl+C recibido, intento N". Despues de 3 intentos, el programa termina.

**Ejemplo:**
```
Esperando señales... (Ctrl+C para probar)
^CCtrl+C recibido, intento 1
^CCtrl+C recibido, intento 2
^CCtrl+C recibido, intento 3. Saliendo.
```

**Pistas:**
- Usa una variable global para el contador (volatile sig_atomic_t)
- signal(SIGINT, tu_manejador)
- El programa espera en un bucle con pause() o sleep()

**Solucion:** Ver `../soluciones/05-03-sigint.c`

---

## Ejercicio 5.4: Pipe con timeout usando alarm

**Enunciado:** Escribe un programa que intente leer de un pipe vacio. Registra un manejador de SIGALRM que imprime "Timeout!" y termina. Usa alarm(3) para que el timeout sea de 3 segundos.

**Pistas:**
- Crea un pipe pero no escribas nada
- Registra manejador para SIGALRM
- alarm(3) antes de read
- read se bloqueara y sera interrumpido por la senal

**Solucion:** Ver `../soluciones/05-04-timeout.c`

---

## Ejercicio 5.5: Pregunta tipo examen - pipe bloqueado

**Sin compilar**, que hace este programa?

```c
char b[32*1024*1024];
int main() {
    int fd[2];
    if (pipe(fd) < 0)
        err(1, "pipe");
    write(fd[1], b, sizeof(b));
    read(fd[0], b, sizeof(b));
    exit(EXIT_SUCCESS);
}
```

**Respuesta:** Se queda bloqueado para siempre (deadlock). El write intenta escribir 32MB en un pipe cuyo buffer es ~64KB. El write llena el buffer y se bloquea esperando que alguien lea. Pero el read esta despues del write y nunca se ejecuta. Interbloqueo.

---

## Ejercicio 5.6: Pregunta tipo examen - pipe sin lector

**Sin compilar**, que pasa cuando se escribe en un pipe y nadie tiene abierto el extremo de lectura?

**Respuesta:** El proceso recibe SIGPIPE, que por defecto lo termina. No se queda bloqueado, no devuelve 0, no es un error normal. Es una senal.

---

## Ejercicio 5.7: Pregunta tipo examen - pipe vacio sin escritor

**Sin compilar**, que pasa si lees de un pipe vacio y nadie tiene abierto el extremo de escritura?

**Respuesta:** read() devuelve 0 (EOF). No es un error, es la señal de que no habra mas datos. Es una condicion normal de finalizacion.

---

## Ejercicio 5.8: Pregunta tipo examen - pipe basico

**Sin compilar**, que imprime?

```c
int fd[2];
char c = 'x';
pipe(fd);
write(fd[1], &c, 1);
read(fd[0], &c, 1);
printf("%c", c);
```

**Respuesta:** Imprime 'x'. Se escribe 'x' en el pipe por fd[1], se lee de fd[0], y se imprime. Funciona correctamente porque write pone datos y read los recoge en el mismo proceso antes de que el buffer se llene.
