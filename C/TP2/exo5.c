#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


void handler1(int sign) {
	
	printf("ceci est un bon exercice pour comprendre le mécanisme des signaux 1\n");
}

void handler2(int sign) {
	
	printf("ceci est un bon exercice pour comprendre le mécanisme des signaux 2\n");
}

int main(int argc, char ** argv) {
	
	pid_t pid2;
	pid_t pid1 = fork();
	
	if (pid1 > 0) {

		pid2 = fork();

	}
	
	while(1){
		
		if ((pid1 > 0) && (pid2 > 0)) {
		
			sleep(1);
			kill(pid1, SIGUSR1);
			
			sleep(1);
			kill(pid2, SIGUSR1);

		} else if (pid1 == 0) {

			if (signal(SIGUSR1, handler1) == SIG_ERR) {
		
				printf("Erreur.\n");
			}

		} else if (pid2 == 0) {
			
			if (signal(SIGUSR1, handler2) == SIG_ERR) {
		
				printf("Erreur.\n");
			}
					
		} else {
			
			perror("Erreur (fork)\n");
			
			
		}
	}
	
	return 0;
}