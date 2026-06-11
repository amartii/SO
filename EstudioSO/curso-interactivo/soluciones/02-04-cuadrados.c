#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    long n;
    char *endptr;
    int *arr;
    int i;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <N>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || n < 0) {
        fprintf(stderr, "error: '%s' no es un numero valido\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "error: no hay memoria\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++)
        arr[i] = i * i;

    for (i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i + 1 < n)
            printf(" ");
    }
    printf("\n");

    free(arr);
    exit(EXIT_SUCCESS);
}
