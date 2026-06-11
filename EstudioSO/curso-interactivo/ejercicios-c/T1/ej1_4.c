/***Enunciado:** Escribe un programa que reciba una cadena como 
 * argumento y cuente cuantas letras mayusculas y minusculas tiene. 
 * Usa las funciones de ctype.h.

**Ejemplo:**

```
$ ./contar "Hola Mundo"
Mayusculas: 2
Minusculas: 7
```

**Pistas:**

- Incluye ctype.h para isupper() e islower()
- Recorre la cadena con un bucle while hasta encontrar '\0'

**Solucion:** Ver `../soluciones/01-04-contar.c`*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int
main (int argc, char **argv){
    int numargs = argc -1;
    int may = 0;
    int min = 0;

    if(numargs != 1){
        fprintf(stderr, "error: usage %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i= 0; argv[1][i] != '\0'; i++){
        if (isupper(argv[1][i])){
            may++;
        }else if(islower(argv[1][i])){
            min++;
        }
    }
    
    printf("Mayusculas:%d\n", may);
    printf("Minusculas:%d\n", min);
    exit(EXIT_SUCCESS);

}