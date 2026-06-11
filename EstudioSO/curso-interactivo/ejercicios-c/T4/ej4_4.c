/***Enunciado:** Escribe un programa que haga fork, 
 * el hijo ejecute `ls -la /tmp` con execlp, y el padre espere al hijo e imprima su codigo de salida.

**Pistas:**

- El hijo llama a execlp("ls", "ls", "-la", "/tmp", NULL)
- El padre llama a wait(&status)
- Usa WEXITSTATUS(status) para el codigo de salida*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void usage(void){
    fprintf(stderr, "error: usage ./ej4_4\n");
    exit(EXIT_FAILURE);
}

int
main(int argc, char **argv){
    int numargs = argc -1;
    pid_t pid;
    int status;

    if (numargs != 0){
        usage();
    }

    pid = fork();
    if (pid == -1){
        fprintf(stderr, "error: fork\n");
        exit(EXIT_FAILURE);
    }
    if (pid == 0){
        execlp("ls", "ls", "-la", "/tmp", NULL);
        perror("error: child");
        exit(EXIT_FAILURE);
    }
    if (wait(&status) == -1){
        perror("error: wait");
        exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)){
        printf("Hijo termina con código: %d ", WEXITSTATUS(status));
    }

    exit(EXIT_SUCCESS);
}