# Ejercicios Interactivos de C - Dia 4: Procesos (fork, exec, wait)

---

## Ejercicio 4.1: Fork basico

**Enunciado:** Escribe un programa que haga fork. El hijo imprime "Soy el hijo, PID=X" y el padre imprime "Soy el padre, PID=X, hijo=Y". El padre debe esperar al hijo con wait.

**Pistas:**
- fork() devuelve 0 en el hijo, PID del hijo en el padre
- Usa getpid() para obtener tu propio PID

**Solucion:** Ver `../soluciones/04-01-fork.c`

---

## Ejercicio 4.2: Contar procesos (EXAMEN)

**Sin compilar**, cuantos procesos existen al final y cuantas veces se imprime "X"?

```c
int main() {
    fork();
    fork();
    printf("X\n");
    return 0;
}
```

**Respuesta:** Se crean 4 procesos y se imprime "X" 4 veces.
- El primer fork crea 2 procesos
- El segundo fork duplica los 2, total 4
- Los 4 imprimen "X"

---

## Ejercicio 4.3: Fork y printf sin newline (EXAMEN)

**Sin compilar**, cuantas veces se imprime "A" y cuantas "B"?

```c
int main() {
    printf("A");
    fork();
    printf("B\n");
    return 0;
}
```

**Respuesta:** Se imprime "AB" dos veces, es decir A aparece 2 veces y B 2 veces. Porque printf("A") sin newline queda en el buffer. El fork copia el buffer. Ambos procesos tienen "A" en su buffer y luego añaden "B\n", que provoca el flush. Resultado: "AB\nAB\n".

---

## Ejercicio 4.4: Ejecutar comando externo

**Enunciado:** Escribe un programa que haga fork, el hijo ejecute `ls -la /tmp` con execlp, y el padre espere al hijo e imprima su codigo de salida.

**Pistas:**
- El hijo llama a execlp("ls", "ls", "-la", "/tmp", NULL)
- El padre llama a wait(&status)
- Usa WEXITSTATUS(status) para el codigo de salida

**Solucion:** Ver `../soluciones/04-04-exec.c`

---

## Ejercicio 4.5: Lanzar N procesos

**Enunciado:** Escribe un programa que reciba N como argumento y lance N procesos hijos. Cada hijo imprime su numero (del 0 al N-1) y su PID. El padre espera a todos los hijos.

**Ejemplo:**
```
$ ./nhijos 3
Hijo 0, PID=12345
Hijo 1, PID=12346
Hijo 2, PID=12347
Padre: todos los hijos terminaron
```

**Pistas:**
- Haz fork en un bucle
- El hijo debe hacer exit() para no seguir el bucle del padre
- El padre espera con un bucle de wait()

**Solucion:** Ver `../soluciones/04-05-nhijos.c`

---

## Ejercicio 4.6: searchstr (basado en practica real)

**Enunciado:** Escribe un programa que reciba pares de argumentos (fichero, cadena) y busque cada cadena en su fichero usando procesos hijos que ejecuten fgrep. Es decir, si recibes 4 argumentos, lanzas 2 procesos fgrep en paralelo. El padre espera a todos.

**Ejemplo:**
```
$ ./searchstr fichero1 "hola" fichero2 "mundo"
```

**Pistas:**
- Comprueba que el numero de argumentos es par
- Para cada par, fork + execl("/usr/bin/fgrep", "fgrep", cadena, fichero, NULL)
- El padre recoge los hijos con wait en un bucle

**Solucion:** Ver `../soluciones/04-06-searchstr.c`

---

## Ejercicio 4.7: Pregunta tipo examen - fork y arbol

**Sin compilar**, dibuja el arbol de procesos y di que imprime:

```c
int main() {
    int x = 0;
    pid_t pid = fork();
    if (pid == 0) {
        x = 1;
        fork();
    }
    printf("%d\n", x);
    return 0;
}
```

**Respuesta:**
```
Arbol:
  Padre (x=0)
    |
    Hijo1 (x=1)
       |
       Nieto (x=1)

Salida: tres lineas
  0   (padre, no entro en el if)
  1   (hijo1, cambio x a 1)
  1   (nieto, heredo x=1 del hijo1)
```
El padre imprime 0. El hijo cambia x a 1, luego fork crea un nieto que hereda x=1. Ambos imprimen 1.

---

## Ejercicio 4.8: Pregunta tipo examen - exec y continuacion

**Sin compilar**, que imprime este programa si execl tiene exito?

```c
int main() {
    printf("Antes\n");
    execl("/bin/echo", "echo", "Hola", NULL);
    printf("Despues\n");
    return 0;
}
```

**Respuesta:** Imprime "Antes" y luego "Hola". El printf("Despues") nunca se ejecuta porque execl reemplaza el programa. Si exec tiene exito, el codigo posterior no existe.
