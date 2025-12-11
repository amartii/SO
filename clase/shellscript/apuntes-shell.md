# Apuntes Shell Scripting

## Conceptos Generales

- **No entregar scripts de bash**
- Siempre comenzar con `#!/bin/sh` → **IMPORTANTE** (empieza por esta línea siempre)
- Hay que otorgarle permisos de ejecución

## Primer Script: hola.sh

```sh
#!/bin/sh
echo hola
exit 0
```

### Comandos Relacionados

```bash
ls -l hola.sh              # Ver permisos
chmod +x hola.sh           # Dar permisos de ejecución
./hola.sh                  # Ejecutar el script
echo $?                    # Ver status de salida
```

## Segundo Script: hola2.sh - Argumentos Posicionales

```sh
#!/bin/sh
echo hola $1
echo todos los argumentos son: $*
exit 0
```

**Ejecutar:** `./hola2.sh juan alberto`

### Variables de Argumentos

| Variable | Descripción |
|----------|-------------|
| `$1, $2, ...` | Parámetros posicionales (lo que le pasamos al script) |
| `$#` | Número de argumentos que se pasan |
| `$*` | Todos los argumentos |

## Tercer Script: hola3.sh - Comando shift

```sh
#!/bin/sh
echo hola $1
echo todos los argumentos son: $*
shift
echo todos los argumentos son: $*
echo '$1' es $1
exit 0
```

**Ejecutar:** `./hola3.sh juan alberto`

### Comando shift

El comando `shift` desplaza argumentos hacia la izquierda descartando el primero.

## Sustitución de Comandos

```sh
fecha=$(date)    # o fecha=`date`
echo $fecha
```

## Condicionales: Comando true y false

En shell:
- `true` es un programa que sale con éxito (0)
- `false` es un programa que sale con fallo (1)

```sh
if true
then
    echo estoy dentro del if
fi
```

## Bucles: for

### Script for.sh

```sh
#!/bin/sh
echo hola me han pasado $# argumentos
for i in $*
do
    echo un param: $i
done
exit 0
```

**Ejecutar:** `./for.sh uno dos tres`

**Salida:**
```
hola me han pasado 3 parametros
un param: uno
un param: dos
un param: tres
```

## Diferencias de Impresión: `$@` vs `"$@"` vs `$*` vs `"$*"`

### Script examples.sh

```sh
#!/bin/sh
echo 'con $@'
for i in $@
do
    echo "<$i>"
done

echo 'con "$@"'
for i in "$@"
do
    echo "<$i>"
done

echo 'con $*'
for i in $*
do
    echo "<$i>"
done

echo 'con "$*"'
for i in "$*"
do
    echo "<$i>"
done

exit 0
```

**Lo mejor es usar `"$@"` entre comillas**

## Lectura de Líneas

```sh
#!/bin/sh
ls -l $1 | while read line
do  
    echo una linea: $line
done
exit 0
```

## Variable IFS

- `IFS` → no jugar con ella
- Contiene: espacio, tabulación y salto de línea

## Funciones

```sh
hello(){
    echo hola $1
    shift
    echo adios $1
}

hello uno dos
```

## Comando TEST

### Test con Ficheros

```sh
test -f <ruta>    # Verifica si existe el fichero y si es un fichero
test -d <ruta>    # Verifica si existe la ruta y es un directorio
```

### Test con Cadenas

```sh
test -n String1         # Si la longitud de la string no es cero
test -z String1         # Si la longitud de la string es cero
String1 = String2       # Si son iguales
String1 != String2      # Si no son idénticas
String1                 # Si la string no es nula
```

### Test con Números

```sh
test $# -ne 1    # Verifica el número de argumentos (not equal)
```

## Script con Validación

```sh
#!/bin/sh
if test $# -ne 1
then
    echo usage: hola.sh path >&2
    exit 1
fi
```

---

**Nota:** Los ejemplos se deben ejecutar otorgando permisos con `chmod +x` antes de correr cada script.