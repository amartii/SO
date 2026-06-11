#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    int lista[5] = {10, 20, 30, 40, 50};
    int *p;

    if (argc != 1) {
        fprintf(stderr, "usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (p = lista; p < lista + 5; p++) {
        printf("%d\n", *p);
    }
    exit(EXIT_SUCCESS);
}
