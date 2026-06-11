/***Enunciado:** Escribe un programa que reciba N 
 * como argumento, reserve un array de N enteros con malloc, 
 * lo rellene con los cuadrados (0, 1, 4, 9, 16...), lo imprima, 
 * y lo libere.

**Ejemplo:**

```
$ ./cuadrados 5
0 1 4 9 16
```

**Pistas:**

- Convierte argv[1] a entero con atoi o strtol
- malloc(n * sizeof(int))
- No olvides comprobar NULL y llamar a free*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char ** argv){
    int numargs = argc-1;
    char *endptr;
    long n;
    int *array;



    if (numargs != 1){
        fprintf(stderr, "error: usage %s <number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || n < 0){
        fprintf(stderr, "error: %s must be a positive int\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    array = malloc(n * sizeof(int));
    if (array == NULL){
        fprintf(stderr, "error: no memory\n");
        exit(EXIT_FAILURE);
    }

    for (int i= 0; i < n; i++){
        array[i] = i*i;
        printf("%d\n",array[i]);
    }

    free(array);
    exit(EXIT_SUCCESS);
}