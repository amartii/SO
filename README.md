# Sistemas Operativos

Repositorio de apuntes y código de la asignatura de Sistemas Operativos, centrado en programación en C y desarrollo sobre GNU/Linux.

## Estructura del repositorio

### `/clase`
Materiales organizados por tema:

- **`/apuntes`**: PDFs teóricos de la asignatura
- **`/C`**: Programas en C desarrollados durante las clases
- **`/ejs`**: Ejercicios resueltos
- **`/shellscript`**: Scripts de shell

### `/curso c`
Material complementario para el aprendizaje de C

### `/pruebas`
Código experimental y pruebas de concepto

## Compilación

Los programas se compilan con los siguientes flags obligatorios:

```bash
gcc -Wall -Wshadow -Wvla -g -c archivo.c
gcc -g -o ejecutable archivo.o
