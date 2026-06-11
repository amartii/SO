# Errores Comunes en Examenes de Sistemas Operativos

Este documento recopila los errores mas frecuentes que cometen los estudiantes. Leelo la noche antes del examen.

---

## 1. Errores de Punteros y Memoria

| Error | Por que esta mal | Correccion |
|-------|-----------------|------------|
| Retornar puntero a variable local | La variable se destruye al salir | Usar malloc dentro de la funcion |
| sizeof(puntero) en vez de sizeof(*puntero) | Da 8 bytes, no el tamaño del bloque | Guardar el tamaño o usar sizeof del tipo |
| malloc sin comprobar NULL | Si no hay memoria, crash | Siempre comprobar: if (p == NULL) |
| free y luego usar el puntero | Use-after-free, comportamiento indefinido | Poner p = NULL despues de free |
| p = "literal" despues de p = malloc() | Se pierde la memoria de malloc | Usa strcpy(p, "literal") |
| memset con sizeof(puntero) | Solo inicializa 8 bytes | Usar el tamaño real del bloque |
| Doble free | Corrompe el heap | Free solo una vez por cada malloc |

---

## 2. Errores de Fork y Procesos

| Error | Por que esta mal | Correccion |
|-------|-----------------|------------|
| printf sin \n antes de fork | Buffer se duplica con el fork | Usar fflush(stdout) antes del fork |
| Olvidar exit() en el hijo | El hijo sigue ejecutando codigo del padre | Siempre exit() al final del bloque del hijo |
| Fork en bucle sin exit en hijo | Se crean procesos exponencialmente | El hijo debe hacer exit() o exec() |
| No hacer wait() | Procesos zombie | Siempre wait o signal(SIGCHLD, SIG_IGN) |
| Codigo despues de exec | Solo se ejecuta si exec falla | Pon perror y exit para el caso de fallo |

---

## 3. Errores de Pipes

| Error | Por que esta mal | Correccion |
|-------|-----------------|------------|
| No cerrar extremos no usados | El pipe no sabe cuando terminar | Cerrar fd[0] en escritor, fd[1] en lector |
| Write grande sin lector simultaneo | Deadlock: write bloquea, read nunca llega | Usar fork para tener lector y escritor separados |
| Olvidar que SIGPIPE mata | Si no hay lector, el escritor muere | Manejar SIGPIPE o comprobar retorno |
| Pipe despues de fork | Los hijos no heredan el pipe | Crear pipe ANTES del fork |

---

## 4. Errores de Shell Script

| Error | Por que esta mal | Correccion |
|-------|-----------------|------------|
| Variables sin comillas | Se rompe con espacios en nombres | Siempre "$variable" |
| getenv("$PATH") | El $ no va en getenv | getenv("PATH") |
| Esperar que variables se hereden | Solo se heredan las exportadas | Usar export |
| test con = para numeros | = compara cadenas | Usar -eq, -lt, -gt para numeros |
| Olvidar fi, esac, done | Error de sintaxis | Cada if tiene fi, case tiene esac, do tiene done |

---

## 5. Errores de Concurrencia

| Error | Por que esta mal | Correccion |
|-------|-----------------|------------|
| Comprobacion fuera del lock | Condicion de carrera | Meter la comprobacion DENTRO del lock |
| Pensar que x++ es atomico | Son 3 instrucciones: load, add, store | Proteger con mutex |
| Spinlock con alta contencion | Desperdicia CPU | Usar mutex (duerme en vez de girar) |
| Confundir mlock con mutex | mlock es para swap, mutex para sincronizacion | Son cosas completamente distintas |
| Confundir flock con spinlock | flock es para ficheros | flock = lock de ficheros, spinlock = lock de memoria |

---

## 6. Errores de Memoria Virtual

| Error | Realidad |
|-------|---------|
| "Se asignan todos los marcos al hacer malloc" | Con paginacion bajo demanda, solo al acceder |
| "TLB cachea datos" | TLB cachea traducciones de direcciones |
| "Copy-on-write copia toda la memoria" | Solo copia la pagina que se modifica |
| "SIGKILL se puede capturar" | SIGKILL y SIGSTOP no se pueden capturar |

---

## 7. Errores de ELF y Enlazado

| Error | Realidad |
|-------|---------|
| ".data tiene las instrucciones" | .text tiene instrucciones, .data tiene datos |
| "ELF especifica el planificador" | El planificador lo decide el kernel |
| "ldd muestra bibliotecas estaticas" | ldd muestra DINAMICAS |
| "Con lazy binding se resuelve al inicio" | Se resuelve en la primera llamada |
| "Con RELRO se resuelve en la primera llamada" | Con RELRO se resuelve al inicio |

