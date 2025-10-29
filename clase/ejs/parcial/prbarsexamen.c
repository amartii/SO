#include <stdio.h>
#include <string.h>

int 
main(int argc, char **argv){
    int i;

    if (argc < 2){
        printf("error: use %s argmento1 argumento2 ...\n", argv[0]);
    }

    for(i = 1; i < argc; i++){
        if(strchr(argv[i], '/') != NULL){
            printf("%s\n", argv[i]);
        }
    }
}