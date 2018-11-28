#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid;

int main(int argc, char ** argv) {

	if(argc<3) {

		printf("Erreur (2 arguments attendus) : %d\n", argc-1);
		return 1;

	}

	int t = atoi(argv[1]);
	pid = fork();

	if (pid > 0) {

		sleep(t);
		kill(pid,SIGKILL);

	} else if (pid == 0) {

		execvp(argv[2], &argv[2]);
		printf("Erreur (commande invalide) : %s\n", argv[2]);

	} else {
		
		perror("Erreur (fork)\n");
		
	}

	return 0;
}