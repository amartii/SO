#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	int fd[2];
	pid_t pid;
	int i;

	if (pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	/* Hijo 1: ps aux -> escribe en pipe */
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1) {
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		execlp("ps", "ps", "aux", (char *)NULL);
		perror("execlp ps");
		exit(EXIT_FAILURE);
	}
	/* Hijo 2: wc -l <- lee del pipe */
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1) {
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		execlp("wc", "wc", "-l", (char *)NULL);
		perror("execlp wc");
		exit(EXIT_FAILURE);
	}
	/* Padre: cerrar pipe y esperar */
	close(fd[0]);
	close(fd[1]);
	for (i = 0; i < 2; i++) {
		wait(NULL);
	}
	exit(EXIT_SUCCESS);
}
