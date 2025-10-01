#include <stdio.h>

int 
main(int argc, char*argv[]) {
    int a = 1;
    int b = 2; 
    int suma = a + b;

    int n1;
    int n2;
    int resultado;
    // imprimimos el sumatorio de los dos numeros definidos como variables
    printf("La suma es: %d\n", suma);
    // pedimos al usuario que ingrese dos numeros
    printf("Ingresa el primer numero: ");
    scanf("%d", &n1);
    printf("Ingresa el segundo numero: ");
    scanf("%d", &n2);
    resultado = n1 + n2;
    printf("El resultado de la suma es: %d\n", resultado);

    return 0;
}