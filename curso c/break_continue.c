#include <stdio.h>

int 
main (int argc, char*argv[]){
    int n= 0;
    int o = 10;
    while (n <=10){
        if (n==8){
            break;
        }
        printf("%i\n", n);
        n++;
    }
    while (o <=20){
        o++; //aumentamos el contador aquí para usar el continue, cuando encuentra el 16 se lo salta
        if (o==16){
            printf("Me salto el: %i\n", o);
            continue;
        }
        printf("%i\n", o);
    }
    return 0; 
}