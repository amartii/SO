#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char **argv){
    int longBarra;
    int retardo;
    int i;
    int j;

    /*printf("Introduce la longitud de la barra:\n");
    scanf("%i", &longBarra);
    printf("Introduce el retardo:\n");
    scanf("%i", &retardo);*/

    if (argc != 3){
        printf("uso: %s longitud retardo\n", argv[0]);
        return 1;
    }

    longBarra = atoi(argv[1]);
    retardo = atoi(argv[2]);

    for (i = 0; i <= longBarra; i++){
        printf("\r[");
        for(j = 0; j < longBarra; j++){
            if(j < i){
                printf("#");
            }else{
                printf(".");
            }
        }
        printf("] %i%%", i * 100 / longBarra);
        fflush(stdout);
        usleep(retardo);
    }
    printf("\n");

    return 0;
}