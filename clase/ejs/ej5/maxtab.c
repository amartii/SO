#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void 
usage(void){
    fprintf(stderr, "usage: ./maxtab file\n");
    exit(EXIT_FAILURE);
}

void
error_cant_open(const char *name){
    fprintf(stderr, "error: cant open %s\n", name);
    usage();
}

void
find_max_tab_line(const char *filename){
    FILE *f;
    char linea[256];

    f = fopen(filename,"rb");
    if (f == NULL){
        error_cant_open(filename);
    }
    read_lines(f, linea);

    //hacer una función que lea
    while (fgets(linea, sizeof(linea), f) != NULL) {
        //si la linea es muy larga -> error de que la linea es muy larga >256
        
        //buscar los tabs
        printf("%ld\n",strcspn(linea, "\t"));
        printf("%s", linea);
        //guardar la linea con los tabs mayor
        //si la linea nueva tiene mas o igual tabs guardar esa

    }

    fclose(f);
}

int
main(int argc, char **argv){
    if (argc != 2){
        usage();
    }

    find_max_tab_line(argv[1]);
   // printf("%i: %s", num_tabs, line);
    return EXIT_SUCCESS;
}