# Mini apuntes de E/S en C

## 1. `open`, `read`, `write`, `close` (llamadas al sistema)

### Uso habitual
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int fd = open("archivo.txt", O_RDONLY);
if (fd < 0) {
    perror("open");
    exit(EXIT_FAILURE);
}

char buf[4096];
ssize_t n;
while ((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(STDOUT_FILENO, buf, n) != n) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
}
if (n < 0) {
    perror("read");
    close(fd);
    exit(EXIT_FAILURE);
}

if (close(fd) < 0) {
    perror("close");
    exit(EXIT_FAILURE);
}
```

### Qué debes saber
- `open` devuelve un descriptor de fichero (`int`) o `-1` en error.
- `read` devuelve:
  - >0 = bytes leídos
  - 0 = fin de fichero
  - -1 = error
- `write` devuelve el número de bytes escritos o `-1` en error.
- `close` cierra el descriptor y puede fallar.

### Crear / truncar un archivo de salida
```c
int fdout = open("destino.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fdout < 0) {
    perror("open destino");
    close(fdin);
    exit(EXIT_FAILURE);
}
```

### Copiar de un fichero a otro
```c
while ((n = read(fdin, buf, sizeof(buf))) > 0) {
    ssize_t written = 0;
    while (written < n) {
        ssize_t m = write(fdout, buf + written, n - written);
        if (m < 0) {
            perror("write");
            close(fdin);
            close(fdout);
            exit(EXIT_FAILURE);
        }
        written += m;
    }
}
```

---

## 2. `fopen`, `fread`, `fwrite`, `fclose` (I/O en stdio)

### Uso habitual
```c
#include <stdio.h>
#include <stdlib.h>

FILE *f = fopen("archivo.txt", "rb");
if (!f) {
    perror("fopen");
    exit(EXIT_FAILURE);
}

unsigned char buf[4096];
size_t n;
while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
    if (fwrite(buf, 1, n, stdout) != n) {
        perror("fwrite");
        fclose(f);
        exit(EXIT_FAILURE);
    }
}
if (ferror(f)) {
    perror("fread");
    fclose(f);
    exit(EXIT_FAILURE);
}

if (fclose(f) != 0) {
    perror("fclose");
    exit(EXIT_FAILURE);
}
```

### Modos comunes de `fopen`
- `"r"` : leer.
- `"w"` : escribir, crea o trunca.
- `"a"` : añadir al final.
- `"rb"`, `"wb"` : modo binario.

### Copiar con `FILE *`
```c
FILE *in = fopen("origen.bin", "rb");
if (!in) {
    perror("fopen origen");
    exit(EXIT_FAILURE);
}
FILE *out = fopen("destino.bin", "wb");
if (!out) {
    perror("fopen destino");
    fclose(in);
    exit(EXIT_FAILURE);
}

size_t r;
while ((r = fread(buf, 1, sizeof(buf), in)) > 0) {
    if (fwrite(buf, 1, r, out) != r) {
        perror("fwrite");
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }
}
if (ferror(in)) {
    perror("fread");
}

fclose(in);
fclose(out);
```

---

## 3. Diferencias clave

- `open/read/write/close` son llamadas al sistema y usan descriptores `int`.
- `fopen/fread/fwrite/fclose` usan la biblioteca estándar `stdio` y manejan un buffer interno.
- `fread` y `fwrite` trabajan con elementos y cantidades, no solo bytes.
- Usa `ssize_t` para `read`/`write`, y `size_t` para `fread`/`fwrite`.

## 4. Flujo habitual de errores

1. Abrir el fichero.
2. Comprobar si la apertura falló.
3. Leer en un bucle.
4. Escribir en un bucle.
5. Comprobar errores de E/S al final.
6. Cerrar el fichero.

## 5. `stat()` para metadatos de fichero

`stat()` es una llamada al sistema que obtiene información del fichero sin abrirlo para lectura/escritura.

### Uso básico
```c
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

struct stat sb;
if (stat("origen.txt", &sb) < 0) {
    perror("stat");
    exit(EXIT_FAILURE);
}

if (!S_ISREG(sb.st_mode)) {
    fprintf(stderr, "error: origen no es un fichero regular\n");
    exit(EXIT_FAILURE);
}

printf("existe y es regular\n");
printf("tamaño = %lld bytes\n", (long long) sb.st_size);
```

### Qué obtiene `stat()`
- `sb.st_mode`: tipo de fichero y permisos.
- `sb.st_size`: tamaño del fichero en bytes.
- `sb.st_uid`, `sb.st_gid`: propietario y grupo.
- `sb.st_mtime`: última fecha de modificación.
- `sb.st_nlink`: número de enlaces duros.

### Para qué sirve en un programa de copia
- comprobar si el fichero existe antes de abrirlo.
- saber si es un fichero regular y no un directorio.
- obtener su tamaño si quieres mostrarlo o usarlo como referencia.
- evitar errores antes de hacer `open`/`read`.

### Ejemplo con `open()` y `stat()` juntos
```c
struct stat sb;
if (stat(origen, &sb) < 0) {
    perror("stat origen");
    exit(EXIT_FAILURE);
}
if (!S_ISREG(sb.st_mode)) {
    fprintf(stderr, "error: origen no es fichero regular\n");
    exit(EXIT_FAILURE);
}
int fdin = open(origen, O_RDONLY);
if (fdin < 0) {
    perror("open origen");
    exit(EXIT_FAILURE);
}
```

## 6. Trucos útiles
- No confíes en `write` para escribir todo de una vez; puede escribir menos.
- En `fread`, cuando sale `0`, comprueba `feof()` y `ferror()`.
- Cuando uses `open` con `O_CREAT`, pasa el modo `0644`.
- Siempre cierra lo que abras, incluso en caso de error.
