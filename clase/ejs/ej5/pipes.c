#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void
usage(void)
{
    fprintf(stderr, "usage: ./pspid [pid]\n");
    exit(EXIT_FAILURE);
}

void
primer_hijo(int fd[2])
{
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* hijo: ps aux, escribe en el pipe */
        if (close(fd[0]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        if (close(fd[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
        execlp("ps", "ps", "aux", (char *)NULL);
        perror("execlp ps");
        exit(EXIT_FAILURE);
    }
}

void
segundo_hijo(int fd[2])
{
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* hijo: wc -l, lee del pipe */
        if (close(fd[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        if (close(fd[0]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }
}

void
padre(void)
{
    int fd[2];
    int status;
    int i;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    primer_hijo(fd);
    segundo_hijo(fd);

    if (close(fd[0]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
    if (close(fd[1]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    /* esperar a los dos hijos (no necesitamos distinguir cuál es cuál aquí) */
     for (i = 0; i < 2; i++) {
        if (wait(&status) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }
}

int
main(int argc, char **argv)
{
    padre();
    return EXIT_SUCCESS;
}