---

## Regla de Oro

Si ves un if FUERA de un lock que comprueba un recurso compartido, y luego el lock protege solo la modificacion: **ES UNA CONDICION DE CARRERA**. La comprobacion y la modificacion deben estar ambas dentro del lock.

Si te preguntan por sizeof de algo que parece un array pero es un parametro o un puntero: **la respuesta es 8** (en 64 bits), no el tamaño del bloque.

Si hay un fork y antes un printf sin newline: **el buffer se duplica** y el texto puede imprimirse mas veces de las esperadas.

---

# RESUMACO DE TRAMPAS DE EXAMEN (lo que cae SI O SI)

Destilado del banco real de examenes (Popurri, `clase/apuntes`). Cada punto es una trampa
que ha aparecido literalmente en un TEST1. Leelo entero el dia antes; si dominas esto,
apruebas la parte de test.

## A. Punteros, arrays y `sizeof` (la trampa numero 1)

- **`sizeof(puntero)` SIEMPRE da 8** (64 bits) o 4 (32 bits), nunca el tamaño del bloque.
  Da igual que el puntero venga de `malloc(100)` o sea un parametro de funcion.
  - `int *p = malloc(100); sizeof(p)` -> 8.
  - `void f(int a[]) { sizeof(a); }` -> 8 (el array se DEGRADA a puntero al pasarlo).
- **`sizeof(array_local)` SI da el tamaño total**: `int a[5]; sizeof(a)` -> 20 (= 5*4).
  - Trampa clasica: `for (i = 0; i < sizeof(a); i++)` itera 20 veces, no 5 -> lee basura.
    Lo correcto es `sizeof(a) / sizeof(a[0])`.
- **`memset(p, 0, sizeof(p))`** solo pone a cero 8 bytes (el puntero), no el bloque.
  Si luego compruebas que esta todo a cero, fallara: "array mal inicializado".
- **Aritmetica de punteros**: `p = arr + 2` apunta a `arr[2]`. `p = &p[1]` avanza uno mas.
  Truco: traduce todo a indices de `arr` y suma. `(arr+2)`, luego `&(.[1])` = `arr+3`,
  luego `[2]` = `arr[5]`.
- **String que se acorta con `\0`**: poner un `'\0'` (o `0`) en mitad de una cadena hace que
  `strlen` cuente solo hasta ahi. `"hola"` con `p[2]=0` -> `strlen` = 2.
- **`char p[5] = "hola"`** es modificable (esta en la pila). `char *p = "hola"` apunta a un
  literal de SOLO LECTURA: escribir en el es comportamiento indefinido.

## B. Memoria dinamica

- **Devolver `&variable_local`** (o un `char buf[]` local) = puntero colgante. Posible
  segfault. Para devolver memoria de una funcion, usa `malloc` DENTRO.
- **`p = malloc(...); p = "literal";`** = fuga (se pierde el malloc) + `free(p)` sobre un
  literal es comportamiento indefinido. Para copiar texto usa `strcpy(p, "literal")`.
- **Fuga por reasignacion**: `s = new_obj(); s = malloc(...)` pierde lo que devolvio
  `new_obj`. Cada `malloc` necesita su `free`.
- **Reasignar dentro de un bucle de recorrido**: `p = malloc(...); for (p = list; ...)`
  -> el malloc es inutil y se fuga. (Pregunta TEST1 2015 clasica.)
- **Use-after-free** y **doble free** son comportamiento indefinido (corrompen el heap).
  Tras `free(p)` pon `p = NULL`.
- **`malloc` sin comprobar NULL** = crash si no hay memoria. Comprueba siempre.

## C. Procesos: fork / exec / wait

- **N forks seguidos -> 2^N procesos.** `fork(); fork(); fork();` = 8 procesos.
- **`fork()` devuelve: 0 al hijo, PID del hijo al padre, -1 en error.** Es lo que permite
  distinguir quien es quien (NO devuelve "su propio pid", NO es igual en ambos).
- **`printf` sin `\n` ANTES de fork**: el texto queda en el buffer y el fork lo COPIA, asi
  que se imprime de mas. `printf("A"); fork();` con buffer -> "A" sale 2 veces al final.
  - Pero si la `A` esta antes del PRIMER fork y la cuentan "veces ejecutado el printf", la
    sentencia se ejecuta 1 vez (la duplicacion es del buffer, no de la sentencia). Lee bien
    si preguntan "cuantas veces se ejecuta el printf" vs "cuantas A aparecen".
