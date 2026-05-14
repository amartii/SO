#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		printf("Soy el hijo, PID=%d\n", getpid());
		exit(EXIT_SUCCESS);
	}
	printf("Soy el padre, PID=%d, hijo=%d\n", getpid(), pid);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
