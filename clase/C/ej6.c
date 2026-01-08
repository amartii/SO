#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void usage(void){
    fprintf(stderr, "usage: ./ej6 <argumento> ... <argumento> ...\n");
    exit(EXIT_FAILURE);
}

int
main(int argc, char **argv){

    int args = argc -1;
    if (args < 1){
        usage();
    }

    for (int i= 1;i< argc;i++){
            for (int j= 0;j < strlen(argv[i]); j++){
                if(argv[i][j] == '/'){
                    printf("%s\n",argv[i]);
                }
            }
    }
    exit(EXIT_SUCCESS);
}