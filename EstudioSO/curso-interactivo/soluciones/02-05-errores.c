#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *
crear_saludo(const char *nombre)
{
    size_t len = strlen(nombre) + 7;
    char *saludo = malloc(len);

    if (saludo == NULL) {
        fprintf(stderr, "error: no hay memoria\n");
        exit(EXIT_FAILURE);
    }
    snprintf(saludo, len, "Hola, %s", nombre);
    return saludo;
}

int
main(int argc, char *argv[])
{
    char *p;
    char *q;
    int *arr;
    char *saludo;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <nombre>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    p = malloc(10);
    if (p == NULL) {
        fprintf(stderr, "error: no hay memoria\n");
        exit(EXIT_FAILURE);
    }
    memset(p, 0, 10);

    q = malloc(5);
    if (q == NULL) {
        free(p);
        fprintf(stderr, "error: no hay memoria\n");
        exit(EXIT_FAILURE);
    }
    strcpy(q, "hola");
    free(q);

    arr = malloc(100 * sizeof(int));
    if (arr == NULL) {
        free(p);
        fprintf(stderr, "error: no hay memoria\n");
        exit(EXIT_FAILURE);
    }
    arr[0] = 42;
    free(arr);

    saludo = crear_saludo(argv[1]);
    printf("%s\n", saludo);
    free(saludo);

    free(p);
    exit(EXIT_SUCCESS);
}
