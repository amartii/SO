<<<<<<< HEAD
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
=======
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

//comprobar con limits.h que no sea el numero ni max ni min y además *end= \0 

int 
main(int argc, char **argv){
    char *endn;
    char *endl;
    long n;
    long l;
    int nargs;

    //comprobar que se pasan los argumentos n y l y controlar el error (el programa sale con estado de fallo)
    if (argc < 3){
        fprintf(stderr, "Uso: %s N L ps\n", argv[0]);
        return EXIT_FAILURE;
    } else{
        n = strtol(argv[1],&endn,10); //strtol(string, apuntoalfinal,base);
        l = strtol(argv[2],&endl,10);

        nargs = argc -1;
        printf("Numero de args:%i\n",nargs);

        //comprobación de los argumentos
        for (int i=0; i<=argc -1;i++){
            printf("El argumento %i es:%s\n",i, argv[i]);
        }
        printf("Argumento l: %ld\n", l);
        printf("Argumento n: %ld\n", n);
        return 0;
    }
 
}

>>>>>>> a1b0b6ff4eb0fce0d275bc272e76be1f1dc03952
