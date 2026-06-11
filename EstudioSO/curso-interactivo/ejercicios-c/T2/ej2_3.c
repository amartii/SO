/***Enunciado:** Escribe una funcion `char *duplicar(const char *s)` 
 * que reserve memoria con malloc, copie la cadena, y 
 * devuelva el puntero. El llamador debe liberar la memoria. 
 * Pruebala desde main.

**Pistas:**

- Necesitas reservar strlen(s) + 1 bytes (para el '\0')
- Usa strcpy para copiar
- Comprueba si malloc devolvio NULL
- No olvides free() en main*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *duplicar(const char *s){
    char *copia;

    copia = malloc(strlen(s) + 1);
    if (copia==NULL){
        fprintf(stderr, "error: no memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy(copia,s);
    return copia;

}

int 
main (int argc, char ** argv){
    int numargs = argc -1;

    char *original = "hola que tal";
    char *copia;

    if (numargs != 0){
        fprintf(stderr, "error: usage %s\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    printf("Original:%s\n",original);
    copia = duplicar(original);
    printf("Copia:%s\n",copia);
    free(copia);

    exit (EXIT_SUCCESS);

}