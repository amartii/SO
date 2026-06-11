# Ejercicios Interactivos de C - Dia 1: Basicos

Cada ejercicio tiene un enunciado, pistas y la solucion al final. Intenta hacerlo tu primero antes de mirar la solucion. Compila con: `gcc -g -c -Wall -Wshadow -Wvla fichero.c && gcc -g -o fichero fichero.o`

---

## Ejercicio 1.1: Hola Mundo con argumentos

**Enunciado:** Escribe un programa que reciba un nombre como argumento y salude al usuario. Si no recibe argumentos, debe mostrar un mensaje de uso por stderr y salir con EXIT_FAILURE.

**Ejemplo:**
```
$ ./saludo Juan
Hola, Juan!
$ ./saludo
usage: ./saludo <nombre>
```

**Pistas:**
- argc contiene el numero de argumentos (incluyendo el nombre del programa)
- argv[0] es el nombre del programa, argv[1] es el primer argumento
- Usa fprintf(stderr, ...) para errores

**Solucion:** Ver `../soluciones/01-01-saludo.c`

---

## Ejercicio 1.2: Tabla de multiplicar

**Enunciado:** Escribe un programa que reciba un numero como argumento y muestre su tabla de multiplicar del 1 al 10. Convierte el argumento a entero usando atoi().

**Ejemplo:**
```
$ ./tabla 7
7 x 1 = 7
7 x 2 = 14
...
7 x 10 = 70
```

**Pistas:**
- Incluye stdlib.h para atoi()
- Usa un bucle for de 1 a 10

**Solucion:** Ver `../soluciones/01-02-tabla.c`

---

## Ejercicio 1.3: Calculadora simple

**Enunciado:** Escribe un programa que reciba tres argumentos: un numero, un operador (+, -, *, /) y otro numero. Imprime el resultado. Usa switch para seleccionar la operacion.

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

**Solucion:** Ver `../soluciones/01-03-calc.c`

---

## Ejercicio 1.4: Contar mayusculas y minusculas

**Enunciado:** Escribe un programa que reciba una cadena como argumento y cuente cuantas letras mayusculas y minusculas tiene. Usa las funciones de ctype.h.

**Ejemplo:**
```
$ ./contar "Hola Mundo"
Mayusculas: 2
Minusculas: 7
```

**Pistas:**
- Incluye ctype.h para isupper() e islower()
- Recorre la cadena con un bucle while hasta encontrar '\0'

**Solucion:** Ver `../soluciones/01-04-contar.c`

---

## Ejercicio 1.5: Numeros en distintas bases

**Enunciado:** Escribe un programa que reciba un numero decimal como argumento y lo imprima en decimal, octal y hexadecimal.

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

**Solucion:** Ver `../soluciones/01-05-bases.c`

---

## Ejercicio 1.6: Sizeof explorer

**Enunciado:** Escribe un programa que imprima el tamaño en bytes de todos los tipos de datos basicos: char, int, long, unsigned int, float, double, y un puntero a char. Este ejercicio es clave para el examen.

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
- Declara una variable char *ptr para medir el tamaño del puntero

**Solucion:** Ver `../soluciones/01-06-sizeof.c`
