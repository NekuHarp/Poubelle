#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int pidordo(){
	
	int content;
	FILE* fichier=fopen("ordo.dat","r");
	if(fichier!=NULL){
		
		fscanf(fichier, "%d", &content);
		fclose(fichier);
		printf("ORDO %d\n", content);
		return content;
		
	} else {
		
		return -1;
		
	}
}

void piddat(){
	
	FILE* fichier;
	fichier = fopen("pid.dat", "w+");
	if (fichier != NULL){
		
		fprintf(fichier,"%d",getpid());
		fclose(fichier);
		
	}
}


int main(int argc, char ** argv) {

	int status;
	pid_t pid = fork();

	if(argc<2) {

		return 0;

	}

	if (pid > 0) {
		
		wait(&status);
		int pido = pidordo();
		kill(pido,SIGUSR2);

	} else if (pid == 0) {
		
		piddat();
		int pido = pidordo();
		kill(pido,SIGUSR1);
		execvp(argv[1], &argv[1]);
		printf("Erreur (commande invalide) : %s\n", argv[1]);

	} else {
		
		perror("Erreur (fork)\n");

	}
	
	return 0;
}