- **`exec` con exito NO retorna**: reemplaza el proceso. El codigo despues de un exec solo
  se ejecuta si exec FALLA. Por eso `execv(...); printf("ok")` -> "ok" NUNCA se imprime.
- **`exec` sin `fork` antes** mata tu programa (lo reemplaza). Para lanzar un comando y
  seguir vivo: `fork` y `exec` en el hijo.
- **`exec` en un bucle**: el bucle no se repite (exec no vuelve). Si quieres relanzar,
  necesitas `fork` en cada vuelta.
- **`wait` garantiza el orden**: el padre que hace `wait` imprime DESPUES de que el hijo
  termine. Sin `wait`, el orden no esta garantizado.
- **getppid de hermanos es igual**: tras `fork(); fork();`, los procesos que comparten padre
  dan el mismo `getppid` -> "dos iguales y dos distintos".
- **Hijo sin `exit()`** en un bucle de forks sigue creando procesos (explosion). El hijo
  SIEMPRE debe terminar con `exit()` o `exec()`.

## D. Llamadas al sistema y ficheros

- **`read` devuelve: >0 bytes leidos, 0 = EOF, -1 = error.** Puede devolver MENOS de lo
  pedido sin ser error (short read). El bucle correcto es `while ((n=read(...)) > 0)`.
- **`write` puede escribir MENOS de lo pedido** (short write) y no es error; solo -1 lo es.
  Comprobar solo `if (nw < 0)` no detecta el short write.
- **`write(1, "hola", 4)`** escribe 4 caracteres en stdout (descriptor 1). El 4 es correcto
  (NO se incluye el `\0`). 0=stdin, 1=stdout, 2=stderr.
- **`fopen`/`fprintf` usan BUFFER en espacio de usuario**. Si el programa no termina ni hace
  `fflush`/`fclose` (p.ej. bucle infinito), lo escrito puede no llegar nunca al disco.
- **`fread`/`fwrite` hacen MENOS llamadas al sistema** que `read`/`write` directos, porque
  bufferizan. Mas eficiente para muchas lecturas pequeñas.
- **`dup2(fd, 0)`** redirige stdin; `dup2(fd, 1)` redirige stdout. Patron de redireccion:
  `open` el fichero, `dup2`, `close(fd)`, `exec`. (`open + dup2(fd,0) + exec wc -l` cuenta
  las lineas del fichero por stdout.)
- **`readdir` lista TODAS las entradas** del directorio (ficheros Y directorios, incluidos
  `.` y `..`), no solo los regulares.
- **i-nodo vs nombre**: una entrada de directorio asocia un NOMBRE con un i-nodo. Puede haber
  VARIOS nombres para el mismo i-nodo (enlaces duros). El i-nodo guarda los METADATOS, no el
  nombre.
- **`unlink` / `rm` decrementa `st_nlink`**; el fichero solo se borra cuando llega a 0. Tras
  `ln a b` (nlink=2) y `rm a`, el i-nodo sigue vivo con nlink=1 via `b`.
- **`lstat` vs `stat`**: `lstat` NO sigue el enlace simbolico (te dice que es un enlace);
  `stat` sigue el enlace. Para un `ls` que distinga enlaces se usa `lstat` + `S_IFMT`.

## E. Pipes

- **Buffer de pipe limitado (~64 KB)**. Un `write` enorme en un solo proceso (sin lector que
  vacie) LLENA el buffer y se BLOQUEA para siempre (deadlock). El `read` posterior nunca se
  ejecuta.
- **`write` en pipe sin lectores** -> SIGPIPE (por defecto MATA el proceso).
- **`read` de pipe vacio sin escritores** -> devuelve 0 (EOF). No es error, no se bloquea.
- **Crear el pipe ANTES del fork** para que ambos lo hereden.
- **Cerrar los extremos que no se usan**: si un proceso (incluido el PADRE que solo conecta
  dos hijos) deja abierto el extremo de escritura, el lector nunca recibe EOF y se cuelga.

## F. Shell y variables de entorno

- **Variables de shell NO se heredan** por procesos hijos a menos que se hagan `export`.
  `x=5; bash; echo $x` -> linea vacia en el sub-shell.
- **`getenv("PATH")`**, NO `getenv("$PATH")`. El `$` es del shell, no de C.
- **`PATH`** = lista de directorios donde se buscan EJECUTABLES, separados por `:`.
- **`argc--; argv++;`** salta el nombre del programa; el bucle imprime los argumentos
  reales (NO es exactamente `echo`, pinta uno por linea).
