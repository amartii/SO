#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *
concatenar(const char *a, const char *b)
{
    size_t len = strlen(a) + strlen(b) + 1;
    char *resultado = malloc(len);

    if (resultado == NULL) {
        fprintf(stderr, "error: no hay memoria\n");
        exit(EXIT_FAILURE);
    }
    strcpy(resultado, a);
    strcat(resultado, b);
    return resultado;
}

int
main(int argc, char *argv[])
{
    char *resultado;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <cadena1> <cadena2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    resultado = concatenar(argv[1], argv[2]);
    printf("%s\n", resultado);
    free(resultado);
    exit(EXIT_SUCCESS);
}
