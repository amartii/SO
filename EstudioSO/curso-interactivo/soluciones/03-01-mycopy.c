#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	int fdin, fdout;
	char buf[4096];
	ssize_t n;

	if (argc != 3) {
		fprintf(stderr, "usage: %s origen destino\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	fdin = open(argv[1], O_RDONLY);
	if (fdin < 0) {
		perror("open origen");
		exit(EXIT_FAILURE);
	}
	fdout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout < 0) {
		perror("open destino");
		close(fdin);
		exit(EXIT_FAILURE);
	}
	while ((n = read(fdin, buf, sizeof(buf))) > 0) {
		if (write(fdout, buf, n) != n) {
			perror("write");
			close(fdin);
			close(fdout);
			exit(EXIT_FAILURE);
		}
	}
	if (n < 0) {
		perror("read");
	}
	close(fdin);
	close(fdout);
	exit(EXIT_SUCCESS);
}
