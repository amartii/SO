#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int contador = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *
incrementar(void *arg)
{
	int i;

	for (i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
		contador++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int
main(int argc, char *argv[])
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, incrementar, NULL);
	pthread_create(&t2, NULL, incrementar, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Contador final: %d (esperado 2000000)\n", contador);
	exit(EXIT_SUCCESS);
}
/* Compilar con: gcc -g -Wall -o mutex mutex.c -lpthread */
