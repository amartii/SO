#include <stdlib.h>
#include <stdio.h>

void
swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int
main(int argc, char *argv[])
{
	int a = 10, b = 20;

	printf("Antes: a=%d, b=%d\n", a, b);
	swap(&a, &b);
	printf("Despues: a=%d, b=%d\n", a, b);
	exit(EXIT_SUCCESS);
}
