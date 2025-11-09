#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// <  >

int 
main(int argc, char **argv){

    long n;
    char *endn, name[256];
    int buffer, i;
    FILE *f, *f2;
    size_t r;

    //compruebo el n de args
    if (argc < 3){
        fprintf(stderr, "usage: ./mysplit N file\n");
       return EXIT_FAILURE;
    }
    
    errno = 0;
    //validación de N 
    n = strtol(argv[1], &endn, 10);
    if (errno == ERANGE || endn == argv[1] || *endn != '\0' || n < 0){
        fprintf(stderr, "error: bad value \"%s\"\n", argv[1]);
        printf("usage: ./mysplit N file\n");
        return EXIT_FAILURE;
    }

    //validación de file
    f = fopen(argv[2], "rb");
    if (f == NULL){
        fprintf(stderr, "error: cant open \"%s\"\n", argv[2]);
        printf("usage: ./mysplit N file\n");
        return EXIT_FAILURE;
    }

    r = fread(buffer[n], sizeof(int), n, f);
    for(i = 0; i < n; i++){
        printf("Buffer[%i]: %i\n", i, buffer[i]);
        snprintf(name, sizeof(name),"%03ld%s", i, argv[2]);
        f2 = fopen(argv[2], "wb");
        fwrite(buffer, sizeof(int), n, f2);
        fclose(f2);
        if (r < n){
            //se termina el archivo origen
        }
        //incrementa el contador de bloque
        

    }
    fclose(f);
    
    printf("Elementos leidos: %zu\n", r);
    

    return EXIT_SUCCESS;
}