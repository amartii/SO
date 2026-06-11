/***Enunciado:** Declara un array 
 * de 5 enteros {10, 20, 30, 40, 50}. 
 * Recorre el array usando solo aritmetica 
 * de punteros (sin usar indices con corchetes) e 
 * imprime cada elemento.

**Pistas:**

- Un puntero p que apunta al array avanza al siguiente elemento con p++
- *p accede al valor actual*/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv){

    int numargs = argc-1;
    int lista [5] = {10, 20, 30, 40, 50};
    int *p = lista;

    if (numargs!=0){
        fprintf(stderr, "error: usage %s\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    
    for (int i = 0; i<5;i++){
        printf("%d\n", *p);
        p++;
    }

    exit(EXIT_SUCCESS);
}