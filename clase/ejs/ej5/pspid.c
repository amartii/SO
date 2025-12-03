#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void
usage(void)
{
    fprintf(stderr, "usage: ./pspid [pid]\n");
    exit(EXIT_FAILURE);
}

void
error_bad_value(void)
{
    fprintf(stderr, "error: bad pid\n");
    usage();
}

long
pid_correcto(const char *s)
{
    char *endn;
    long n;

    errno = 0;
    n = strtol(s, &endn, 10);
    if (errno == ERANGE || endn == s || *endn != '\0' || n < 0) {
        error_bad_value();
    }

    return n;
}

void
primer_hijo(int fd[2])
{
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if (close(fd[0]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        if (close(fd[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
        execlp("ps", "ps", (char *)NULL);
        perror("execlp ps");
        exit(EXIT_FAILURE);
    }
}

pid_t
segundo_hijo(int fd[2], long pid_to_find)
{
    pid_t pid;
    FILE *in;
    char line[4096];
    long col_pid;
    int found = 0;
    int ret;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if (close(fd[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        in = fdopen(fd[0], "r");
        if (in == NULL) {
            perror("fdopen");
            exit(EXIT_FAILURE);
        }

        while (fgets(line, sizeof(line), in) != NULL) {
            char *p = line;
            while (*p == ' ' || *p == '\t') {
                p++;
            }
            ret = sscanf(p, "%ld", &col_pid);
            if (ret == 1 && col_pid == pid_to_find) {
                found = 1;
                break;
            }
        }


        if (fclose(in) == EOF) {
            perror("fclose");
            exit(EXIT_FAILURE);
        }

        if (found) {
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    return pid;
}

void
padre(long pid_to_find)
{
    int fd[2];
    int status;
    pid_t pid2;
    pid_t wpid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    primer_hijo(fd);
    pid2 = segundo_hijo(fd, pid_to_find);

    if (close(fd[0]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
    if (close(fd[1]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    if (waitpid(pid2, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    /* recoger también al primer hijo para no dejar zombie */
    do {
        wpid = wait(NULL);
    } while (wpid > 0 || (wpid == -1 && errno == EINTR));

    if (WIFEXITED(status)) {
        exit(WEXITSTATUS(status));  /* 0 si encontrado, 1 si no */
    }

    exit(EXIT_FAILURE);
}

int
main(int argc, char **argv)
{
    long n;

    if (argc != 2) {
        usage();
    }
    
    n = pid_correcto(argv[1]);
    padre(n);
    return EXIT_SUCCESS;
}
