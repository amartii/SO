#include <stdio.h>
#include <stdlib.h>

void usage(void){
    fprintf(stderr, "usage: ./ej1 <num1> <num2>\n");
    exit(EXIT_FAILURE);
}

int 
main(int argc, char **argv){
    int args=argc -1;
    int a, b;
    char *endptr;

    if (args!=2){
        usage();
    }

    a =strtol(argv[1], &endptr, 10);
    if(*endptr!='\0'){
        fprintf(stderr, "error:'%s' no es un número válido\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    b =strtol(argv[2], &endptr, 10);
    if(*endptr!='\0'){
        fprintf(stderr, "error:'%s' no es un número válido\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    printf("los números son: %d y %d\n", a, b);

    printf("La suma es:%d\n", a+b);
    printf("La resta es: %d\n", a-b);
    printf("El producto es: %d\n", a*b);
    printf("La división entera es: %d\n", a/b);
    printf("El módulo es: %d\n", a%b);
    
    exit(EXIT_SUCCESS);
}