#include <stdlib.h>
#include <stdio.h>

void usage(void){
    fprintf(stderr, "usage: ./ej2 <Number>\n");
    exit(EXIT_FAILURE);
}

int
main(int argc, char ** argv){
    int N;
    int suma = 0;
    int count = 0;
    int args = argc-1;
    char *endptr;

    if (args != 1){
        usage();
    }
    
    N = strtol(argv[1], &endptr, 10);
    if(*endptr != '\0'){
        fprintf(stderr, "error: %s no es un numero entero\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    printf("El numero es: %d\n",N);
    printf("Forma 2:\n");
    for (int i=0;count<N ; i++){
        if(i%2 == 0){
            printf("%d\n", i);
            suma +=i;
            count++;
        }
    }
    
    suma = 0;
    printf("Forma 2:\n");
    for (int i=0; i<N; i++){
        int par = i*2;
        printf("%d\n",par);
        suma = suma + par;
    }
    printf("suma: %d\n", suma);
    exit(EXIT_SUCCESS);
}