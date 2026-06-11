# Ejercicios Practicos de Shell Script para Examen

Ejercicios de **escribir scripts** seleccionados por ser los que mas caen. Cada uno tiene
enunciado, ejemplo de uso, pistas y **solucion completa**. Estan escritos para `/bin/sh`
(POSIX), que es lo habitual en examen; funcionan tambien en bash.

**Ejecutar:**
```bash
chmod +x script.sh
./script.sh argumentos
# o bien:
sh script.sh argumentos
```

Recuerda las reglas de oro:
- Comillas SIEMPRE: `"$var"`, `"$@"`.
- Comparar numeros con `-eq -lt -gt -le -ge`; cadenas con `=` y `!=`.
- Comprobar el numero de argumentos con `$#`.
- `$?` es el codigo de salida del ultimo comando; `exit N` para devolver el tuyo.

Indice:
1. Validar argumentos y comprobar tipo de fichero
2. Sumar los numeros pasados como argumentos
3. Tabla de multiplicar (bucle)
4. Contar ficheros por extension en un directorio
5. Renombrar añadiendo prefijo a ficheros .txt
6. Backup con fecha de un directorio
7. Buscar y mostrar las lineas mas largas
8. Promedio de una columna numerica (awk)
9. Histograma de extensiones
10. Comprobar si un proceso esta vivo / esperar a un fichero
11. Menu interactivo con case
12. Procesar un CSV: filtrar y sumar
13. Encontrar duplicados por nombre
14. Recorrer recursivamente con find y actuar

---

## Ejercicio 1: Validar argumentos y tipo de fichero

**Enunciado:** Recibe una ruta. Di si es un fichero regular, un directorio, un enlace
simbolico, o si no existe.

```
$ ./tipofich.sh /etc/passwd
/etc/passwd: fichero regular
$ ./tipofich.sh /etc
/etc: directorio
```

**Pistas:** `test -f` regular, `-d` directorio, `-L` enlace, `-e` existe.

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 1
then
    echo "usage: $0 <ruta>" >&2
    exit 1
fi

ruta="$1"

if test ! -e "$ruta"
then
    echo "$ruta: no existe" >&2
    exit 1
fi

if test -L "$ruta"
then
    echo "$ruta: enlace simbolico"
elif test -d "$ruta"
then
    echo "$ruta: directorio"
elif test -f "$ruta"
then
    echo "$ruta: fichero regular"
else
    echo "$ruta: otro tipo"
fi
```
**Clave:** comprueba `-L` ANTES que `-f`/`-d`, porque un enlace a un fichero tambien pasa
`-f` (test sigue el enlace por defecto).

---

## Ejercicio 2: Sumar los argumentos numericos

**Enunciado:** Suma todos los numeros pasados como argumentos. Si no hay argumentos, error.

```
$ ./suma.sh 3 10 7
20
```

**Solucion:**
```sh
#!/bin/sh

if test $# -eq 0
then
    echo "usage: $0 n1 n2 ..." >&2
    exit 1
fi

total=0
for n in "$@"
do
    total=$((total + n))
done
echo "$total"
```
**Clave:** `$((...))` hace aritmetica entera. `"$@"` expande cada argumento como una
palabra independiente (respeta espacios).

---

## Ejercicio 3: Tabla de multiplicar

**Enunciado:** Recibe un numero N e imprime su tabla del 1 al 10.

```
$ ./tabla.sh 3
3 x 1 = 3
3 x 2 = 6
...
3 x 10 = 30
```

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 1
then
    echo "usage: $0 <numero>" >&2
    exit 1
fi

n="$1"
i=1
while test "$i" -le 10
do
    echo "$n x $i = $((n * i))"
    i=$((i + 1))
done
```
**Clave:** bucle `while test ... do ... done`. Acuerdate de incrementar `i` o sera bucle
infinito.

---

## Ejercicio 4: Contar ficheros por extension

**Enunciado:** Recibe un directorio y cuenta cuantos ficheros hay de cada extension.

```
$ ./contarext.sh /etc
12 conf
3 d
...
```

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 1 || test ! -d "$1"
then
    echo "usage: $0 <directorio>" >&2
    exit 1
fi

find "$1" -type f -name '*.*' | sed 's/.*\.//' | sort | uniq -c | sort -rn
```
**Clave:** `sed 's/.*\.//'` borra todo hasta el ultimo punto, dejando la extension.
`sort | uniq -c` cuenta repeticiones. El primer `-name '*.*'` evita ficheros sin extension.

---

## Ejercicio 5: Renombrar añadiendo prefijo

**Enunciado:** Añade el prefijo "old_" a todos los ficheros .txt del directorio actual.

```
$ ./renombrar.sh
nota.txt -> old_nota.txt
```

**Solucion:**
```sh
#!/bin/sh

