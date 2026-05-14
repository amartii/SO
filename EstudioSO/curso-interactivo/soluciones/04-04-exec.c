#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		execlp("ls", "ls", "-la", "/tmp", (char *)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	if (wait(&status) == -1) {
		perror("wait");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status)) {
		printf("Hijo termino con codigo: %d\n", WEXITSTATUS(status));
	}
	exit(EXIT_SUCCESS);
}
