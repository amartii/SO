# TEMA 9: SHELL SCRIPTING EN #!/bin/sh

**Basado en:** Tema 9 (diapositivas) y "Fundamentos de sistemas operativos: una aproximación práctica usando Linux"

---

## PARTE I: CONCEPTOS FUNDAMENTALES

### 1. ¿QUÉ ES UN SCRIPT DE SHELL?

Un **script de shell** es un fichero de texto que contiene una serie de comandos que la shell ejecuta secuencialmente.

**Estructura mínima:**
```sh
#!/bin/sh
# Comentario: esto no se ejecuta
echo "Hola mundo"
exit 0
```

**Requisitos:**
- Primera línea: `#!/bin/sh` (shebang) - indica qué intérprete usar.
- Permisos de ejecución: `chmod +x script.sh`
- Si no termina con `exit`, el script devuelve el status del último comando ejecutado.

**Política POSIX:** Los scripts con `#!/bin/sh` deben usar **solo características POSIX** (IEEE Std 1003.1-2017) para ser **portables** entre sistemas.

---

## PARTE II: PARÁMETROS POSICIONALES

### 2. ACCESO A ARGUMENTOS

La shell proporciona variables especiales para acceder a los argumentos pasados al script:

| Variable | Significado |
|----------|-------------|
| `$0` | Nombre con el que se invocó el script |
| `$1`, `$2`, `$3`, ... | Argumentos posicionales (primero, segundo, tercero, ...) |
| `$#` | Número de argumentos (sin contar `$0`) |
| `$*` | Todos los argumentos como una única cadena: `"$1 $2 $3..."` |
| `$@` | Todos los argumentos separados: `"$1" "$2" "$3"...` |

**Ejemplo: `prueba_params.sh`**
```sh
#!/bin/sh
echo "Nombre del script: $0"
echo "Número de parámetros: $#"
echo "Todos juntos (\$*): $*"
echo "---"

for arg in "$@"
do
    echo "  Argumento: $arg"
done

exit 0
```

**Cómo probarlo:**
```bash
chmod +x prueba_params.sh
./prueba_params.sh uno dos "tres cuatro"
```

**Salida esperada:**
```
Nombre del script: ./prueba_params.sh
Número de parámetros: 3
Todos juntos ($*): uno dos tres cuatro
---
  Argumento: uno
  Argumento: dos
  Argumento: tres cuatro
```

**Diferencia importante entre `"$*"` y `"$@"`:**
```sh
#!/bin/sh
# Con "$*": argumentos se tratan como una única palabra
for x in "$*"
do
    echo "palabra: $x"
done

# Con "$@": cada argumento es una palabra separada
for x in "$@"
do
    echo "palabra: $x"
done
```

---

### 3. COMANDO SHIFT

`shift` desplaza los argumentos posicionales: `$2` pasa a ser `$1`, `$3` pasa a ser `$2`, etc. Se actualiza `$#`.

**Uso común:** Procesar argumentos optativos sin complicar el resto del código.

**Ejemplo: `prueba_shift.sh`**
```sh
#!/bin/sh
echo "Antes de shift: $# argumentos -> $@"

shift
echo "Después de 1 shift: $# argumentos -> $@"

shift 2
echo "Después de 2 shifts más: $# argumentos -> $@"

exit 0
```

**Cómo probarlo:**
```bash
./prueba_shift.sh a b c d e
```

**Salida esperada:**
```
Antes de shift: 5 argumentos -> a b c d e
Después de 1 shift: 4 argumentos -> b c d e
Después de 2 shifts más: 2 argumentos -> d e
```

**Patrón típico de parámetro optativo:**
```sh
#!/bin/sh
debug=false

if test $# -gt 0 -a "$1" = "-d"
then
    debug=true
    shift  # Eliminamos -d de los argumentos
fi

# Ahora el resto del código solo trabaja con argumentos sin opciones
echo "debug = $debug"
echo "Otros argumentos: $@"
```

---

## PARTE III: AGRUPACIONES DE COMANDOS

### 4. AGRUPACIONES EN SUBSHELL Y EN LA SHELL ACTUAL