for f in *.txt
do
    if test -f "$f"
    then
        mv -- "$f" "old_$f"
        echo "$f -> old_$f"
    fi
done
```
**Clave:** el `test -f "$f"` evita que si no hay ningun .txt el patron `*.txt` se procese
literalmente. `mv --` protege contra nombres que empiezan por `-`.

---

## Ejercicio 6: Backup con fecha

**Enunciado:** Recibe un directorio y crea un tar.gz con la fecha y hora en el nombre.

```
$ ./backup.sh midir
Creado backup-midir-20260611-1530.tar.gz
```

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 1 || test ! -d "$1"
then
    echo "usage: $0 <directorio>" >&2
    exit 1
fi

dir="$1"
base=$(basename "$dir")
fecha=$(date +%Y%m%d-%H%M)
nombre="backup-$base-$fecha.tar.gz"

tar czf "$nombre" "$dir" || {
    echo "error al crear el backup" >&2
    exit 1
}
echo "Creado $nombre"
```
**Clave:** `$(comando)` captura la salida. `date +%Y%m%d-%H%M` formatea la fecha.
`basename` quita la ruta dejando solo el nombre.

---

## Ejercicio 7: Las N lineas mas largas de un fichero

**Enunciado:** Recibe un fichero y un numero N; muestra las N lineas mas largas.

```
$ ./larga.sh /etc/passwd 3
```

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 2
then
    echo "usage: $0 <fichero> <n>" >&2
    exit 1
fi

awk '{ print length, $0 }' "$1" | sort -rn | head -n "$2" | cut -d' ' -f2-
```
**Clave:** `awk '{print length, $0}'` antepone la longitud a cada linea; `sort -rn` ordena
por ese numero descendente; `cut -d' ' -f2-` elimina la columna de longitud.

---

## Ejercicio 8: Promedio de una columna

**Enunciado:** Recibe un fichero con numeros (uno por linea) y calcula su media.

```
$ printf '10\n20\n30\n' | ./media.sh
20
```

**Solucion (lee de stdin o de fichero):**
```sh
#!/bin/sh

awk '{ suma += $1; n++ } END { if (n > 0) print suma / n; else print 0 }' "$@"
```
**Clave:** awk acumula en `suma`, cuenta en `n`, y en el bloque `END` imprime la media.
Pasar `"$@"` permite tanto fichero como tuberia (si no hay args, awk lee stdin).

---

## Ejercicio 9: Histograma de extensiones (barras)

**Enunciado:** Como el ejercicio 4 pero dibuja una barra de almohadillas proporcional al
conteo.

```
ext txt: ##########
ext log: ###
```

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 1 || test ! -d "$1"
then
    echo "usage: $0 <directorio>" >&2
    exit 1
fi

find "$1" -type f -name '*.*' | sed 's/.*\.//' | sort | uniq -c |
while read -r cuenta ext
do
    barra=""
    i=0
    while test "$i" -lt "$cuenta"
    do
        barra="$barra#"
        i=$((i + 1))
    done
    echo "ext $ext: $barra"
done
```
**Clave:** `while read -r cuenta ext` lee dos campos por linea de la salida de `uniq -c`.
El `-r` evita que se interpreten las barras invertidas.

---

## Ejercicio 10: Esperar a que aparezca un fichero

**Enunciado:** Recibe un nombre de fichero. Espera (comprobando cada segundo) hasta que el
fichero exista, y entonces avisa. Maximo 30 intentos.

```
$ ./waitfile.sh /tmp/listo
Esperando /tmp/listo ...
/tmp/listo ha aparecido
```

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 1
then
    echo "usage: $0 <fichero>" >&2
    exit 1
fi

fich="$1"
intentos=0
echo "Esperando $fich ..."
while test ! -e "$fich"
do
    intentos=$((intentos + 1))
    if test "$intentos" -ge 30
    then
        echo "timeout: $fich no aparecio" >&2
        exit 1
    fi
    sleep 1
done
echo "$fich ha aparecido"
```
**Clave:** patron de espera activa con `sleep 1` y un contador de seguridad para no esperar
infinitamente.

---

## Ejercicio 11: Menu interactivo con case

**Enunciado:** Muestra un menu: (1) fecha, (2) usuarios conectados, (3) espacio en disco,
(q) salir. Repite hasta que el usuario pulse q.

**Solucion:**
```sh
#!/bin/sh

