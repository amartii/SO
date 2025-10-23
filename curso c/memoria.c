#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char **argv){
    //char array[30]; que pasa si ocupo solo 15, estoy despediciando 15/30
    char * p;
    int n = -10;

    p = malloc(n*sizeof(char));
    if(p == NULL){
        printf("Error al asignar memoria\n");
    }else{
        printf("Se asignó memoria\n");
    }

    return 0;
}