Podemos agrupar comandos para ejecutarlos como una unidad.

#### 4.1 Agrupación en **subshell** `( ... )`

Crea un nuevo proceso hijo. Los cambios de entorno (cd, export) no afectan a la shell padre.

```sh
#!/bin/sh
pwd
( cd /tmp && ls && pwd )  # Se ejecuta en subshell
pwd  # Seguimos en el directorio original
```

#### 4.2 Agrupación en la **misma shell** `{ ... }`

Se ejecuta en el contexto de la shell actual. Los cambios de entorno SÍ afectan.

```sh
#!/bin/sh
pwd
{ cd /tmp; ls; pwd; }  # Se ejecuta en la misma shell
pwd  # Ahora estamos en /tmp (cambio persiste)
```

**Ejemplo completo: `prueba_agrupaciones.sh`**
```sh
#!/bin/sh

echo "=== SUBSHELL ==="
echo "Antes (pwd): $(pwd)"
(
    cd /tmp
    echo "Dentro subshell (pwd): $(pwd)"
)
echo "Después (pwd): $(pwd)"

echo ""
echo "=== MISMA SHELL ==="
echo "Antes (pwd): $(pwd)"
{
    cd /tmp
    echo "Dentro mismo shell (pwd): $(pwd)"
}
echo "Después (pwd): $(pwd)"

exit 0
```

**Redirecciones con agrupaciones:**
```sh
# Redirigir la salida de múltiples comandos
{ echo "línea 1"; echo "línea 2"; } > fichero.txt

# Procesar con filtros
{ cat a.txt; cat b.txt; } | sort | uniq
```

---

## PARTE IV: SUSTITUCIÓN DE COMANDOS

### 5. SUSTITUCIÓN: EJECUTAR COMANDOS Y USAR SU SALIDA

Dos formas equivalentes:

```sh
variable=$(comando)   # Forma moderna (recomendada)
variable=`comando`    # Forma antigua (backticks)
```

**Ejemplo: `prueba_substitucion.sh`**
```sh
#!/bin/sh

# Guardar número de líneas de un fichero
lineas=$(wc -l < /etc/passwd)
echo "El archivo /etc/passwd tiene $lineas líneas"

# Usar sustitución en un argumento
echo "Contenido de /tmp:"
ls /tmp | wc -l
archivos=$(ls /tmp | wc -l)
echo "Total: $archivos ficheros en /tmp"

# Sustitución anidada
primero=$(echo "hola mundo" | cut -d' ' -f1)
echo "Primera palabra: $primero"

exit 0
```

**Prueba:**
```bash
./prueba_substitucion.sh
```

---

## PARTE V: CONTROL DE FLUJO: if, elif, else, fi

### 6. SENTENCIAS CONDICIONALES IF

Las condiciones se basan en el **estado de salida de un comando**:
- Estado `0` = éxito = verdadero
- Estado ≠ `0` = fallo = falso

```sh
if comando
then
    comandos_si_éxito
elif comando
then
    comandos_si_éxito_segunda_condición
else
    comandos_si_fallo
fi
```

**Ejemplo simple: `prueba_if.sh`**
```sh
#!/bin/sh

fichero="/etc/hostname"

if test -f "$fichero"
then
    echo "El fichero $fichero existe"
    cat "$fichero"
else
    echo "El fichero $fichero no existe"
fi

exit 0
```

**Negar condiciones con `!`:**
```sh
if ! grep -q "usuario" /etc/passwd
then
    echo "El usuario no existe"
fi
```

---

### 7. COMANDO TEST Y OPERADORES

`test` (o `[ ... ]`) comprueba condiciones:

#### **Pruebas de ficheros:**
```sh
test -f fichero    # ¿Existe y es fichero regular?
test -d directorio # ¿Existe y es directorio?
test -e ruta       # ¿Existe (fichero o directorio)?
test -s fichero    # ¿Fichero existe y tiene tamaño > 0?
```

#### **Pruebas de cadenas:**
```sh
test -z cadena     # ¿Cadena vacía?
test -n cadena     # ¿Cadena no vacía?
test "$a" = "$b"   # ¿Cadenas iguales?
test "$a" != "$b"  # ¿Cadenas distintas?
test -n "$var"     # ¿Variable definida?
```

