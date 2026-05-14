# Ejercicios Interactivos de C - Dia 2: Punteros y Memoria Dinamica

---

## Ejercicio 2.1: Intercambio con punteros

**Enunciado:** Escribe una funcion `swap(int *a, int *b)` que intercambie los valores de dos enteros. Pruebala desde main imprimiendo antes y despues.

**Ejemplo:**
```
Antes: a=10, b=20
Despues: a=20, b=10
```

**Pistas:**
- Necesitas una variable temporal
- Pasa las direcciones con &

**Solucion:** Ver `../soluciones/02-01-swap.c`

---

## Ejercicio 2.2: Recorrer array con punteros

**Enunciado:** Declara un array de 5 enteros {10, 20, 30, 40, 50}. Recorre el array usando solo aritmetica de punteros (sin usar indices con corchetes) e imprime cada elemento.

**Pistas:**
- Un puntero p que apunta al array avanza al siguiente elemento con p++
- *p accede al valor actual

**Solucion:** Ver `../soluciones/02-02-puntarray.c`

---

## Ejercicio 2.3: Duplicar cadena con malloc

**Enunciado:** Escribe una funcion `char *duplicar(const char *s)` que reserve memoria con malloc, copie la cadena, y devuelva el puntero. El llamador debe liberar la memoria. Pruebala desde main.

**Pistas:**
- Necesitas reservar strlen(s) + 1 bytes (para el '\0')
- Usa strcpy para copiar
- Comprueba si malloc devolvio NULL
- No olvides free() en main

**Solucion:** Ver `../soluciones/02-03-duplicar.c`

---

## Ejercicio 2.4: Array dinamico

**Enunciado:** Escribe un programa que reciba N como argumento, reserve un array de N enteros con malloc, lo rellene con los cuadrados (0, 1, 4, 9, 16...), lo imprima, y lo libere.

**Ejemplo:**
```
$ ./cuadrados 5
0 1 4 9 16
```

**Pistas:**
- Convierte argv[1] a entero con atoi o strtol
- malloc(n * sizeof(int))
- No olvides comprobar NULL y llamar a free

**Solucion:** Ver `../soluciones/02-04-cuadrados.c`

---

## Ejercicio 2.5: Detectar errores de memoria (EXAMEN)

**Enunciado:** El siguiente codigo tiene multiples errores de memoria. Identifica todos los errores sin compilar. Luego corrigelos.

```c
#include <stdlib.h>
#include <string.h>

char *crear_saludo(const char *nombre) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Hola, %s", nombre);
    return buffer;  // Error 1
}

int main() {
    char *p = malloc(10);
    memset(p, 0, sizeof(p));  // Error 2
    
    char *q = malloc(5);
    q = "hola";  // Error 3
    free(q);
    
    int *arr = malloc(100 * sizeof(int));
    free(arr);
    arr[0] = 42;  // Error 4
    
    return 0;
}
```

**Errores a encontrar:**
1. Retornar puntero a variable local (buffer se destruye al salir)
2. sizeof(p) es 8 (tamaño del puntero), no 10 (tamaño del bloque)
3. Se pierde la memoria de malloc(5), y luego free de un literal causa crash
4. Uso de memoria despues de free (use-after-free)

**Solucion corregida:** Ver `../soluciones/02-05-errores.c`

---

## Ejercicio 2.6: Concatenar strings con malloc

**Enunciado:** Escribe una funcion `char *concatenar(const char *a, const char *b)` que reserve memoria suficiente y devuelva la concatenacion de ambas cadenas. Pruebala y libera la memoria.

**Ejemplo:**
```
concatenar("Hola ", "Mundo") -> "Hola Mundo"
```

**Pistas:**
- Tamaño necesario: strlen(a) + strlen(b) + 1
- Copia primero a con strcpy, luego b con strcat

**Solucion:** Ver `../soluciones/02-06-concat.c`

---

## Ejercicio 2.7: Pregunta tipo examen - sizeof

**Sin compilar**, responde: que imprime este programa?

```c
#include <stdio.h>
#include <stdlib.h>

void f(int arr[]) {
    printf("%zu\n", sizeof(arr));
}

int main() {
    int a[5] = {1,2,3,4,5};
    int *p = malloc(20);
    printf("%zu\n", sizeof(a));
    printf("%zu\n", sizeof(p));
    f(a);
    free(p);
    return 0;
}
```

**Respuesta:**
```
20   (sizeof de array en pila = 5 * 4 = 20)
8    (sizeof de puntero en 64 bits = 8)
8    (array degradado a puntero como parametro = 8)
```
