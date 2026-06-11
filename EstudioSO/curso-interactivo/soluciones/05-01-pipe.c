#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	int fd[2];
	pid_t pid;
	char buf[256];
	ssize_t n;
	char *msg = "Mensaje del padre";

	if (pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		/* Hijo: lector */
		close(fd[1]);
		n = read(fd[0], buf, sizeof(buf) - 1);
		if (n > 0) {
			buf[n] = '\0';
			printf("Hijo recibio: %s\n", buf);
		}
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	/* Padre: escritor */
	close(fd[0]);
	write(fd[1], msg, strlen(msg));
	close(fd[1]);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
