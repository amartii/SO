/* **Enunciado:** Escribe un programa que imprima el tamaño 
en bytes de todos los tipos de datos basicos: 
char, int, long, unsigned int, float, double, y un puntero a char. 
Este ejercicio es clave para el examen.

**Ejemplo de salida esperada (en 64 bits):**

```
sizeof(char) = 1
sizeof(int) = 4
sizeof(long) = 8
sizeof(unsigned int) = 4
sizeof(float) = 4
sizeof(double) = 8
sizeof(char*) = 8
```

**Pistas:**

- Usa %zu como formato para sizeof (es de tipo size_t)
- Declara una variable char *ptr para medir el tamaño del puntero*/
#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char **argv){
    int numargs = argc -1;

    if (numargs != 0){
        fprintf(stderr, "error: usage %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("sizeof(char) = %zu\n", sizeof(char));
    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("sizeof(long) = %zu\n", sizeof(long));
    printf("sizeof(unsigned int) = %zu\n", sizeof(unsigned int));
    printf("sizeof(float) = %zu\n", sizeof(float));
    printf("sizeof(double) = %zu\n", sizeof(double));
    printf("sizeof(char*) = %zu\n", sizeof(char *));

    exit(EXIT_SUCCESS);
}