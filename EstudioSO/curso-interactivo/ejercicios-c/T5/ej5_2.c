/***Enunciado:** Escribe un programa que simule el pipeline 
 * del shell `ps aux | wc -l` usando pipe, fork, dup2 y exec. 
 * Crea dos hijos: uno ejecuta ps aux y otro ejecuta wc -l, conectados por un pipe.

**Pistas:**

- Crea un pipe
- Hijo 1: cierra fd[0], dup2(fd[1], STDOUT_FILENO), cierra fd[1], execlp("ps", ...)
- Hijo 2: cierra fd[1], dup2(fd[0], STDIN_FILENO), cierra fd[0], execlp("wc", ...)
- Padre: cierra ambos extremos y espera a los dos hijos*/

#include <stdio.h>
#include <stdlib.h>
 #include <unistd.h>
 #include <sys/wait.h>

void usage(void){
    fprintf(stderr, "error: usage ./ej5_2\n");
    exit(EXIT_SUCCESS);
}

int 
main(int argc, char **argv){
    int numargs = argc -1;
    
    int fd[2];
    pid_t pid;

    if (numargs != 0){
        usage();
    }

    if (pipe(fd) == -1){
        perror("error: pipe");
        exit(EXIT_FAILURE);
    }

    /* Hijo 1: ps aux -> escribe en pipe */
    pid = fork();
    if (pid == -1){
        perror("error: fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0){
        close(fd[0]);
        if(dup2(fd[1], STDOUT_FILENO) == -1){
            perror("error:dup2 1st child");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);
		execlp("ps", "ps", "aux", (char *)NULL);
		perror("execlp ps");
		exit(EXIT_FAILURE);
    }
    /* Hijo 2: wc -l <- lee del pipe */
    pid = fork();
    if (pid == -1){
        perror("error: fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0){
        close(fd[1]);
        if(dup2(fd[0], STDIN_FILENO) == -1){
            perror("error:dup2 2nd child");
            exit(EXIT_FAILURE);
        }
        close(fd[0]);
		execlp("wc", "wc", "-l", (char *)NULL);
		perror("execlp wc");
		exit(EXIT_FAILURE);
    }
    /* Padre: cerrar pipe y esperar */
    close(fd[0]);
    close(fd[1]);
    for (int i = 0; i< 2; i++){
        wait(NULL);
    }
    exit(EXIT_SUCCESS);


}