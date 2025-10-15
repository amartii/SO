#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

//comprobar con limits.h que no sea el numero ni max ni min y además *end= \0 

int 
main(int argc, char **argv){
    char *endn;
    char *endl;
    long n;
    long l;
    int nargs;

    //comprobar que se pasan los argumentos n y l y controlar el error (el programa sale con estado de fallo)
    if (argc < 3){
        fprintf(stderr, "Uso: %s N L ps\n", argv[0]);
        return EXIT_FAILURE;
    } else{
        n = strtol(argv[1],&endn,10); //strtol(string, apuntoalfinal,base);
        l = strtol(argv[2],&endl,10);

        nargs = argc -1;
        printf("Numero de args:%i\n",nargs);

        //comprobación de los argumentos
        for (int i=0; i<=argc -1;i++){
            printf("El argumento %i es:%s\n",i, argv[i]);
        }
        printf("Argumento l: %ld\n", l);
        printf("Argumento n: %ld\n", n);
        return 0;
    }
 
}

