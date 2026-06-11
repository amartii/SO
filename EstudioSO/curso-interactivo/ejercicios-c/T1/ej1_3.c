/***Enunciado:** Escribe un programa que reciba tres argumentos: 
 * un numero, un operador (+, -, *, /) y otro numero. 
 * Imprime el resultado. Usa switch para seleccionar la operacion.

**Ejemplo:**

```
$ ./calc 10 + 5
15
$ ./calc 10 / 3
3
```

**Pistas:**

- El operador es argv[2][0] (primer caracter del segundo argumento)
- En el switch, usa 'break' en cada caso
- Cuidado con la division por cero

**Solucion:** Ver `../soluciones/01-03-calc.c`*/

#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char **argv){
    int numargs = argc -1;
    char *endptr1, *endptr2;
    long n1, n2; 

    if (numargs != 3){
        fprintf(stderr, "error: usage %s <number> <operartor> <number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n1 = strtol(argv[1], &endptr1, 10);
    n2 = strtol(argv[3], &endptr2, 10); 
    if (endptr1 == argv[1] || *endptr1 != '\0'){
        fprintf(stderr, "error: %s not a number\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (endptr2 == argv[3] || *endptr2 != '\0'){
        fprintf(stderr, "error: %s not a number\n", argv[3]);
        exit(EXIT_FAILURE);
    }

    switch (argv[2][0]){
        case '+':
            printf("%ld\n",n1 + n2);
            break;
        case '-':
            printf("%ld\n",n1 - n2);
            break;
        case '*':
            printf("%ld\n",n1 * n2);
            break;
        case '/':
            if (n2 == 0){
                fprintf(stderr, "error: division by 0\n");
                exit(EXIT_FAILURE);
            }
            printf("%ld\n",n1 / n2);
            break;
        default:
            fprintf(stderr, "error: %s not an operator\n", argv[2]);
            exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

}