#### **Pruebas de enteros:**
```sh
test $a -eq $b     # ¿Iguales?
test $a -ne $b     # ¿Distintos?
test $a -gt $b     # ¿Mayor que?
test $a -ge $b     # ¿Mayor o igual?
test $a -lt $b     # ¿Menor que?
test $a -le $b     # ¿Menor o igual?
```

**Ejemplo: `prueba_test.sh`**
```sh
#!/bin/sh

# Pruebas de ficheros
if test -f "/etc/passwd"
then
    echo "/etc/passwd es un fichero regular"
fi

# Pruebas de cadenas
nombre="Juan"
if test -n "$nombre"
then
    echo "La variable nombre contiene: $nombre"
fi

# Pruebas de enteros
edad=25
if test $edad -ge 18
then
    echo "$edad años: ¡Mayor de edad!"
fi

# Prueba: ¿fichero no está vacío?
if test -s "/var/log/syslog"
then
    echo "El log /var/log/syslog tiene contenido"
fi

exit 0
```

**Sintaxis alternativa con `[ ... ]`:**
```sh
# Equivalentes:
test -f fichero
[ -f fichero ]

# En un if:
if [ -f fichero ]
then
    echo "Existe"
fi
```

---

### 8. SENTENCIAS CASE

`case` compara una palabra contra **patrones de globbing**:

```sh
case palabra in
patrón1)
    comandos
    ;;
patrón2 | patrón3)
    comandos (múltiples patrones)
    ;;
*)
    comandos_default
    ;;
esac
```

**Ejemplo: `prueba_case.sh`**
```sh
#!/bin/sh

archivo="documento.txt"

case "$archivo" in
*.txt)
    echo "Es un fichero de texto"
    ;;
*.pdf)
    echo "Es un PDF"
    ;;
*.sh)
    echo "Es un script de shell"
    ;;
*)
    echo "Tipo desconocido"
    ;;
esac

exit 0
```

---

## PARTE VI: BUCLES

### 9. BUCLE WHILE

Se ejecuta mientras el comando devuelve éxito (status 0):

```sh
while comando
do
    comandos
done
```

**Ejemplo: `prueba_while.sh`**
```sh
#!/bin/sh

contador=1
while test $contador -le 5
do
    echo "Iteración $contador"
    contador=$((contador + 1))
done

echo "Fin"
exit 0
```

---

### 10. BUCLE FOR

Itera sobre una lista de palabras:

```sh
for variable in palabra1 palabra2 palabra3
do
    comandos  # Usa $variable
done
```

**Ejemplo: `prueba_for.sh`**
```sh
#!/bin/sh

# Iterar sobre literales
for fruta in manzana plátano cereza
do
    echo "Fruta: $fruta"
done

# Iterar sobre sustitución de comando
echo "Números del 1 al 5:"
for num in $(seq 1 5)
do
    echo "  - $num"
done

# Iterar sobre argumentos
echo "Argumentos recibidos:"
for arg in "$@"
do
    echo "  - $arg"
done

exit 0
```

---

## PARTE VII: LECTURA DE ENTRADA: read

### 11. COMANDO READ

`read` lee una línea de la entrada estándar y la guarda en una variable.

```sh
read variable
```

**Ejemplo: `prueba_read.sh`**
```sh
#!/bin/sh

echo "¿Cuál es tu nombre?"
read nombre
echo "¡Hola, $nombre!"

exit 0
```

**Read en bucle (leer fichero línea a línea):**
```sh
while read linea
do
    echo "Línea leída: $linea"
done < fichero.txt
```

**Ejemplo completo: `prueba_read_bucle.sh`**
```sh
#!/bin/sh

# Crear fichero de prueba
cat > /tmp/datos.txt << 'EOF'
línea uno
línea dos
línea tres
EOF

echo "Leyendo /tmp/datos.txt:"
while read linea
do
    echo "  -> $linea"
done < /tmp/datos.txt

rm /tmp/datos.txt
exit 0
```

