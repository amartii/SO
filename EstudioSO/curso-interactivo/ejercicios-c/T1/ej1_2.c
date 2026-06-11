/* **Enunciado:** Escribe un programa que reciba un numero como argumento 
y muestre su tabla de multiplicar del 1 al 10. Convierte el argumento a 
entero usando atoi().

**Ejemplo:**

```
$ ./tabla 7
7 x 1 = 7
7 x 2 = 14
...
7 x 10 = 70
```

**Pistas:**

- Incluye stdlib.h para atoi()
- Usa un bucle for de 1 a 10*/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv){

    int numargs = argc-1;
    char *endptr;
    long num = strtol(argv[1], &endptr, 10);


    if(numargs != 1){
        fprintf(stderr, "error: usage ./ej1_2 <number>\n");
        exit(EXIT_FAILURE);
    }

    if (endptr == argv[1] || *endptr != '\0'){
        fprintf(stderr, "error: '%s' not a number\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    
    for (int i = 1; i <= 10; i++){
        printf("%ld x %d = %ld\n", num, i, num*i);
    }
    exit(EXIT_SUCCESS);
}