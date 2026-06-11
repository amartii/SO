#include <stdlib.h>
#include <stdio.h>

int
main(void)
{
    char *ptr = NULL;

    printf("sizeof(char) = %zu\n", sizeof(char));
    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("sizeof(long) = %zu\n", sizeof(long));
    printf("sizeof(unsigned int) = %zu\n", sizeof(unsigned int));
    printf("sizeof(float) = %zu\n", sizeof(float));
    printf("sizeof(double) = %zu\n", sizeof(double));
    printf("sizeof(char*) = %zu\n", sizeof(ptr));
    exit(EXIT_SUCCESS);
}
