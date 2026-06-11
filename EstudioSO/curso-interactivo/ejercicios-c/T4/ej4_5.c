/***Enunciado:** Escribe un programa que reciba N como argumento 
 * y lance N procesos hijos. Cada hijo imprime su numero (del 0 al N-1) y su PID. 
 * El padre espera a todos los hijos.

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
- El padre espera con un bucle de wait()*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void usage(void){
    fprintf(stderr, "error: usage ./ej4_5\n");
    exit(EXIT_FAILURE);
}

int
main(int argc, char **argv){
    int numargs = argc -1;
    long n;
    char *endptr;
    pid_t pid;

    if (numargs != 1){
        usage();
    }

    n = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || n < 0){
        fprintf(stderr, "error: not a valid number\n");
        exit(EXIT_FAILURE);
    }

    for (int i= 0; i < n; i++){
        pid = fork();
        if (pid == -1){
            fprintf(stderr, "error: fork\n");
            exit(EXIT_FAILURE);
        }
        if (pid == 0){
            printf("Hijo %d, PID = %d\n", i, getpid());
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < n; i++) {
		wait(NULL);
	}
	printf("Padre: todos los hijos terminaron\n");
	exit(EXIT_SUCCESS);

}