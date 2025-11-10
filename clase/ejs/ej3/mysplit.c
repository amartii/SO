#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// <  >

int 
main(int argc, char **argv){

    long n;
    char *endn, name[256];
    unsigned char *buffer;
    FILE *f, *f2;
    size_t r;
    long parte = 0;

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

    buffer = malloc(n);
    if (buffer == NULL){
        fprintf(stderr, "error: no memory\n");
        fclose(f);
        return EXIT_FAILURE;
    }

    while(1){
        r = fread(buffer, 1, n, f);
        if(r== 0){
            break;
        }
        snprintf(name, sizeof(name),"%03ld%s", parte, argv[2]);
        f2 = fopen(name, "wb");
        if(f2 == NULL){
            fprintf(stderr, "error: cant create \"%s\"\n", name);
            fclose(f);
            return EXIT_FAILURE;
        }
        fwrite(buffer, 1, r, f2);
        fclose(f2);
        parte++;
        if (r < n){
            break;
        }
    }

    free(buffer);
    fclose(f);

    return EXIT_SUCCESS;
}