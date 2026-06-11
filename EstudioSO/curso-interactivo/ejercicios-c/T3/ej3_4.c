/***Enunciado:** Escribe un programa que reciba un directorio como argumento 
 * y liste todas sus entradas, mostrando si cada una es un fichero regular o un directorio.

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
- Construye la ruta completa: directorio + "/" + nombre*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void usage(void){
    fprintf(stderr, "error: usasge ./ej3_4 <dir>\n");
    exit(EXIT_FAILURE);
}

int 
main (int argc, char** argv){
    int numargs = argc -1;
    DIR *dir;
    struct stat sb;
    struct dirent *entry; 
    char path[PATH_MAX];

    if(numargs != 1){
        usage();
    }

    dir = opendir(argv[1]);
    if (dir == NULL){
        fprintf(stderr, "error: no se puede abrir el dir %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while((entry = readdir(dir))!= NULL){
        snprintf(path, sizeof(path), "%s/%s", argv[1], entry -> d_name);
        if (stat(path, &sb) <0){
            printf("[UNKOWN] %s\n", entry -> d_name);
            continue;
        }
        if(S_ISDIR(sb.st_mode))
            printf("[DIR] %s\n", entry -> d_name);
        else if(S_ISREG(sb.st_mode))
            printf("[FILE] %s\n", entry->d_name);
        else
            printf("[OTHER] %s\n", entry->d_name);
    }
    closedir(dir);

    exit(EXIT_SUCCESS);

}
