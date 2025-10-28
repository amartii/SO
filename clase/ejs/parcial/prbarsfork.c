#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int nBarras;
    int i;
    int longBarra;
    int retardo;
    int j;
    int k;
    pid_t pid;

    if (argc < 3 || (argc - 1) % 2 != 0) {
        printf("uso: %s long1 ret1 [long2 ret2 ...]\n", argv[0]);
        return 1;
    }

    nBarras = (argc - 1) / 2;
    printf("Numero de barras %i\n", nBarras);
    for (i = 0; i < nBarras; i++) {
        pid = fork();
        if (pid == 0) { // Proceso hijo
            printf("Barra %i\n", i +1);
            longBarra = atoi(argv[1 + i * 2]);
            retardo = atoi(argv[2 + i * 2]);
            printf("%i\n", longBarra);
            printf("%i\n", retardo);
            for (j = 0; j <= longBarra; j++) {
                printf("\r[");
                for (k = 0; k < longBarra; k++) {
                    if (k < j) {
                        printf("#");
                    } else {
                        printf(".");
                    }
                }
                printf("] %d%%", j * 100 / longBarra);
                fflush(stdout);
                usleep(retardo);
            }
            printf("\n");
            return 0;
        }else{
            wait(NULL);//espera a que el hijo termine antes de seguir
        }
    }
    return 0;
}