#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

pid_t pid;

int main(int argc, char ** argv) {
	
	if(argc<3) {

		printf("Erreur (2 arguments attendus) : %d\n", argc);
		return 1;

	}
	
	int t = atoi(argv[1]);
	
	while(1){
		
		sleep(t);
		pid = fork();

		if (pid == 0) {

			execvp(argv[2], &argv[2]);
			printf("Erreur (commande invalide) : %s\n", argv[2]);

		} else if (pid == -1) {
			
			perror("Erreur (fork)\n");
			
		}
	}

	return 0;
}