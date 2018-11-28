#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv) {

	int status;
	pid_t pid = fork();

	if(argc<2) {

		return 0;

	}

	if (pid > 0) {

		wait(&status);

	} else if (pid == 0) {

		execvp(argv[1], &argv[1]);
		printf("Erreur (commande invalide) : %s\n", argv[1]);

	} else {
		
		perror("Erreur (fork)\n");

		
	}

	return 0;
}