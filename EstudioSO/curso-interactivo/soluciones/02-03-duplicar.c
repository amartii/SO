#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *
duplicar(const char *s)
{
	char *copia;

	copia = malloc(strlen(s) + 1);
	if (copia == NULL) {
		fprintf(stderr, "error: no memory\n");
		exit(EXIT_FAILURE);
	}
	strcpy(copia, s);
	return copia;
}

int
main(int argc, char *argv[])
{
	char *original = "Hola Mundo";
	char *copia;

	copia = duplicar(original);
	printf("Original: %s\n", original);
	printf("Copia: %s\n", copia);
	free(copia);
	exit(EXIT_SUCCESS);
}
