/***Enunciado:** Escribe un programa que reciba un fichero como argumento 
 * y muestre su tamaño en bytes. Usa la llamada stat().

**Ejemplo:**

```
$ ./filesize /etc/passwd
Tamaño: 2847 bytes
```

**Pistas:**

- Incluye sys/stat.h
- Declara struct stat sb
- stat(argv[1], &sb) rellena la estructura
- sb.st_size tiene el tamaño*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void usage(void){
    fprintf(stderr, "error: usage ./ej3_2\n");
    exit(EXIT_FAILURE);
}

int
main(int argc, char **argv){
    int numargs = argc - 1;
    struct stat sb;

    if(numargs != 1){
        usage();
    }

    if (stat(argv[1], &sb) < 0){
        fprintf(stderr, "error: cant get %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

   printf("Tamaño en bytes: %lld\n", (long  long) sb.st_size);
   exit(EXIT_SUCCESS);
}