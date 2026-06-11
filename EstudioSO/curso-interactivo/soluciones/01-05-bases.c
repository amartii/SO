#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    unsigned long n;
    char *endptr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <decimal number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n = strtoul(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "error: '%s' no es un numero\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("Decimal: %lu\n", n);
    printf("Octal: %lo\n", n);
    printf("Hexadecimal: %lx\n", n);
    exit(EXIT_SUCCESS);
}
