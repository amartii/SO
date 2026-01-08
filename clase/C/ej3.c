#include <stdlib.h>
#include <stdio.h>
 #include <ctype.h>
 #include <string.h>

void usage(void){
    fprintf(stderr, "usage: ./ej3 <arg>\n");
    exit (EXIT_FAILURE);
}

int 
main(int argc, char **argv){
    int args=argc-1;
    char c=argv[1][0];

    if (args!=1){
        usage();
    }

    if (strlen(argv[1])!= 1){
        printf("error: argumen must be one character\n");
        usage();
    }

    if (isdigit(c)){
        printf("Es un dígito\n");
    }else{
        switch(c){
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            printf("Es una vocal\n");
            break;
        default:
            if(isalpha(c)){
                printf("Es una consonante\n");

            }else{
                printf("Es otro caracter\n");
            }
            break;
        }
    }
}