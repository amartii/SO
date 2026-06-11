/***Enunciado:** Escribe un programa que reciba un nombre como argumento y 
 * salude al usuario. Si no recibe argumentos, debe mostrar un mensaje de 
 * uso por stderr y salir con EXIT_FAILURE.

**Ejemplo:**

```
$ ./saludo Juan
Hola, Juan!
$ ./saludo
usage: ./saludo <nombre>
```

**Pistas:**

- argc contiene el numero de argumentos (incluyendo el nombre del programa)
- argv[0] es el nombre del programa, argv[1] es el primer argumento
- Usa fprintf(stderr, ...) para errores*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
main(int argc, char **argv){
    int numargs = argc-1;

    if (numargs!= 1){
        fprintf(stderr, "error: usage ./ej1_1 <nombre>\n");
        exit(EXIT_FAILURE);

    }else{
        printf("Hola %s !\n", argv[1]);
    }
    
    exit(EXIT_SUCCESS); 
}