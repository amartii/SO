/***Enunciado:** Escribe un programa que reciba pares de 
 * argumentos (fichero, cadena) y busque cada cadena en su fichero 
 * usando procesos hijos que ejecuten fgrep. Es decir, si recibes 4 
 * argumentos, lanzas 2 procesos fgrep en paralelo. El padre espera a todos.

**Ejemplo:**

```
$ ./searchstr fichero1 "hola" fichero2 "mundo"
```

**Pistas:**

- Comprueba que el numero de argumentos es par
- Para cada par, fork + execl("/usr/bin/fgrep", "fgrep", cadena, fichero, NULL)
- El padre recoge los hijos con wait en un bucle*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void usage(void){
    fprintf(stderr, "error: usage ./ej4_6 <fichero> <cadena> <fichero> <cadena> ... \n");
    exit(EXIT_FAILURE);
}

int
main(int argc, char **argv){
    int numargs = argc - 1;
    pid_t pid;
    int pares = numargs/2;

    if (numargs < 2 || numargs % 2 !=0){
        usage();
    }

    for (int i=0; i < numargs; i++){
        pid = fork();
        if (pid == -1){
            fprintf(stderr, "error: fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0){
            execl("/usr/bin/fgrep", "fgrep", argv[i + 1], argv[i], NULL);
            perror("error: execl falla");
            exit(EXIT_FAILURE);

        }

    }
    for (int i= 0; i < pares; i++){
        wait(NULL);
    }

    exit(EXIT_SUCCESS);
}