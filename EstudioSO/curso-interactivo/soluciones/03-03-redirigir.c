#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int fd;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <fichero>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "error: no se puede abrir '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) < 0) {
        fprintf(stderr, "error: no se puede redirigir stdout\n");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    printf("Este texto fue redirigido a un fichero\n");
    exit(EXIT_SUCCESS);
}
