#include <stdio.h>

int main(void) {
    int n1[4] = {1, 2, 3, 4};
    int n2[]  = {3, 4, 5, 6, 7};

    const size_t sizen1 = sizeof n1 / sizeof n1[0];
    const size_t sizen2 = sizeof n2 / sizeof n2[0];

    printf("El tamaño de n1: %zu\n", sizen1);
    printf("El contenido de n1 es:\n");
    for (size_t i = 0; i < sizen1; i++) {
        printf("%d-", n1[i]);
    }
    printf("\n");

    printf("El tamaño de n2: %zu\n", sizen2);
    printf("El contenido de n2 es:\n");
    for (size_t i = 0; i < sizen2; i++) {
        printf("%d-", n2[i]);
    }
    printf("\n");

    return 0;
}
