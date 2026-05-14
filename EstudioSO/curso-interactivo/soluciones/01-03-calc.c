#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int a, b;

	if (argc != 4) {
		fprintf(stderr, "usage: %s num op num\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	a = atoi(argv[1]);
	b = atoi(argv[3]);
	switch (argv[2][0]) {
	case '+':
		printf("%d\n", a + b);
		break;
	case '-':
		printf("%d\n", a - b);
		break;
	case '*':
		printf("%d\n", a * b);
		break;
	case '/':
		if (b == 0) {
			fprintf(stderr, "error: division por cero\n");
			exit(EXIT_FAILURE);
		}
		printf("%d\n", a / b);
		break;
	default:
		fprintf(stderr, "error: operador desconocido '%c'\n", argv[2][0]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