**Cuidado:** Si usas `read` dentro de un bucle con redirección, ten cuidado con la entrada de otros comandos en el bucle.

---

## PARTE VIII: VARIABLE IFS (Internal Field Separator)

### 12. IFS: SEPARADOR DE CAMPOS

`IFS` define qué caracteres se usan como **separadores de campos**. Por defecto: espacio, tabulador, salto de línea.

**Ejemplo: `prueba_ifs.sh`**
```sh
#!/bin/sh

datos="uno:dos:tres:cuatro"

echo "Con IFS por defecto (espacio):"
for palabra in $datos
do
    echo "  - $palabra"
done

echo ""
echo "Con IFS = ':':"
IFS=:
for palabra in $datos
do
    echo "  - $palabra"
done

exit 0
```

**Cuidado:** Cambiar `IFS` afecta a todo el script. **Usa subshell** para cambios locales:

```sh
#!/bin/sh

datos="uno:dos:tres"

# Cambio LOCAL en subshell
(
    IFS=:
    for palabra in $datos
    do
        echo "  - $palabra"
    done
)

# IFS original aquí
```

---

## PARTE IX: FUNCIONES

### 13. DEFINICIÓN Y USO DE FUNCIONES

Las funciones agrupan código reutilizable. Los parámetros se acceden como `$1`, `$2`, etc.

```sh
nombre_funcion() {
    # comandos
    # Acceso a parámetros: $1, $2, $#, etc.
}

# Ejecutar función
nombre_funcion arg1 arg2
```

**Ejemplo: `prueba_funciones.sh`**
```sh
#!/bin/sh

# Definir función
saludar() {
    nombre=$1
    edad=$2
    echo "¡Hola, $nombre! Tienes $edad años."
}

# Llamar función
saludar "Juan" "25"
saludar "María" "30"

exit 0
```

**Funciones con variables locales (shadowing):**
```sh
#!/bin/sh

variable_global="GLOBAL"

mi_funcion() {
    variable_global="LOCAL"  # Oculta la global dentro de la función
    echo "Dentro de la función: $variable_global"
}

echo "Antes: $variable_global"
mi_funcion
echo "Después: $variable_global"  # ¡Cambio PERSISTE!
```

---

## PARTE X: OPERACIONES ARITMÉTICAS

### 14. CÁLCULOS CON NÚMEROS

```sh
resultado=$((expresión))
```

**Ejemplo: `prueba_aritmetica.sh`**
```sh
#!/bin/sh

a=10
b=3

suma=$((a + b))
resta=$((a - b))
producto=$((a * b))
division=$((a / b))
modulo=$((a % b))

echo "a = $a, b = $b"
echo "Suma: $suma"
echo "Resta: $resta"
echo "Producto: $producto"
echo "División: $division"
echo "Módulo: $modulo"

# Incrementar variable
contador=0
contador=$((contador + 1))
echo "contador = $contador"

exit 0
```

---

## PARTE XI: EXPRESIONES REGULARES

### 15. CONCEPTOS DE EXPRESIONES REGULARES

Una **expresión regular** describe un **lenguaje formal** (conjunto de cadenas).

#### **Caracteres especiales:**

| Carácter | Significado |
|----------|-------------|
| `.` | Cualquier carácter |
| `[abc]` | Uno de a, b o c |
| `[a-z]` | Rango: de a a z |
| `[^abc]` | Cualquiera EXCEPTO a, b, c |
| `^` | Principio de línea |
| `$` | Final de línea |
| `*` | Cero o más veces el anterior |
| `+` | Una o más veces el anterior |
| `?` | Cero o una vez el anterior |
| `\|` | Alternativa (o) |
| `( )` | Agrupación |
| `\` | Escape (carácter literal) |

#### **Ejemplos:**
```
a.c       → Encaja: aac, abc, aXc (cualquier carácter en el medio)
[0-9]+    → Encaja: 1, 123, 9999 (uno o más dígitos)
[a-z]*    → Encaja: "", a, abc, xyz (cero o más minúsculas)
^inicio   → Encaja si la línea COMIENZA con "inicio"
fin$      → Encaja si la línea TERMINA con "fin"
(ab)+     → Encaja: ab, abab, ababab
hola|adiós→ Encaja: hola o adiós
```

---

### 16. GREP Y EGREP

#### **egrep:** Busca líneas que encajen con una expresión regular

```sh
egrep [opciones] 'expresión_regular' [fichero]
```

| Opción | Significado |
|--------|-------------|
| `-v` | Inverso: líneas que NO encajen |
| `-n` | Mostrar número de línea |
| `-q` | Silencioso (solo status) |
| `-i` | Ignorar mayúsculas/minúsculas |
| `-c` | Contar coincidencias |

**Ejemplo: `prueba_egrep.sh`**
```sh
#!/bin/sh

