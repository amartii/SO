#include <stdio.h>

int 
main(int argc, char*argv[]) {

    int contador = 0; 

    do {
        printf("%i\n", contador);
        contador++;
    }
    while (contador <=10);

    return 0;
}