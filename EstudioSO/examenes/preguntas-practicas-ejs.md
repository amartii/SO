# Preguntas Tipo Test sobre las Practicas (clase/ejs)

Examen de preguntas sobre los programas de las practicas de clase (`clase/ejs`). Cubre
`necho`, `searchstr`, `mysplit`, `ficheros`, `myls`, `maxtab`, `pipes`/`pspid`,
`waitfiles.sh`, `catlen.sh`, `photocol.sh`, `prbars`/`prbarsfork`, `strlib`.

**25 preguntas con 5 opciones (a-e). Una sola correcta.** Las respuestas y explicaciones
estan al final. Para sacarles partido, ten el codigo de cada practica delante.

---

## necho (ej0)  — imprime las ultimas N palabras truncadas a L caracteres

### Pregunta 1
En `necho`, para validar que el argumento `N` es un numero correcto se usa:
```c
errno = 0;
n = strtol(argv[1], &endn, 10);
if (errno == ERANGE || endn == argv[1] || *endn != '\0' || n < 0) { ... }
```
Que comprueba exactamente `*endn != '\0'`?
- [ ] a) Que el numero no se salga del rango de `long`
- [ ] b) Que se consumio TODA la cadena (no hay caracteres sobrantes tras el numero)
- [ ] c) Que el numero es positivo
- [ ] d) Que `argv[1]` no es NULL
- [ ] e) Que la base es 10

### Pregunta 2
`necho` imprime cada palabra con `printf("%.*s\n", (int)l, argv[i])`. Que hace `%.*s`?
- [ ] a) Imprime la cadena en mayusculas
- [ ] b) Imprime como maximo `l` caracteres de la cadena (precision dada por el argumento)
- [ ] c) Repite la cadena `l` veces
- [ ] d) Imprime la cadena rellenada con espacios hasta `l`
- [ ] e) Es un error de formato, no compila

### Pregunta 3
Si se ejecuta `./necho 2 3 hola mundo adios` (N=2 ultimas palabras, L=3), que imprime?
- [ ] a) `hol` y `mun`
- [ ] b) `mun` y `adi`
- [ ] c) `hola` y `mundo`
- [ ] d) `adi`
- [ ] e) `hol`, `mun` y `adi`

### Pregunta 4
En `necho`, si `N` (numero de palabras pedidas) es mayor que las palabras disponibles
(`words = argc - 3`), el codigo hace `if (n > words) n = words;`. Por que?
- [ ] a) Para provocar un error controlado
- [ ] b) Para no leer fuera de `argv` (evitar acceso invalido)
- [ ] c) Porque `strtol` lo exige
- [ ] d) Para truncar las palabras
- [ ] e) No tiene efecto, es codigo muerto

---

## searchstr (ej1) — fgrep en paralelo sobre pares (fichero, cadena)

### Pregunta 5
`searchstr` exige que el numero de argumentos (`args = argc - 1`) sea:
- [ ] a) Impar y mayor que 0
- [ ] b) Par y mayor que 0
- [ ] c) Exactamente 2
- [ ] d) Cualquiera
- [ ] e) Multiplo de 3

### Pregunta 6
Cada hijo ejecuta `execl("/usr/bin/fgrep", "fgrep", argv[i+1], argv[i], (char *)NULL)`.
Que representa cada cosa?
- [ ] a) `argv[i]` es la cadena a buscar y `argv[i+1]` el fichero
- [ ] b) `argv[i]` es el fichero y `argv[i+1]` la cadena a buscar
- [ ] c) Ambos son ficheros
- [ ] d) Ambos son cadenas
- [ ] e) `argv[i]` es una opcion de fgrep

