#include <stdio.h>

void saludo(){
    printf("hola\n");
    return;
}

int suma(){
    int a= 2;
    int b = 5;
    int suma;
    suma = a + b;
    return suma;
}

int resta(int a , int b){
    int resta;
    resta = a - b;
    return resta;
}

void holaquetal(){
    printf("Hola que tal\n");
}

int main (int argc, char *argv[]){
    int c= 5;
    int d = 2; 
    saludo();
    printf("La suma es:%i\n", suma());
    printf("La resta es:%i\n", resta(c,d));
    holaquetal();
    return 0;
}