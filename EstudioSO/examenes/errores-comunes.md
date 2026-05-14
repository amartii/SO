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