### Pregunta 7
El padre recoge los hijos con `while ((pid = wait(&status)) != -1)` y trata como ERROR los
que salen con `WEXITSTATUS(status) > 1`. Por que `> 1` y no `> 0`?
- [ ] a) Porque grep/fgrep devuelve 0 si encuentra, 1 si NO encuentra (no es error), y >1 si hay error real
- [ ] b) Porque el primer hijo siempre falla
- [ ] c) Porque hay que ignorar el primer hijo
- [ ] d) Es un bug, deberia ser `> 0`
- [ ] e) Porque `wait` devuelve 1 al terminar

### Pregunta 8
Por que `searchstr` crea los procesos en un bucle ANTES de hacer los `wait`?
- [ ] a) Para que los fgrep se ejecuten en PARALELO (no esperar a uno antes de lanzar el siguiente)
- [ ] b) Porque `wait` no funciona dentro del bucle
- [ ] c) Para ahorrar memoria
- [ ] d) Es indiferente, el resultado es el mismo en tiempo
- [ ] e) Para evitar zombies

---

## mysplit (ej2) — parte un fichero en trozos de N bytes

### Pregunta 9
`mysplit` abre el fichero con `fopen(filename, "rb")` y los trozos con `fopen(name, "wb")`.
Por que el modo binario (`b`)?
- [ ] a) Para comprimir
- [ ] b) Para tratar cualquier byte tal cual, sin traducciones de fin de linea
- [ ] c) Es obligatorio en Linux para todo
- [ ] d) Para que `fread` cuente lineas
- [ ] e) No tiene efecto en ningun sistema

### Pregunta 10
Los trozos se nombran con `snprintf(name, sizeof(name), "%03ld%s", parte, filename)`. Para
un fichero `datos.txt` partido en 2 trozos, los nombres son:
- [ ] a) `datos.txt.0` y `datos.txt.1`
- [ ] b) `000datos.txt` y `001datos.txt`
- [ ] c) `datos000.txt` y `datos001.txt`
- [ ] d) `0datos.txt` y `1datos.txt`
- [ ] e) `parte0` y `parte1`

### Pregunta 11
El bucle de lectura termina cuando `fread` devuelve 0, y tambien con `if (r < n) break;` al
final. Que significa que `fread` devuelva menos de `n`?
- [ ] a) Que hubo un error siempre
- [ ] b) Que se llego al final del fichero (ultimo trozo, posiblemente incompleto)
- [ ] c) Que el buffer es demasiado pequeño
- [ ] d) Que hay que volver a abrir el fichero
- [ ] e) Que `n` era negativo

### Pregunta 12
Si `malloc(n)` falla, `mysplit` hace `error_no_memory(); fclose(f); return EXIT_FAILURE;`.
Que buena practica ilustra el `fclose(f)` antes de salir?
- [ ] a) Liberar recursos (el fichero abierto) aunque haya error
- [ ] b) Forzar el flush del buffer de lectura
- [ ] c) Es innecesario, el SO lo cierra
- [ ] d) Evitar un deadlock
- [ ] e) Cerrar el pipe

---

## ficheros (ej2) — E/S binaria vs texto

### Pregunta 13
En `ficheros.c` se escribe con `fwrite(buffer, sizeof(int), 5, f)` un array `{0,10,20,30,40}`.
Cuantos BYTES ocupa el fichero `a.txt` resultante (enteros de 4 bytes)?
- [ ] a) 5
- [ ] b) 10
- [ ] c) 20
- [ ] d) 40
- [ ] e) Depende del contenido

### Pregunta 14
El fichero `b.txt` se escribe con `fprintf(f, "%d\n", i*100)`. En que se diferencia de
`a.txt` (escrito con `fwrite`)?
- [ ] a) En nada, son identicos
- [ ] b) `b.txt` es texto legible ("0\n100\n...") y `a.txt` son bytes binarios crudos
- [ ] c) `a.txt` es texto y `b.txt` binario
- [ ] d) `b.txt` ocupa menos siempre
- [ ] e) `a.txt` no se puede leer con `fread`

