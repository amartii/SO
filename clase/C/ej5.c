#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void usage(void){
    fprintf(stderr, "usage: ./ej5 <word>\n");
    exit(EXIT_FAILURE);
}

void mayus(char *str){
    for (int i = 0; str[i] != '\0'; i++){
        str[i] = toupper(str[i]);
    }
}

void invertir(char *str){
    int len = strlen(str);
    char temp;
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int 
main(int argc, char **argv){
    int args = argc-1;
    int longitud;
    char *palabra;

    if (args != 1){
        usage();
    }

    longitud = strlen(argv[1]);
    palabra = malloc(longitud +1);
    if  (palabra == NULL){
        fprintf(stderr, "error: no hay memoria\n");
        exit(EXIT_FAILURE);
    }

    strcpy(palabra, argv[1]);
    printf("Palabra: %s\n", palabra);

    strcpy(palabra, argv[1]);
    invertir(palabra);
    printf("Palabra al revés: %s\n", palabra);

    strcpy(palabra, argv[1]);
    mayus(palabra);
    printf("Palabra en mayúsculas: %s\n", palabra);

    printf("Longitud de la palabra:%d\n", longitud);

    free(palabra);
    exit(EXIT_SUCCESS);
}