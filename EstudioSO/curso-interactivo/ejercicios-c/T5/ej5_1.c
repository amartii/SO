/***Enunciado:** Escribe un programa donde el padre envie 
 * un mensaje al hijo a traves de un pipe. El hijo lee el mensaje y lo imprime.

**Ejemplo:**

```
Hijo recibio: Mensaje del padre
```

**Pistas:**

- Crea el pipe ANTES del fork
- El padre cierra fd[0] (lectura) y escribe en fd[1]
- El hijo cierra fd[1] (escritura) y lee de fd[0]
- El padre hace wait*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void usage(void){
    fprintf(stderr, "error: usage ./ej5_1\n");
    exit(EXIT_FAILURE);
}

int
main(int argc, char **argv){
    int numargs = argc -1;
    int fd[2];
    pid_t pid;
    char buf[256];
    ssize_t n;

    if (numargs != 0){
        usage();
    }

    if (pipe(fd) == -1){
        perror("error: pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0){
        perror("error: fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0){
        //hijo lector
        close(fd[1]);
        n = read(fd[0], buf, sizeof(buf)-1);
        if (n > 0){
            buf[n] = '\0';
            printf("Hijo recibio: %s\n", buf);
        }
        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
    //padre: escritor
    close(fd[0]);
    write(fd[1], "Mensaje del padre", 17);
    close(fd[1]);
    wait(NULL);
    exit(EXIT_SUCCESS);
}