# Crear fichero de prueba
cat > /tmp/test.txt << 'EOF'
Juan 25
María 30
Pedro 22
Ana 28
EOF

echo "=== Líneas con números de 2 dígitos ==="
egrep '[0-9]{2}' /tmp/test.txt

echo ""
echo "=== Nombres que empiezan con J o M ==="
egrep '^[JM]' /tmp/test.txt

echo ""
echo "=== Contar líneas ==="
egrep -c '' /tmp/test.txt

rm /tmp/test.txt
exit 0
```

---

### 17. SED: STREAM EDITOR

`sed` es un **editor de flujos**: aplica comandos a cada línea de entrada.

#### **Comandos básicos:**

| Comando | Significado |
|---------|-------------|
| `d` | Borrar la línea |
| `p` | Imprimir la línea |
| `s/viejo/nuevo/` | Sustituir primera ocurrencia |
| `s/viejo/nuevo/g` | Sustituir todas las ocurrencias |
| `q` | Salir |

#### **Direcciones (dónde actuar):**
```
sed 's/viejo/nuevo/' fichero          # Primera ocurrencia de cada línea
sed '2s/viejo/nuevo/' fichero         # Solo línea 2
sed '1,5s/viejo/nuevo/' fichero       # Líneas 1 a 5
sed '/patrón/s/viejo/nuevo/' fichero  # Líneas que encajen con patrón
```

**Ejemplo: `prueba_sed.sh`**
```sh
#!/bin/sh

# Crear fichero de prueba
cat > /tmp/datos.txt << 'EOF'
hola mundo
adiós mundo
hola amigos
mundo mundo
EOF

echo "=== Original ==="
cat /tmp/datos.txt

echo ""
echo "=== Reemplazar 'mundo' por 'universo' (primera ocurrencia por línea) ==="
sed 's/mundo/universo/' /tmp/datos.txt

echo ""
echo "=== Reemplazar 'mundo' por 'universo' (todas en cada línea) ==="
sed 's/mundo/universo/g' /tmp/datos.txt

echo ""
echo "=== Borrar líneas que contienen 'adiós' ==="
sed '/adiós/d' /tmp/datos.txt

rm /tmp/datos.txt
exit 0
```

#### **Sustituciones con referencias hacia atrás (backreferences):**

Si usas `sed -E` (extended regex) y agrupaciones `(...)`, puedes referir lo que encajó:

```sh
echo "Juan 25" | sed -E 's/([A-Za-z]+) ([0-9]+)/Nombre: \1, Edad: \2/'
# Salida: Nombre: Juan, Edad: 25
```

---

## PARTE XII: FILTROS ÚTILES

### 18. SORT, UNIQ, TAIL, HEAD

#### **sort: Ordenar líneas**
```sh
sort fichero                 # Orden alfanumérico
sort -n fichero              # Orden numérico
sort -k2 -t: fichero         # Ordenar por campo 2 con separador ':'
sort -u fichero              # Ordenar y eliminar duplicados
```

#### **uniq: Eliminar líneas contiguas duplicadas**
```sh
uniq fichero                 # Eliminar duplicados
uniq -c fichero              # Contar duplicados
uniq -d fichero              # Mostrar solo duplicados
```

#### **tail: Últimas líneas; head: Primeras líneas**
```sh
tail -n 3 fichero            # Últimas 3 líneas
head -n 5 fichero            # Primeras 5 líneas
tail -f fichero              # Seguir fichero (útil para logs)
```

**Ejemplo: `prueba_filtros.sh`**
```sh
#!/bin/sh

