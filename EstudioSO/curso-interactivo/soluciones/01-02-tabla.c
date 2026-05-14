#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int n, i;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <numero>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	n = atoi(argv[1]);
	for (i = 1; i <= 10; i++) {
		printf("%d x %d = %d\n", n, i, n * i);
	}
	exit(EXIT_SUCCESS);
}