### Pregunta 15
Para releer los enteros de texto de `b.txt` se usa `while (fscanf(f, "%i", &v) == 1)`. Por
que se compara con `== 1`?
- [ ] a) Porque hay un solo numero por linea
- [ ] b) Porque `fscanf` devuelve el NUMERO DE CAMPOS leidos con exito; 1 significa que leyo el entero
- [ ] c) Porque `1` es el descriptor de stdout
- [ ] d) Porque el bucle solo debe correr una vez
- [ ] e) Porque `v` empieza en 1

---

## myls (ej3) — un ls simplificado

### Pregunta 16
`myls` recorre el directorio con `opendir`/`readdir` y obtiene metadatos con
`lstat(ent->d_name, &statbuf)`. Por que `lstat` y no `stat`?
- [ ] a) `lstat` es mas rapido
- [ ] b) `lstat` NO sigue los enlaces simbolicos, asi puede mostrarlos como tipo enlace ('l')
- [ ] c) `stat` no existe
- [ ] d) `lstat` lista el directorio entero de una vez
- [ ] e) Son equivalentes

### Pregunta 17
La funcion `what_type` hace `switch (mode & S_IFMT)`. Para que sirve `& S_IFMT`?
- [ ] a) Extrae los bits de PERMISOS del fichero
- [ ] b) Extrae los bits que indican el TIPO de fichero (regular, dir, enlace...)
- [ ] c) Convierte el modo a octal
- [ ] d) Comprueba si el fichero es ejecutable
- [ ] e) Da el tamaño del fichero

### Pregunta 18
`readdir` en `myls` devolvera, entre otras, las entradas:
- [ ] a) Solo ficheros regulares
- [ ] b) Solo subdirectorios
- [ ] c) Todas las entradas, incluidas `.` y `..`
- [ ] d) Solo ficheros ocultos
- [ ] e) Solo enlaces simbolicos

---

## maxtab (ej4) — linea con mas tabuladores al inicio

### Pregunta 19
`maxtab` detecta lineas demasiado largas con
`if (strchr(linea, '\n') == NULL && !feof(f))`. Que situacion detecta?
- [ ] a) Que la linea esta vacia
- [ ] b) Que `fgets` lleno el buffer sin encontrar `\n` (la linea no cabe entera)
- [ ] c) Que el fichero no existe
- [ ] d) Que hay tabuladores
- [ ] e) Que se llego al final del fichero

### Pregunta 20
Para quedarse con la mejor linea, `maxtab` usa `strdup(linea)` y libera la anterior con
`free(*max_linea)`. Por que `strdup` y no guardar el puntero `linea` directamente?
- [ ] a) Porque `linea` es un buffer reutilizado en cada `fgets`; hay que COPIAR su contenido
- [ ] b) Porque `strdup` es mas rapido que `=`
- [ ] c) Porque `linea` es de solo lectura
- [ ] d) Porque `free` necesita memoria estatica
- [ ] e) No hace falta, es codigo redundante

---

## pipes / pspid (ej5) — `ps aux | wc -l` con pipe

### Pregunta 21
En `pipes.c`/`pspid.c`, despues de crear los dos hijos, el PADRE hace `close(fd[0])` y
`close(fd[1])`. Que pasaria si NO cerrara el extremo de escritura `fd[1]`?
- [ ] a) Nada, funciona igual
- [ ] b) El proceso `wc -l` (lector) nunca recibiria EOF y se quedaria bloqueado
- [ ] c) `ps` fallaria
- [ ] d) Se duplicaria la salida
- [ ] e) Recibiria SIGPIPE

### Pregunta 22
El primer hijo hace `dup2(fd[1], STDOUT_FILENO)` y luego `execlp("ps", ...)`. Que consigue?
- [ ] a) Que `ps` lea del pipe
- [ ] b) Que la salida estandar de `ps` vaya al pipe en vez de a la pantalla
- [ ] c) Que `ps` escriba en un fichero
- [ ] d) Que `ps` ignore el pipe
- [ ] e) Que el padre reciba la salida directamente

