/*## Ejercicio 1.5: Numeros en distintas bases

**Enunciado:** Escribe un programa que reciba 
un numero decimal como argumento y lo imprima en decimal, 
octal y hexadecimal.

**Ejemplo:**

```
$ ./bases 255
Decimal: 255
Octal: 377
Hexadecimal: ff
```

**Pistas:**

- Usa %d para decimal, %o para octal, %x para hexadecimal
- Convierte el argumento con atoi()

**Solucion:** Ver `../soluciones/01-05-bases.c`*/
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv){
    int numargs = argc -1;
    char *endptr1;
    unsigned int n1;

    if (numargs != 1){
        fprintf(stderr, "error: usage %s <decimal number>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 

    n1= strtol(argv[1],&endptr1,10);  //la clave está en leer el numero y que sea decimal

    if (endptr1 == argv[1] || *endptr1 != '\0'){
        fprintf(stderr, "error: not a number\n");
        exit(EXIT_SUCCESS);
    }

    printf("Decimal: %d\n", n1);
    printf("Octal: %o\n", n1);
    printf("Hexadecimal: %x\n", n1);
    exit(EXIT_SUCCESS);
}