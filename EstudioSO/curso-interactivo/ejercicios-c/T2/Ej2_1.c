/***Enunciado:** Escribe una funcion 
 * `swap(int *a, int *b)` que intercambie los 
 * valores de dos enteros. Pruebala desde main 
 * imprimiendo antes y despues.

**Ejemplo:**

```
Antes: a=10, b=20
Despues: a=20, b=10
```

**Pistas:**

- Necesitas una variable temporal
- Pasa las direcciones con &*/

//&a es la dirección del parámetro local a
//*a es el valor al que apunto

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int tmp = *a;
     *a = *b;
     *b = tmp;
}

int
main(int argc, char **argv){
    int numargs= argc-1;
    int n1 = 10;
    int n2 = 20;
    int *a = &n1;
    int *b = &n2;

    if(numargs !=0){
        fprintf(stderr, "error: usage %s", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    printf("Antes: a=%d, b=%d\n",*a,*b);
    swap(&n1,&n2);
    printf("Después: a=%d, b=%d\n",*a,*b);
    exit(EXIT_SUCCESS);
}