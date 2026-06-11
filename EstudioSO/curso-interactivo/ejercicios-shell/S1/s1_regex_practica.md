# Práctica de glob, regex, grep, find y awk

## Mini apuntes

### 1. Glob vs regex
- Glob: patrones de shell. Se usan en `find -name`, en nombres de ficheros y en la expansión del intérprete.
- Regex: expresiones regulares. Se usan en `grep`, `sed`, `awk` y a veces en otras herramientas.
- Glob no es regex.

### 2. Diferencias rápidas
- `grep`: regex básicas.
- `grep -E`: regex extendidas.
- `grep -F`: texto literal, sin regex.
- `find -name`: glob, no regex.

### 3. Piezas clave de regex
- `^`: inicio de línea.
- `$`: fin de línea.
- `.`: cualquier carácter.
- `*`: cero o más repeticiones del carácter anterior.
- `[...]`: uno de varios caracteres.
- `[^...]`: ninguno de esos caracteres.

### 4. Cuándo usar cada cosa
- Usa `grep` si quieres filtrar líneas.
- Usa `grep -F` si quieres buscar texto literal.
- Usa `find` si quieres buscar ficheros por nombre.
- Usa `awk` si quieres filtrar y además imprimir campos.

## Ejercicios

### Ejercicio 1: empezar por una letra
En un fichero llamado `palabras.txt`, muestra las líneas que empiezan por `a`.

Pista: `grep '^a' palabras.txt`

### Ejercicio 2: terminar por texto
Muestra las líneas que terminan en `txt`.

Pista: `grep 'txt$' palabras.txt`

### Ejercicio 3: buscar dos alternativas
Muestra las líneas que contengan `hola` o `adios`.

Pista: `grep -E 'hola|adios' palabras.txt`

### Ejercicio 4: búsqueda literal
Busca la cadena `a.b` sin que el punto signifique “cualquier carácter”.

Pista: `grep -F 'a.b' palabras.txt`

### Ejercicio 5: ficheros con extensión concreta
Lista los ficheros `.c` y `.h` de un directorio.

Pista: `find . -name '*.[ch]'`

### Ejercicio 6: otros ficheros
Cuenta los ficheros que no sean `.c`, `.h` ni `.txt`.

Pista: `find . -type f ! -name '*.c' ! -name '*.h' ! -name '*.txt' | wc -l`

### Ejercicio 7: campos con awk
De `/etc/passwd`, muestra usuario y shell separados por `:`.

Pista: `awk -F: '{print $1 ":" $7}' /etc/passwd`

### Ejercicio 8: filtrar por patrón y contar
Cuenta cuántas líneas de un fichero contienen la palabra `root`.

Pista: `grep -c 'root' fichero`

### Ejercicio 9: clasificar nombres
En un directorio, imprime solo los nombres de ficheros que terminen en `.md`.

Pista: `find . -type f -name '*.md'`

### Ejercicio 10: combinar find y grep
Lista todos los ficheros y quédate solo con los que no terminen en `.txt`.

Pista: `find . -type f | grep -vE '\.txt$'`

## Mini chuleta mental
- Empieza por `^`
- Termina con `$`
- Cualquier cosa: `.`
- Repetición: `*`
- Uno de varios: `[...]`
- No uno de varios: `[^...]`
- Literal: `grep -F`

## Qué debes recordar para examen
- `find -name` usa glob, no regex.
- `grep -E` es más cómodo para `|` y paréntesis.
- `grep -F` sirve para texto literal.
- `awk` es útil cuando quieres filtrar y extraer campos a la vez.
