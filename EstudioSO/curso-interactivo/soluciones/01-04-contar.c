#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int
main(int argc, char *argv[])
{
	int may = 0, min = 0;
	char *p;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <cadena>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	for (p = argv[1]; *p != '\0'; p++) {
		if (isupper(*p))
			may++;
		else if (islower(*p))
			min++;
	}
	printf("Mayusculas: %d\nMinusculas: %d\n", may, min);
	exit(EXIT_SUCCESS);
}
