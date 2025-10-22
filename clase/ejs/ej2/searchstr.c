#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>


int
main(int argc, char **argv){
    int args = argc -1;

    if ((args % 2) != 0 || args == 0){
        fprintf(stderr, "error: bad number of arguments\n");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if (pid < 0){
        perror("error: fork ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0){
        printf("Instrucción: fgrep %s %s\n", argv[2], argv[1]);
        //fgrep <cadena> <archivo>
        execl("/usr/bin/fgrep","fgrep", argv[2], argv[1], (char *)NULL);
        perror("error: execl");
        exit(EXIT_FAILURE);
    }else{
        wait(NULL);
    }


    /*//prueba imprimir args en parejas
    for (int i = 1;i< args; i++){
        printf("%s - %s\n",argv[i], argv[i +1]);
        i++;
    }*/

    return 0;
}