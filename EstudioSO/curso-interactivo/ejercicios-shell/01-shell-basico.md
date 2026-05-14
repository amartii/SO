# Ejercicios Interactivos de Shell - Dia 6: Shell Basico

Todos los scripts deben empezar con `#!/bin/sh` (POSIX, no bash).

---

## Ejercicio S1.1: Hola con argumentos

**Enunciado:** Escribe un script que salude a cada argumento recibido. Sin argumentos, muestra error por stderr.

```
$ ./saluda.sh Juan Maria
Hola Juan
Hola Maria
```

**Pistas:**
- Usa `for name in "$@"` para iterar
- Comprueba `$# -lt 1` para validar

**Solucion:** Ver `../soluciones/s01-01-saluda.sh`

---

## Ejercicio S1.2: Verificar tipo de fichero

**Enunciado:** Escribe un script que reciba una ruta y diga si es un fichero regular, directorio, enlace simbolico, o no existe.

```
$ ./tipofich.sh /tmp
/tmp es un directorio
$ ./tipofich.sh /etc/passwd
/etc/passwd es un fichero regular
```

**Pistas:**
- test -f para fichero regular
- test -d para directorio
- test -L para enlace simbolico (comprobar ANTES de -f y -d)

**Solucion:** Ver `../soluciones/s01-02-tipofich.sh`

---

## Ejercicio S1.3: Calculadora en shell

**Enunciado:** Escribe un script que reciba tres argumentos (num op num) y muestre el resultado. Usa case para el operador y $((...)) para la aritmetica.

```
$ ./calc.sh 10 + 5
15
$ ./calc.sh 10 '*' 3
30
```

**Pistas:**
- El * debe ir entre comillas simples al llamarlo
- Usa case "$2" in para el operador
- Division por cero: comprueba antes

**Solucion:** Ver `../soluciones/s01-03-calc.sh`

---

## Ejercicio S1.4: Contar ficheros por extension

**Enunciado:** Escribe un script que reciba un directorio y cuente cuantos ficheros hay de cada extension (.txt, .c, .h, otros).

```
$ ./contarext.sh /home/user/proyecto
.c: 5
.h: 3
.txt: 2
otros: 10
```

**Pistas:**
- Usa find para listar ficheros
- Extrae extension con ${fichero##*.}
- Usa un case o contadores manuales

**Solucion:** Ver `../soluciones/s01-04-contarext.sh`

---

## Ejercicio S1.5: Renombrar en lote

**Enunciado:** Escribe un script que reciba una extension vieja y una nueva, y renombre todos los ficheros del directorio actual. Ejemplo: cambiar .txt a .md.

```
$ ./renombrar.sh txt md
Renombrado: notas.txt -> notas.md
Renombrado: readme.txt -> readme.md
```

**Pistas:**
- for f in *."$1"
- nuevo="${f%.$1}.$2" (quita la extension vieja y pone la nueva)
- mv "$f" "$nuevo"

**Solucion:** Ver `../soluciones/s01-05-renombrar.sh`

---

## Ejercicio S1.6: Funciones y return

**Enunciado:** Escribe un script con una funcion `es_par` que reciba un numero y devuelva 0 si es par, 1 si es impar. Usa la funcion para clasificar los argumentos.

```
$ ./pares.sh 2 5 8 11
2 es par
5 es impar
8 es par
11 es impar
```

**Pistas:**
- Dentro de la funcion: $(($1 % 2))
- return $resultado
- Comprueba el retorno con $? o directamente en un if

**Solucion:** Ver `../soluciones/s01-06-pares.sh`

---

## Ejercicio S1.7: waitfiles (basado en practica real)

**Enunciado:** Escribe un script que reciba una lista de ficheros y espere (polling cada segundo) hasta que todos hayan sido borrados. Si algun argumento no es un fichero regular al inicio, error.

```
$ touch /tmp/a /tmp/b
$ ./waitfiles.sh /tmp/a /tmp/b &
# (en otra terminal, borra los ficheros)
$ rm /tmp/a /tmp/b
done
```

**Pistas:**
- Funcion queda_algo() que comprueba si algun fichero existe
- Bucle while con sleep 1
- Comprobacion inicial de que todos son ficheros regulares

**Solucion:** Ver `../soluciones/s01-07-waitfiles.sh`

---

## Ejercicio S1.8: Pregunta tipo examen - variables heredadas

**Sin ejecutar**, que imprime?

```bash
$ mipid=20
$ bash
$ echo "$mipid"
```

**Respuesta:** Imprime una linea vacia (nada). La variable mipid es de shell, no de entorno. Al crear un nuevo bash, no se hereda. Solo se heredan variables exportadas con `export`.
