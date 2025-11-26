#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// <  >
void
usage(void){
    fprintf(stderr, "usage: ./mysplit N file\n");
    exit(EXIT_FAILURE);
}

void
error_bad_value(const char *s){
    fprintf(stderr, "error: bad value \"%s\"\n", s);
    usage();
}

void error_cant_open(const char *s){
    fprintf(stderr, "error: cant open \"%s\"\n", s);
    usage();
}

void
error_no_memory(void){
    fprintf(stderr, "error: no memory\n");
}

void
error_cant_create(const char *s){
    fprintf(stderr, "error: cant create \"%s\"\n", s);
}

int split_file(long n, const char *filename){
    unsigned char *buffer;
    FILE *f, *f2;
    size_t r;
    long parte = 0;
    char name[256];

    f = fopen(filename, "rb");
    if (f == NULL)
    {
        error_cant_open(filename);
        return EXIT_FAILURE;
    }

    buffer = malloc(n);
    if (buffer == NULL)
    {
        error_no_memory();
        fclose(f);
        return EXIT_FAILURE;
    }

    while (1)
    {
        r = fread(buffer, 1, n, f);
        if (r == 0)
        {
            break;
        }
        snprintf(name, sizeof(name), "%03ld%s", parte, filename);
        f2 = fopen(name, "wb");
        if (f2 == NULL)
        {
            error_cant_create(name);
            free(buffer);
            fclose(f);
            return EXIT_FAILURE;
        }
        fwrite(buffer, 1, r, f2);
        fclose(f2);
        parte++;
        if (r < n)
        {
            break;
        }
    }

    free(buffer);
    fclose(f);

    return EXIT_SUCCESS;
}

int 
main(int argc, char **argv){

    long n;
    char *endn;

    if (argc < 3){
        usage();
    }
    
    errno = 0;
    n = strtol(argv[1], &endn, 10);
    if (errno == ERANGE || endn == argv[1] || *endn != '\0' || n < 0){
        error_bad_value(argv[1]);
    }

    split_file(n, argv[2]);

    return EXIT_SUCCESS;
}