while true
do
    echo "=== MENU ==="
    echo "1) Fecha"
    echo "2) Usuarios conectados"
    echo "3) Espacio en disco"
    echo "q) Salir"
    printf "Opcion: "
    read -r opcion

    case "$opcion" in
        1) date ;;
        2) who ;;
        3) df -h ;;
        q|Q) echo "Adios"; break ;;
        *) echo "Opcion no valida" >&2 ;;
    esac
    echo
done
```
**Clave:** `case` con patrones; `q|Q` acepta ambas; `*)` es el caso por defecto. Cada rama
termina en `;;`. El `case` cierra con `esac`.

---

## Ejercicio 12: Procesar un CSV (filtrar y sumar)

**Enunciado:** Tienes un CSV `ventas.csv` con `producto,categoria,importe`. Recibe una
categoria y suma los importes de esa categoria.

```
$ ./totalcat.sh ventas.csv libros
Total libros: 145.50
```

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 2
then
    echo "usage: $0 <fichero.csv> <categoria>" >&2
    exit 1
fi

fichero="$1"
cat="$2"

total=$(awk -F, -v c="$cat" '$2 == c { suma += $3 } END { printf "%.2f", suma }' "$fichero")
echo "Total $cat: $total"
```
**Clave:** `-F,` fija la coma como separador; `-v c="$cat"` pasa una variable de shell a
awk; `$2 == c` filtra por categoria; `printf "%.2f"` formatea con 2 decimales.

---

## Ejercicio 13: Encontrar ficheros con nombre duplicado

**Enunciado:** Recibe un directorio y lista los nombres de fichero (sin ruta) que aparecen
mas de una vez en el arbol.

```
$ ./dup.sh /proyecto
3 README.md
2 config.json
```

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 1 || test ! -d "$1"
then
    echo "usage: $0 <directorio>" >&2
    exit 1
fi

find "$1" -type f | sed 's#.*/##' | sort | uniq -c |
    awk '$1 > 1 { print }'
```
**Clave:** `sed 's#.*/##'` borra todo hasta la ultima barra dejando el nombre base (se usa
`#` como delimitador para no chocar con las `/`). `awk '$1 > 1'` filtra los repetidos.

---

## Ejercicio 14: Recorrer recursivamente y actuar (limpiar temporales)

**Enunciado:** Recibe un directorio. Borra todos los ficheros `.tmp` y `.bak`, pero antes
muestra cuantos va a borrar y pide confirmacion.

**Solucion:**
```sh
#!/bin/sh

if test $# -ne 1 || test ! -d "$1"
then
    echo "usage: $0 <directorio>" >&2
    exit 1
fi

dir="$1"
n=$(find "$dir" -type f \( -name '*.tmp' -o -name '*.bak' \) | wc -l)

if test "$n" -eq 0
then
    echo "No hay ficheros temporales"
    exit 0
fi

printf "Se borraran %s ficheros. Continuar? (s/n): " "$n"
read -r resp
if test "$resp" = "s"
then
    find "$dir" -type f \( -name '*.tmp' -o -name '*.bak' \) -delete
    echo "Borrados"
else
    echo "Cancelado"
fi
```
**Clave:** `find ... \( -name A -o -name B \)` combina condiciones con OR (los parentesis
van escapados). `-delete` borra lo encontrado. Siempre cuenta y confirma antes de borrar.

---

## Chuleta de filtros (memorizar)

| Tarea | Comando |
|-------|---------|
| Contar lineas/palabras/bytes | `wc -l / -w / -c` |
| Filtrar lineas que contienen X | `grep X` (`-v` invierte, `-c` cuenta, `-i` ignora caso) |
| Sustituir texto | `sed 's/viejo/nuevo/g'` |
| Borrar lineas | `sed '/patron/d'` |
| Extraer campo N (sep coma) | `cut -d, -f N` o `awk -F, '{print $N}'` |
| Ordenar numerico desc | `sort -rn` |
| Contar repetidos | `sort \| uniq -c` |
| Top N frecuentes | `sort \| uniq -c \| sort -rn \| head -N` |
| Espacio a salto de linea | `tr ' ' '\n'` |
| Mayusculas | `tr 'a-z' 'A-Z'` |
| Buscar ficheros | `find DIR -type f -name 'PATRON'` |

## Errores de shell que cuestan puntos

- Olvidar las comillas: `rm $f` falla si `$f` tiene espacios -> `rm "$f"`.
- Usar `=` para numeros: usa `-eq`. `=` compara cadenas.
- No comprobar `$#` antes de usar `$1`.
- Olvidar `fi`, `esac`, `done`.
- Esperar que las variables se hereden sin `export`.
- Confundir `$*` (todo junto) con `"$@"` (cada arg por separado, lo correcto casi siempre).
