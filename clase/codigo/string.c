#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    char s[5] = "hola";
    int i;
    for (i=0; i<5; i++){
         printf("el char %d es %c:%x\n",i, s[i], s[i]);
    }
    printf("s vale %s\n",s);
    exit(EXIT_SUCCESS);
}