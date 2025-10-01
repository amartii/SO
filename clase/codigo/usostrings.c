#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    char s[] = "hola";
    char s2[10];

    int len;

    len = strlen(s);

    printf("s vale %s\n",s);
    
    exit(EXIT_SUCCESS);
}