- **Comparar numeros**: `-eq -lt -gt -le -ge`. Comparar cadenas: `=` y `!=`. Mezclarlos es
  error tipico.
- **Comillas SIEMPRE** en `"$var"` y `"$@"`: sin ellas se rompe con espacios.

## G. Memoria virtual y paginacion

- **Paginacion bajo demanda + overcommit**: declarar un array global enorme NO reserva
  marcos; solo se asigna un marco por cada PAGINA realmente accedida. `char a[8MB]; a[0]='x'`
  -> 1 marco.
- **TLB** = cache de traducciones de direccion VIRTUAL a FISICA (no cachea datos ni
  instrucciones).
- **Copy-on-write** en fork: padre e hijo COMPARTEN paginas hasta que uno ESCRIBE; solo
  entonces se copia esa pagina.
- **Memoria virtual** sirve sobre todo para PROTEGER el espacio de cada proceso (cada uno ve
  su propio espacio de direcciones).

## H. Planificacion

- **Round-Robin con cuanto MUY GRANDE -> degenera en FCFS** (efecto convoy).
- **Round-Robin con cuanto MUY PEQUEÑO -> muchos cambios de contexto**; es la politica mas
  perjudicada si encarece el coste de cambiar de contexto.
- **`renice`**: cambia la prioridad (niceness), rango -20 (mas prioridad) a 19 (menos).

## I. Concurrencia

- **REGLA DE ORO**: si el `if` que comprueba un recurso compartido esta FUERA del lock y solo
  la modificacion esta dentro -> CONDICION DE CARRERA. Comprobacion y modificacion deben ir
  ambas dentro del lock. (Aplica a `if (x>0){lock; x--; unlock;}`, a `existe()` + `borrar()`,
  etc.)
- **`x++` NO es atomico** (load, add, store): sin proteccion se pierden incrementos.
- **Spinlocks**: NO usar con CONTIENDA ALTA (desperdician CPU girando). Buenos solo si la
  seccion critica es minima y la contienda baja.
- **No confundir**: `mlock` evita el SWAP (no sincroniza). `flock` bloquea FICHEROS
  (lectores/escritores). `mutex`/`spinlock` sincronizan memoria. Son cosas distintas.
- **Mutex = binario** (duerme); **semaforo = contador**.

## J. ELF y enlazado

- **`.text`** = instrucciones (codigo). **`.data`** = datos inicializados. **`.bss`** = no
  inicializados. La trampa: ".data tiene las instrucciones" es FALSO.
- **El ELF NO indica el planificador** (eso lo decide el kernel). Si guarda: arquitectura,
  punto de entrada, datos inicializados, info de enlazado.
- **Lazy binding** -> la direccion de una funcion se resuelve en la PRIMERA llamada (via PLT).
- **RELRO** -> se resuelven todos los simbolos AL INICIO de la ejecucion (y la GOT se hace
  solo-lectura). Es lo contrario del lazy binding.
- **`ldd`** muestra las bibliotecas DINAMICAS que necesita un binario ELF.

## K. Sistemas de ficheros

- **i-nodos (Unix)**: asignacion INDEXADA con esquema COMBINADO (punteros directos +
  indirectos). No contigua, no FAT.
- **FAT**: los nombres estan en las ENTRADAS DE DIRECTORIO; la tabla FAT solo encadena
  clusters.

## L. Señales

- **SIGKILL (9) y SIGSTOP NO se pueden capturar ni ignorar.** SIGKILL no es Ctrl+C.
- **Ctrl+C = SIGINT. Ctrl+Z = SIGTSTP.** SIGTERM (15) si se puede capturar.
- **Mascara de señales** = señales BLOQUEADAS (quedan pendientes), no "ignoradas".

## Flashcards de valores de retorno (memoriza esto al dedillo)

| Funcion | Exito | Caso especial | Error |
|---------|-------|---------------|-------|
| `fork()` | PID hijo (padre) / 0 (hijo) | — | -1 |
| `read()` | nº bytes (>0) | 0 = EOF | -1 |
| `write()` | nº bytes (puede ser < pedido) | — | -1 |
| `open()` | descriptor (>=0) | — | -1 |
| `wait()`/`waitpid()` | PID del hijo | — | -1 |
| `exec*()` | **no retorna** | — | -1 |
| `malloc()`/`realloc()` | puntero | — | NULL |
| `pipe()` | 0 | — | -1 |
| `strtol()` | numero | pon `errno=0` y mira `*endptr` | ERANGE |
