#include <stdio.h>

int 
main(int argc, char*argv[]) {

    int a = 80;
    float f= 45.54; 
    float resultado;

    resultado = (float)a + f;
    printf("Valor entero: %d\nValor float: %.2f\nValor double: %.4f\nValor char: %c\n", a, (float)a, (double)a, (char)a);
    printf("Valor de la suma: %.3f\n", resultado);
    printf("Valor de la suma en char:%c\n", (char)resultado);

    

    return 0;
}