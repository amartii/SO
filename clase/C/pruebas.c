#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void usage(void){
    fprintf(stderr, "usage: ./pruebas [arg] [arg] ... [arg]\n");
    exit(EXIT_FAILURE);
}


int 
main( int argc, char **argv){
    int args = argc -1;
    if (args<2){
        usage();
    }
    printf("funciona\n");
    printf("el número de args es: %d\n", args);

    for (int i=1; i<=args; i++){
        printf("argumento %d: %s\n", i, argv[i]);
    }

    exit(0);
}