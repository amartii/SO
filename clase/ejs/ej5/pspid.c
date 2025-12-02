#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void
usage(void){
    fprintf(stderr, "usage: ./pspid [pid]\n");
    exit(EXIT_FAILURE);
}

void
error_bad_value(void){
    fprintf(stderr, "error: bad pid\n");
    usage();
}

int 
main(int argc, char **argv){
    long n;
    char *endn;

    if (argc != 2){
        usage();
    }
    
    errno = 0;
    n = strtol(argv[1], &endn, 10);
    if (errno == ERANGE || endn == argv[1] || *endn != '\0' || n < 0){
        error_bad_value();
    }
    
}