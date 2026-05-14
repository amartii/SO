#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	int n, i;
	pid_t pid;

	if (argc < 2) {
		fprintf(stderr, "usage: %s N\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	n = atoi(argv[1]);
	for (i = 0; i < n; i++) {
		pid = fork();
		if (pid < 0) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) {
			printf("Hijo %d, PID=%d\n", i, getpid());
			exit(EXIT_SUCCESS);
		}
	}
	for (i = 0; i < n; i++) {
		wait(NULL);
	}
	printf("Padre: todos los hijos terminaron\n");
	exit(EXIT_SUCCESS);
}
