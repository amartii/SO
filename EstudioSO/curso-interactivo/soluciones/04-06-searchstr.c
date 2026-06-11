#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int i;
    pid_t pid;

    if (argc < 3 || argc % 2 == 0) {
        fprintf(stderr, "usage: %s <fichero> <cadena> [<fichero> <cadena> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; i += 2) {
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "error: no se puede crear proceso\n");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            execl("/usr/bin/fgrep", "fgrep", argv[i+1], argv[i], NULL);
            fprintf(stderr, "error: execl fallo\n");
            exit(EXIT_FAILURE);
        }
    }

    while (wait(NULL) > 0)
        ;

    exit(EXIT_SUCCESS);
}
