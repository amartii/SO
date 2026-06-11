#include <stdio.h>
#include <stdlib.h>

void f(int *arr) {
    printf("%zu\n", sizeof(arr));
}

int main(int argc, char **argv) {
    int a[5] = {1,2,3,4,5};
    int *p = malloc(20);
    printf("sizeof array a: %zu\n", sizeof(a));
    printf("sizeof puntero: %zu\n", sizeof(p));
    printf("sizeof funcion (sizeof(array(array))):");
    f(a);
    free(p);
    return 0;
}