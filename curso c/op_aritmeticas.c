#include <stdio.h>

int 
main(int argc, char*argv[]) {

    int n1;
    int n2;
    int suma;
    int resta;
    int multiplicacion;
    int division;
    int modulo;

    // pedimos al usuario que ingrese dos numeros
    printf("Ingresa el primer numero: ");
    scanf("%d", &n1);
    printf("Ingresa el segundo numero: ");
    scanf("%d", &n2);
    
    suma = n1 + n2;
    printf("El resultado de la suma es: %d\n", suma);

    resta = n1 - n2;
    printf("El resultado de la resta es: %d\n", resta);

    multiplicacion = n1 * n2;
    printf("El resultado de la multiplicacion es: %d\n", multiplicacion);

    division = n1 / n2;
    printf("El resultado de la division es: %d\n", division);

    modulo = n1 % n2;
    printf("El resultado del modulo es: %d\n", modulo);

    return 0;
}