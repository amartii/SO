/***Enunciado:** Escribe un programa que redirija stdout a 
 * un fichero usando dup2, y luego imprima un mensaje con printf. 
 * El mensaje debe aparecer en el fichero, no en pantalla.

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
- printf ahora escribe al fichero*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void usage(void){
    fprintf(stderr, "error: usage ./ej3_3 <fich.txt>\n");
    exit(EXIT_FAILURE);
}

int
main (int argc, char ** argv){
    int numargs = argc - 1;
    int fdin;
    struct stat sb;

    if (numargs != 1){
        usage();
    }

    if (stat(argv[1], &sb) < 0){
        fprintf(stderr, "error: %s not found\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    fdin = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fdin <0){
        perror("error open");
        close(fdin);
        exit(EXIT_FAILURE);
    }

    if (dup2(fdin, STDOUT_FILENO) < 0){
        perror("error redirection");
        close(fdin);
        exit(EXIT_FAILURE);
    }
    close(fdin);

    printf("Este texto fue redirigido a un fichero\n");
    exit(EXIT_SUCCESS);


}