#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void AfficherPrompt(){
	printf("~$ ");
}

char ** analyser(char* commande){
	
	char** arg;
	arg=(char**)malloc(100*sizeof(char*));
	arg[0]=strtok(commande," ");
	int i = 1;
	while(arg[i++]=strtok(NULL," "));
	return arg;
}

void executer(char** arg){
	
	int status,pidf;
	int pid = fork();
	
	if(pid == 0){
		
		execvp(arg[0],arg);
		printf("Erreur (commande invalide) : %s\n", arg[0]);
		exit(1);
		
	} else if (pid > 0){

		pidf=wait(&status);

	}
	
}

int main(){
	
	char commande[100];
	char ** arg;
	
	AfficherPrompt();
	
	while(gets(commande)){
		arg = analyser(commande);
		executer(arg);
		AfficherPrompt();
	}
	
}