# Ejercicios Interactivos de Shell - Dia 7: Shell Avanzado y Filtros

---

## Ejercicio S2.1: Contar lineas con palabras

**Enunciado:** Escribe un script que reciba un fichero y una palabra, y cuente cuantas lineas contienen esa palabra.

```
$ ./contarpal.sh /etc/passwd root
Lineas con 'root': 2
```

**Pistas:**
- grep -c cuenta coincidencias
- O usa grep | wc -l

**Solucion:** Ver `../soluciones/s02-01-contarpal.sh`

---

## Ejercicio S2.2: Sustituir texto con sed

**Enunciado:** Escribe un script que reciba un fichero, una palabra vieja y una nueva, y muestre el fichero con todas las ocurrencias sustituidas (sin modificar el original).

```
$ echo "hola mundo hola" > test.txt
$ ./sustituir.sh test.txt hola adios
adios mundo adios
```

**Pistas:**
- sed "s/$viejo/$nuevo/g" "$fichero"

**Solucion:** Ver `../soluciones/s02-02-sustituir.sh`

---

## Ejercicio S2.3: Top 5 palabras mas frecuentes

**Enunciado:** Escribe un script que reciba un fichero y muestre las 5 palabras mas frecuentes con su conteo.

```
$ ./toppal.sh fichero.txt
  15 el
  12 de
   8 que
   7 en
   5 un
```

**Pistas:**
- tr ' ' '\n' convierte espacios en saltos de linea (una palabra por linea)
- sort | uniq -c | sort -rn | head -5

**Solucion:** Ver `../soluciones/s02-03-toppal.sh`

---

## Ejercicio S2.4: Extraer campo de /etc/passwd con awk

**Enunciado:** Escribe un script que imprima el nombre de usuario y su shell de login de /etc/passwd.

```
$ ./usuarios.sh
root:/bin/bash
daemon:/usr/sbin/nologin
...
```

**Pistas:**
- awk -F: '{ print $1 ":" $7 }' /etc/passwd

**Solucion:** Ver `../soluciones/s02-04-usuarios.sh`

---

## Ejercicio S2.5: Buscar ficheros grandes

**Enunciado:** Escribe un script que busque todos los ficheros mayores de N kilobytes en un directorio y los liste ordenados por tamaño.

```
$ ./grandes.sh /var/log 100
150K /var/log/syslog
200K /var/log/auth.log
```

**Pistas:**
- find "$dir" -type f -size +"${n}k"
- Para cada fichero, muestra su tamaño con du -k

**Solucion:** Ver `../soluciones/s02-05-grandes.sh`

---

## Ejercicio S2.6: catlen (basado en practica real)

**Enunciado:** Escribe un script que reciba un directorio. Primero borra todos los .output del directorio. Luego, para cada fichero .txt, calcula la longitud de su nombre (sin la ruta) y concatena su contenido a un fichero llamado "N.output" donde N es esa longitud.

```
$ ./catlen.sh midir
# Si midir contiene hola.txt (8 chars) y mundo.txt (9 chars):
# Genera 8.output con contenido de hola.txt
# Genera 9.output con contenido de mundo.txt
```

**Pistas:**
- longitud=$(printf "%s\n" "$fichero" | wc -c); longitud=$((longitud - 1))
- cat "$fichero" >> "$longitud.output"
- Trabaja dentro del directorio con (cd "$1" && ...)

**Solucion:** Ver `../soluciones/s02-06-catlen.sh`

---

## Ejercicio S2.7: photocol simplificado (basado en practica real)

**Enunciado:** Escribe un script que reciba un directorio destino y uno o mas directorios origen. Copia todas las imagenes (.jpg, .png) de los origenes al destino, normalizando los nombres: todo a minusculas, espacios a guiones, .jpeg a .jpg. Si hay colision de nombres, error y limpia.

```
$ ./photocol.sh coleccion fotos1 fotos2
```

**Pistas:**
- find para buscar imagenes
- tr 'A-Z' 'a-z' para minusculas
- tr ' ' '-' para reemplazar espacios
- sed 's/\.jpeg$/.jpg/' para normalizar extension
- Comprueba colisiones antes de copiar

**Solucion:** Ver `../soluciones/s02-07-photocol.sh`

---

## Ejercicio S2.8: Pipeline complejo

**Enunciado:** Usando SOLO la linea de comandos (un oneliner con pipes), resuelve:
1. Contar cuantos procesos tiene cada usuario en el sistema
2. Mostrar los 3 usuarios con mas procesos

**Solucion:**
```sh
ps aux | awk 'NR>1 {print $1}' | sort | uniq -c | sort -rn | head -3
```

Explicacion: ps aux lista todos los procesos, awk extrae el primer campo (usuario) saltando la cabecera, sort agrupa, uniq -c cuenta, sort -rn ordena por conteo descendente, head -3 muestra los 3 primeros.