### Pregunta 23
El segundo hijo hace `dup2(fd[0], STDIN_FILENO)` antes de `execlp("wc", "wc", "-l", ...)`.
Resultado del conjunto:
- [ ] a) Cuenta las lineas de la salida de `ps` (equivale a `ps | wc -l`)
- [ ] b) Cuenta los caracteres del teclado
- [ ] c) Escribe el numero de procesos en un fichero
- [ ] d) Lista los procesos sin contarlos
- [ ] e) Da error porque falta un tercer proceso

---

## Scripts de shell (ej6, ej7, ej8)

### Pregunta 24
`waitfiles.sh` define `queda_algo()` que recorre los ficheros y hace `return 0` en cuanto
encuentra uno que aun existe. El bucle principal es `while queda_algo "$@"; do sleep 1; done`.
Que hace el script?
- [ ] a) Borra los ficheros pasados
- [ ] b) Espera (sondeando cada segundo) hasta que TODOS los ficheros indicados hayan desaparecido, luego imprime `done`
- [ ] c) Crea los ficheros que faltan
- [ ] d) Cuenta cuantos ficheros hay
- [ ] e) Espera a que aparezca el primer fichero

### Pregunta 25
En `catlen.sh`, para cada `.txt` se calcula
`longitud=$(printf "%s\n" "$fichero" | wc -c); longitud=$((longitud-1))` y luego
`cat "$fichero" >> "$longitud.output"`. Por que se RESTA 1 a `wc -c`?
- [ ] a) Porque `wc -c` cuenta tambien el `\n` que añade `printf`, y no forma parte del nombre
- [ ] b) Porque los nombres empiezan en 0
- [ ] c) Para dejar sitio al `.output`
- [ ] d) Porque `wc -c` cuenta de mas por un bug
- [ ] e) No deberia restarse, es un error

---

# RESPUESTAS Y EXPLICACIONES

1. **b)** `*endn` apunta al primer caracter NO consumido por `strtol`. Si no es `'\0'`,
   sobraba texto (p.ej. "12abc") y el numero es invalido. Junto con `errno==ERANGE` (rango)
   y `endn==argv[1]` (no se leyo nada) forma la validacion completa de un entero.
2. **b)** `%.*s` toma la precision de un argumento `int` (aqui `l`): imprime como mucho `l`
   caracteres de la cadena. Asi `necho` trunca cada palabra a L caracteres.
3. **b)** N=2 -> las 2 ultimas palabras: "mundo" y "adios". L=3 -> truncadas: `mun` y `adi`.
4. **b)** Si pides mas palabras de las que hay, `start = argc - n` se saldria por debajo de
   `argv` valido. Limitando `n` a `words` se evita leer fuera del vector.
5. **b)** Los argumentos van en pares (fichero, cadena), asi que deben ser PAR y > 0; si no,
   error. (`if ((args % 2) != 0 || args == 0)`.)
6. **b)** `execl(..., "fgrep", argv[i+1], argv[i], NULL)`: para `fgrep PATRON FICHERO`, el
   patron es `argv[i+1]` (la cadena) y el fichero `argv[i]`. (Ojo al orden invertido respecto
   a como se pasan en la linea de comandos del propio searchstr.)
7. **a)** Convencion de grep/fgrep: 0 = encontrado, 1 = no encontrado (NO es error), 2+ =
   error real. Por eso solo se considera fallo `WEXITSTATUS > 1`.
8. **a)** Lanzar todos los fork primero y esperar despues permite que los fgrep corran a la
   vez (paralelismo). Si hicieras `wait` dentro del bucle, serian secuenciales.
9. **b)** El modo `b` evita traducciones (en algunos sistemas) y trata el contenido como
   bytes crudos, necesario para partir CUALQUIER fichero (incluido binario) sin corromperlo.
10. **b)** El formato `"%03ld%s"` antepone el numero de parte a 3 cifras con ceros y luego el
    nombre: `000datos.txt`, `001datos.txt`.
