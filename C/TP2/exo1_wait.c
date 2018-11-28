#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(){

	pid_t pid;
	pid = fork();

	if(pid == 0) {

		printf("Enfant : %d ; Parent : %d\n", getpid(), getppid());

	} else if(pid>0) {

		printf("Parent : %d ; Enfant : %d\n", getpid(), pid);
		wait(NULL);

	} else {

		perror("Erreur (fork)\n");
		

	}

	return 0;
}