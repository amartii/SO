#include <stdio.h>

size_t getsize(float *ptr);

int 
main(int argc, char **argv){
    float array[20];
    printf("El numero de bytes del array es: %lu\n", sizeof(array)); //usamos %ld (long unsigned) nos permite imprimir el valor en bytes
    printf("El numero de bytes devueltos por getsize es: %lu\n",getsize(array));
    return 0;
}

size_t getsize(float *ptr){
    return sizeof(ptr);
}