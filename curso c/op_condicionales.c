/* usamos if para toma de decisiones
==  comparamos 
!= diferente
>  mayor que
<  menor que
>= mayor o igual que
<= menor o igual que
*/

#include <stdio.h>

int 
main(int argc, char*argv[]) {
    int edad;
    printf("Ingresa tu edad: ");
    scanf("%d", &edad);

    if (edad > 0 && edad <= 3) {
        printf("Eres un bebe\n");
    }else if (edad > 3 && edad <= 12) {
        printf("Eres un niño\n");
    }else if (edad > 12 && edad <= 18) {
        printf("Eres un adolescente\n");
    }else if (edad > 18 && edad <= 25) {
        printf("Eres un adulto funcional\n");
    }else if (edad > 25 && edad <= 60) {
        printf("Eres un adulto mayor\n");
    }else if (edad > 60 && edad <= 120) {
        printf("Eres un anciano\n");
    }else if (edad != (edad > 0 && edad <= 120)) {
        printf("Edad no valida, estas muerto\n");
    }
    return 0;
}