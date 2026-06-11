/***Enunciado:** Escribe un programa que copie un fichero usando las llamadas 
 * al sistema open, read, write y close. Recibe dos argumentos: 
 * fichero origen y fichero destino. Usa un buffer de 4096 bytes.

**Ejemplo:**

```
$ ./mycopy origen.txt destino.txt
```

**Pistas:**

- Abre origen con O_RDONLY
- Crea destino con O_WRONLY | O_CREAT | O_TRUNC, modo 0644
- Lee en un bucle hasta que read devuelva 0
- Escribe exactamente los bytes leidos*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void usage(void){
    fprintf(stderr, "error: usage ./ej3_2 <origen.txt> <destino.txt>\n");
    exit(EXIT_SUCCESS);
}

int
main (int argc, char ** argv){
    int numargs = argc -1;
    int fdin, fdout;
    char buf[4096];
    ssize_t n;

    if (numargs != 2){
        usage();
    }

    fdin = open(argv[1], O_RDONLY);
    if (fdin <0){
        perror("Error: open origen");
        close(fdin);
        exit(EXIT_FAILURE);
    }

    fdout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 4096);
    if (stdout <0){
        perror("Error: open destino");
        close(fdout);
        exit(EXIT_FAILURE);
    }

    while ((n = read(fdin, buf, sizeof(buf))) > 0){
        if (write(fdout, buf, n) != n){
            perror("error: write");
            close(fdout);       
            exit(EXIT_FAILURE); 
        }
    }
    if (n <0){
        perror("error: read");
    }
    close(fdin);
    close(fdout);

    exit(EXIT_SUCCESS);

}