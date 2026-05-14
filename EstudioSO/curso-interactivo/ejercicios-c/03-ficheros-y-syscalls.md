# Ejercicios Interactivos de C - Dia 3: Ficheros y Llamadas al Sistema

---

## Ejercicio 3.1: Copiar fichero con read/write

**Enunciado:** Escribe un programa que copie un fichero usando las llamadas al sistema open, read, write y close. Recibe dos argumentos: fichero origen y fichero destino. Usa un buffer de 4096 bytes.

**Ejemplo:**
```
$ ./mycopy origen.txt destino.txt
```

**Pistas:**
- Abre origen con O_RDONLY
- Crea destino con O_WRONLY | O_CREAT | O_TRUNC, modo 0644
- Lee en un bucle hasta que read devuelva 0
- Escribe exactamente los bytes leidos

**Solucion:** Ver `../soluciones/03-01-mycopy.c`

---

## Ejercicio 3.2: Contar bytes de un fichero

**Enunciado:** Escribe un programa que reciba un fichero como argumento y muestre su tamaño en bytes. Usa la llamada stat().

**Ejemplo:**
```
$ ./filesize /etc/passwd
Tamaño: 2847 bytes
```

**Pistas:**
- Incluye sys/stat.h
- Declara struct stat sb
- stat(argv[1], &sb) rellena la estructura
- sb.st_size tiene el tamaño

**Solucion:** Ver `../soluciones/03-02-filesize.c`

---

## Ejercicio 3.3: Redireccion con dup2

**Enunciado:** Escribe un programa que redirija stdout a un fichero usando dup2, y luego imprima un mensaje con printf. El mensaje debe aparecer en el fichero, no en pantalla.

**Ejemplo:**
```
$ ./redirigir salida.txt
$ cat salida.txt
Este texto fue redirigido a un fichero
```

**Pistas:**
- Abre el fichero con open
- Usa dup2(fd, STDOUT_FILENO) para redirigir stdout
- Cierra el fd original
- printf ahora escribe al fichero

**Solucion:** Ver `../soluciones/03-03-redirigir.c`

---

## Ejercicio 3.4: Listar directorio con opendir/readdir

**Enunciado:** Escribe un programa que reciba un directorio como argumento y liste todas sus entradas, mostrando si cada una es un fichero regular o un directorio.

**Ejemplo:**
```
$ ./myls /tmp
[DIR]  .
[DIR]  ..
[FILE] test.txt
[DIR]  subdir
```

**Pistas:**
- Usa opendir y readdir (incluye dirent.h)
- Para saber el tipo, usa stat() sobre cada entrada
- S_ISREG(sb.st_mode) para fichero regular
- S_ISDIR(sb.st_mode) para directorio
- Construye la ruta completa: directorio + "/" + nombre

**Solucion:** Ver `../soluciones/03-04-myls.c`

---

## Ejercicio 3.5: Pregunta tipo examen - dup2 y exec

**Sin compilar**, explica que hace este codigo:

```c
int x;
x = open("/tmp/afile", O_RDONLY);
if (x < 0)
    err(1, "error");
dup2(x, 0);
close(x);
execl("/bin/wc", "wc", "-l", NULL);
exit(0);
```

**Respuesta:**
1. Abre /tmp/afile en modo lectura
2. dup2(x, 0) redirige stdin al fichero
3. Cierra el descriptor original
4. execl ejecuta wc -l, que lee de stdin (ahora el fichero)
5. Resultado: escribe por stdout el numero de lineas del fichero
6. El exit(0) solo se ejecuta si execl falla

---

## Ejercicio 3.6: Pregunta tipo examen - buffering

**Sin compilar**, que contiene /tmp/x despues de ejecutar esto?

```c
FILE *f = fopen("/tmp/x", "w");
fprintf(f, "hi\n");
for(;;) { }
```

**Respuesta:** Es muy posible que /tmp/x este vacio. Porque fprintf usa buffering, los datos estan en el buffer de usuario, y el bucle infinito impide que se haga flush o fclose. Los datos nunca llegan a disco.
