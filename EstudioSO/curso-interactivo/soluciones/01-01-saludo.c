#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <nombre>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("Hola, %s!\n", argv[1]);
	exit(EXIT_SUCCESS);
}
