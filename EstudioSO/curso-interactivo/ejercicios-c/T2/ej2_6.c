/***Enunciado:** Escribe una funcion
 *  `char *concatenar(const char *a, const char *b)` 
 * que reserve memoria suficiente y devuelva la 
 * concatenacion de ambas cadenas. Pruebala y libera 
 * la memoria.

**Ejemplo:**

```
concatenar("Hola ", "Mundo") -> "Hola Mundo"
```

**Pistas:**

- Tamaño necesario: strlen(a) + strlen(b) + 1
- Copia primero a con strcpy, luego b con strcat*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenar(const char *a, const char *b){
    char *concat;

    concat = malloc(strlen(a) + strlen(b) +1);
    if (concat == NULL){
        fprintf(stderr, "error: no memory");
        exit(EXIT_SUCCESS);
    }
    concat = strcpy(concat, a);
    concat = strcat(concat, b);
    return concat;

}

int 
main(int argc, char **argv){
    int numargs = argc -1; 
    char *c1 = "Hola ";
    char *c2 = "que tal";
    char *c3;

    if (numargs != 0){
        fprintf(stderr, "error: usasge %s\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    c3 = concatenar(c1, c2);
    printf("Palabra 1: %s\n", c1);
    printf("Palabra 2: %s\n", c2);
    printf("Palabra concatenada: %s\n", c3);
    
    exit(EXIT_SUCCESS);


}