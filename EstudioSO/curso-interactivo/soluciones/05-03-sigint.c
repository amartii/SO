#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t count = 0;

void
handler(int sig)
{
	count++;
	if (count >= 3) {
		printf("Ctrl+C recibido, intento %d. Saliendo.\n", count);
		exit(EXIT_SUCCESS);
	}
	printf("Ctrl+C recibido, intento %d\n", count);
}

int
main(int argc, char *argv[])
{
	signal(SIGINT, handler);
	printf("Esperando señales... (Ctrl+C para probar)\n");
	while (1) {
		pause();
	}
	exit(EXIT_SUCCESS);
}
