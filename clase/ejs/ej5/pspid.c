#include <stdio.h>

void
usage(void){
    fprintf(stderr, "usage: pspid [pid]");
}

int 
main(int argc, char **argv){
    if (argc =! 2){
        usage();
    }
    
}