#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // strlen: calcula la longitud de una cadena, excluyendo el carácter nulo.
    char s1[50] = "Hola";
    printf("strlen(\"%s\") = %zu\n", s1, strlen(s1));

    // strcpy: copia la cadena origen en la cadena destino.
    char s2[50];
    strcpy(s2, s1);  // s2 ahora contiene "Hola"
    printf("strcpy: s2 = \"%s\"\n", s2);

    // strncpy: copia los primeros n caracteres de la cadena origen en destino.
    char s3[50] = "MundoBonito";
    strncpy(s2, s3, 5);     // s2 contiene "Mundo", faltaría el carácter nulo si no lo pones manualmente.
    s2[5] = '\0';
    printf("strncpy de s3 a s2 (5): \"%s\"\n", s2);

    // strcat: concatena la cadena origen al final de la destino.
    strcpy(s1, "Hola ");
    strcat(s1, "mundo");   // s1 ahora es "Hola mundo"
    printf("strcat: \"%s\"\n", s1);

    // strncat: concatena n caracteres de la cadena origen a la destino.
    strncat(s1, " cruel", 3);  // añade " cr" al final (3 letras)
    printf("strncat (3 letras): \"%s\"\n", s1);

    // strcmp: compara dos cadenas. Retorna 0 si son iguales, <0 si la primera es "menor", >0 si la primera es "mayor".
    printf("strcmp(\"abc\", \"abc\") = %d\n", strcmp("abc", "abc"));
    // strncmp: compara los primeros n caracteres de dos cadenas.
    printf("strncmp(\"abc\", \"abd\", 2) = %d\n", strncmp("abc", "abd", 2));

    // strchr: retorna un puntero a la primera aparición de un carácter en una cadena, o NULL si no existe.
    char *pch = strchr(s1, 'o');
    if (pch) printf("strchr('o') primera en: \"%s\"\n", pch);

    // strrchr: retorna un puntero a la última aparición de un carácter en una cadena.
    pch = strrchr(s1, 'o');
    if (pch) printf("strrchr('o') última en: \"%s\"\n", pch);

    // strstr: retorna un puntero al primer substring que coincide con la cadena buscada.
    char *found = strstr(s1, "mun");
    if (found) printf("strstr: Encontrado \"mun\": \"%s\"\n", found);

    // strcspn: cuenta cuántos caracteres iniciales NO pertenecen al conjunto.
    printf("strcspn(\"abc123\", \"123\") = %zu\n", strcspn("abc123", "123")); // da 3, pues 'a','b','c' no están en "123"

    // strspn: cuenta cuántos caracteres iniciales SÍ están dentro del conjunto dado.
    printf("strspn(\"abc123\", \"abc\") = %zu\n", strspn("abc123", "abc")); // da 3, pues 'a','b','c' sí están en "abc"

    // strtok: separa la cadena en tokens utilizando un delimitador, retorna punteros consecutivos a cada token.
    char tokString[50] = "verde,azul,amarillo";
    char *token = strtok(tokString, ",");
    while (token != NULL) {
        printf("strtok token: \"%s\"\n", token);
        token = strtok(NULL, ",");
    }

    // memcpy: copia n bytes de memoria desde fuente a destino.
    char src[] = "copia";
    char dest[10];
    memcpy(dest, src, 6); // copia "copia" y el carácter nulo '\0'
    printf("memcpy dest: \"%s\"\n", dest);

    // memmove: igual que memcpy, pero seguro para solapamientos (cuando src y dest se sobreponen).
    memmove(dest + 1, dest, 5); // mueve "copia" un byte adelante (desplazado)
    dest[6] = '\0';
    printf("memmove destino desplazado: \"%s\"\n", dest);

    // memset: inicializa n bytes de memoria con un valor.
    char buf[10];
    memset(buf, 'X', 5); // pone 'X' en las 5 primeras posiciones
    buf[5] = '\0';
    printf("memset: \"%s\"\n", buf);

    return 0;
}
