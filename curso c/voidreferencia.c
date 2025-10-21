#include <stdio.h>

//ejemplo de como pasar pro referencia el valor a una funcion
int 
main(int argc, char **argv){

    int a = 2;
    int *apuntaa= &a; //apuntamos apuntaa al valor de a
    printf("El valor de a: %i\n", a);
    printf("Puntero a a: %i\n", *apuntaa); 
    printf("Valor hexadecimal de la posición de memoria que aloja a: %p\n", apuntaa);

    return 0;
}