#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 int 
main(int argc, char **argv)
{
	char *endn;
	char *endl;
	long n;
	long l;
	int words = argc - 3;
	int start;

	  if (argc < 3) {
		fprintf(stderr, "usage: %s N L [word ...]\n", argv[0]);
		return EXIT_FAILURE;
	}
	 errno = 0;
	n = strtol(argv[1], &endn, 10);
	if (errno == ERANGE || endn == argv[1] || *endn != '\0' || n < 0) {
		fprintf(stderr, "error: bad value \"%s\"\n", argv[1]);
		return EXIT_FAILURE;
	}
	 errno = 0;
	l = strtol(argv[2], &endl, 10);
	if (errno == ERANGE || endl == argv[2] || *endl != '\0' || l < 0) {
		fprintf(stderr, "error: bad value \"%s\"\n", argv[2]);
		return EXIT_FAILURE;
	}
	 if (n == 0) {
		return EXIT_SUCCESS;
	}
	 if (n > words) {
		n = words;
	}
	 start = argc - n;
	for (int i = start; i < argc; i++) {
		printf("%.*s\n", (int)l, argv[i]);
	}  return EXIT_SUCCESS;
}
