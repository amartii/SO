#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

static void
on_alarm(int signo)
{
    const char msg[] = "Timeout!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(EXIT_SUCCESS);
}

int
main(void)
{
    int fd[2];
    char buf[1];

    if (pipe(fd) < 0) {
        fprintf(stderr, "error: no se puede crear pipe\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGALRM, on_alarm) == SIG_ERR) {
        fprintf(stderr, "error: no se puede instalar alarma\n");
        close(fd[0]);
        close(fd[1]);
        exit(EXIT_FAILURE);
    }

    alarm(3);
    if (read(fd[0], buf, sizeof(buf)) < 0) {
        if (errno != EINTR) {
            fprintf(stderr, "error: read fallo\n");
            close(fd[0]);
            close(fd[1]);
            exit(EXIT_FAILURE);
        }
    }

    close(fd[0]);
    close(fd[1]);
    exit(EXIT_SUCCESS);
}