# Crear fichero
cat > /tmp/numeros.txt << 'EOF'
3
1
4
1
5
9
2
6
EOF

echo "=== Original ==="
cat /tmp/numeros.txt

echo ""
echo "=== Ordenado numéricamente ==="
sort -n /tmp/numeros.txt

echo ""
echo "=== Ordenado y sin duplicados ==="
sort -nu /tmp/numeros.txt

echo ""
echo "=== Últimas 3 líneas ==="
tail -n 3 /tmp/numeros.txt

rm /tmp/numeros.txt
exit 0
```

---

### 19. TR: TRADUCCIÓN DE CARACTERES

`tr` traduce o elimina caracteres:

```sh
tr 'viejo' 'nuevo'   # Traducir cada carácter
tr -d 'caracteres'   # Borrar caracteres
tr 'a-z' 'A-Z'       # Convertir a mayúsculas
```

**Ejemplo: `prueba_tr.sh`**
```sh
#!/bin/sh

texto="Hola Mundo 123"

echo "Original: $texto"
echo "Mayúsculas: $(echo "$texto" | tr 'a-z' 'A-Z')"
echo "Minúsculas: $(echo "$texto" | tr 'A-Z' 'a-z')"
echo "Sin dígitos: $(echo "$texto" | tr -d '0-9')"
echo "Espacios por '_': $(echo "$texto" | tr ' ' '_')"

exit 0
```

---

## PARTE XIII: REDIRECCIONES Y PIPES

### 20. REDIRECCIONES

```sh
comando > fichero       # Salida estándar a fichero (trunca)
comando >> fichero      # Salida estándar al final (append)
comando 2> fichero      # Salida de error a fichero
comando 2>&1            # Salida de error a salida estándar
comando < fichero       # Entrada desde fichero
```

### 21. PIPES (TUBERÍAS)

```sh
comando1 | comando2     # Salida de comando1 → Entrada de comando2
comando1 | comando2 | comando3  # Encadenar comandos
```

**Ejemplo: `prueba_pipes.sh`**
```sh
#!/bin/sh

echo "=== Pipeline simple ==="
echo -e "manzana\nplátano\ncereza" | sort

echo ""
echo "=== Pipeline complejo ==="
echo -e "3\n1\n4\n1\n5" | sort -n | uniq -c | sort -rn

echo ""
echo "=== Redireccionamiento ==="
echo "Error de prueba" 2> /tmp/error.txt
echo "Contenido de error.txt:"
cat /tmp/error.txt
rm /tmp/error.txt

exit 0
```

---

## RESUMEN RÁPIDO DE CONSTRUCCIONES

```sh
# Parámetros
$0, $1, $2, ..., $#, "$@", "$*"

# Control de flujo
if [ -f fichero ]; then ... fi
case $var in patrón) ... ;; esac

# Bucles
for var in lista; do ... done
while comando; do ... done

# Sustitución
$(comando)
`comando`  # Forma antigua

# Aritméticas
$((a + b))

# Variables especiales test
test -f fichero
test -d directorio
test "$a" = "$b"
test $a -eq $b

# Funciones
nombre() { ... }

# Salida estándar y error
> fichero, >> fichero, 2> fichero, 2>&1

# Pipes
cmd1 | cmd2 | cmd3

# Expresiones regulares con egrep
egrep 'patrón' fichero

# Sed
sed 's/viejo/nuevo/g' fichero
sed '/patrón/d' fichero

# Filtros
sort, uniq, tail, head, tr, grep, sed
```

---

## SIGUIENTE PASO

Una vez que domines estos conceptos y hayas practicado con los scripts de ejemplo:

1. **Crea los scripts de prueba** en tu máquina y ejecútalos.
2. **Modifica los ejemplos** para experimentar.
3. **Combina conceptos**: funciones + bucles + test + pipes.

**Cuando estés listo**, pasaremos a resolver el ejercicio **`catlen.sh`** usando toda esta teoría.
