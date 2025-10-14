#include <stdio.h>
 //las funciones recursivas son las que se llaman así mismas
//ejemplo de sacar el factorial de un numero que pedimos
long Factorial(long numero);
int 
main (int argc, char ** argv){

int numero;

printf("Introduce un numero:\n");
scanf("%i", &numero);
printf("El numero introducido es:%i\n", numero);

for (int i=0; i<=numero; i++) {
    printf("El factorial de %i--> %i!=%ld\n",i,i, Factorial(i));
}
return 0;
    
}

long Factorial(long numero){
    if (numero <=1){
        return 1;
    }else{
        return (numero *Factorial(numero -1));
    }

}

