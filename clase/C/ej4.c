#include <stdio.h>
#include <stdlib.h>

void usage(void){
    fprintf(stderr, "usage: ./ej4 <num> ... <num> <num>\n");
    exit(EXIT_FAILURE);
}

int 
main(int argc, char **argv){
    int args=argc-1;
    int N;
    char *endptr;
    float suma=0;
    int max, min;
  

    if (args<1){
        usage();
    }

    max = strtol(argv[1], &endptr,10);
     if (*endptr != '\0'){
            printf("error: %s no es un numero\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    min=max;

    for (int i=1;i<=args;i++){
        N= strtol(argv[i], &endptr, 10);
        if (*endptr != '\0'){
            printf("error: %s no es un numero\n", argv[i]);
            exit(EXIT_FAILURE);
        }
        suma+=N;
        if (min > N){
            min =N;
        }
        if (max<N){
            max=N;
        }
    }
    
    printf("El máximo es %d\n", max);
    printf("El mínimo es %d\n", min);
    printf("La media es %.2f\n", suma/args);

    exit(EXIT_SUCCESS);
}