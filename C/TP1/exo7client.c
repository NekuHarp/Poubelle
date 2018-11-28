#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void handler(int sign) {
	
	printf("ceci est un bon exercice pour comprendre le mécanisme des signaux\n");
}

int main(void) {

	if (signal(SIGUSR1, handler) == SIG_ERR) {
		
		printf("Erreur.\n");
	}

	printf("%d\n", getpid());

	while(1) {
		
		sleep(1);
	}

	return 0;
}