11. **b)** `fread` devuelve menos de `n` cuando alcanza el final del fichero: ese es el ultimo
    trozo (posiblemente mas pequeño). Por eso `if (r < n) break;`.
12. **a)** Aunque vaya a salir con error, cierra el fichero ya abierto para no dejar recursos
    colgando. Buen habito de gestion de errores (liberar lo adquirido).
13. **c)** 5 enteros x 4 bytes = **20 bytes**. `fwrite(buffer, sizeof(int), 5, f)` escribe los
    bytes crudos de los 5 `int`.
14. **b)** `b.txt` es TEXTO legible (`fprintf` con `%d\n`): "0\n100\n200\n300\n400\n". `a.txt`
    son los bytes binarios de los enteros (no legibles como texto).
15. **b)** `fscanf` devuelve el numero de conversiones logradas. `== 1` significa que leyo con
    exito el entero; cuando deja de poder (EOF), devuelve algo distinto de 1 y el bucle acaba.
16. **b)** `lstat` no sigue enlaces simbolicos, por eso `myls` puede etiquetarlos como `'l'`.
    Con `stat` veria el destino del enlace, no el enlace.
17. **b)** `S_IFMT` es la mascara de los bits de TIPO. `mode & S_IFMT` aisla el tipo para
    compararlo con `S_IFDIR`, `S_IFREG`, `S_IFLNK`... (los permisos son otros bits).
18. **c)** `readdir` devuelve TODAS las entradas del directorio, incluidas `.` y `..`.
19. **b)** `fgets` corta al llenar el buffer. Si no hay `\n` y no es fin de fichero, la linea
    no cabia entera -> se considera "line too long".
20. **a)** `linea` es el mismo buffer que `fgets` sobrescribe en cada vuelta. Para conservar
    la mejor linea hay que DUPLICAR su contenido con `strdup` (memoria propia que luego se
    libera).
21. **b)** Mientras quede ALGUN extremo de escritura abierto (aunque sea en el padre), el
    lector `wc -l` no ve EOF y se bloquea. Por eso el padre debe cerrar `fd[1]` (y `fd[0]`).
22. **b)** `dup2(fd[1], STDOUT_FILENO)` hace que stdout del hijo sea el extremo de escritura
    del pipe; al ejecutar `ps`, su salida va al pipe.
23. **a)** Primer hijo: `ps` -> pipe. Segundo hijo: pipe -> stdin de `wc -l`. En conjunto
    cuenta las lineas de `ps`, igual que `ps | wc -l`.
24. **b)** `queda_algo` devuelve exito (0) si AUN existe alguno; el `while` repite mientras
    quede alguno, durmiendo 1 s (polling). Cuando ya no queda ninguno, sale e imprime `done`.
25. **a)** `printf "%s\n"` añade un `\n`, asi que `wc -c` cuenta un byte de mas (el salto).
    Restar 1 deja la longitud real del nombre del fichero.

---

## Resumen de patrones que se repiten en TODAS las practicas

- **Validacion de argumentos** con `if (argc != ...) usage();` y mensajes a `stderr`.
- **Validacion de numeros** con `strtol` + `errno` + `endptr` + `*end == '\0'` (no `atoi`).
- **Comprobar TODO retorno** de syscalls (`fork`, `pipe`, `dup2`, `close`, `open`, `wait`).
- **Patron pipe**: `pipe` -> `fork` -> en hijos `dup2` + `close` de ambos extremos + `exec`;
  el padre cierra los dos extremos y hace `wait` por cada hijo.
- **fgrep/grep paralelo**: un fork+exec por tarea, esperar a todos despues; interpretar el
  codigo de salida (0/1/>1).
- **Scripts**: funciones (`usage`, helpers), `test` para condiciones, comillas en `"$@"`,
  polling con `sleep`, y trabajar con `(cd "$dir" && ...)` cuando hace falta.
