/***Enunciado:** Escribe un programa que haga fork. 
 * El hijo imprime "Soy el hijo, PID=X" y el padre imprime "Soy el padre, PID=X, hijo=Y". 
 * El padre debe esperar al hijo con wait.

**Pistas:**

- fork() devuelve 0 en el hijo, PID del hijo en el padre
- Usa getpid() para obtener tu propio PID*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void usage(void){
    fprintf(stderr, "error: usage ./ej4_1\n");
    exit(EXIT_FAILURE);
}

int
main(int argc, char ** argv){
    int numargs = argc -1;
    pid_t pid;

    if(numargs != 0){
        usage();
    }

    pid = fork();
    if(pid == -1){
        fprintf(stderr,"error: fork\n");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0){
        printf("Soy el hijo, PID=%d\n", getpid());
        exit(EXIT_SUCCESS);
    }
    printf("Soy el padre, PID=%d, hijo=%d\n", getpid(), pid);
    wait(NULL);
    exit(EXIT_SUCCESS);


}