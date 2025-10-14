#include <stdio.h>

int suma();
int resta();
int a = 10; //puedo declarar una variable global y añadirla a la función

int 
main (int argc, char ** argv){
    int num1, num2;

    printf("Ingresa el primer valor:\n");
    scanf("%i", &num1);
    printf("Ingresa el segundo valor:\n");
    scanf("%i", &num2);
    printf("La suma es:%i\n", suma(num1, num2));
    printf("La resta es:%i\n", resta(num1, num2));
    return 0;
}

int suma(int num1,int num2){
    int suma = num1 + num2 + a; //incluimos la var global sin pasarsela a la función
    return suma;
}

int resta (int num1, int num2){
    int resta = num1 - num2;
    return resta;
}