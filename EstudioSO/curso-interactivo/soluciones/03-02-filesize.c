#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
    struct stat sb;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <fichero>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (stat(argv[1], &sb) < 0) {
        fprintf(stderr, "error: no se puede obtener el fichero '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("Tamaño: %lld bytes\n", (long long) sb.st_size);
    exit(EXIT_SUCCESS);
}
