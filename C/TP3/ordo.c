#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct liste liste;

struct liste{
	
    pid_t pid;
	liste *next;
	liste *prev;
};

liste * x = NULL;
int number=0;

void suivant(){
	
	x=x->next;
}

void ajouter(pid_t toadd){
	
	liste * y;
	y=malloc(sizeof(liste));
	y->pid=toadd;
	if(!x){
		
		y->next=y;
		y->prev=y;
		x=y;
		number++;
		
	} else {
		
		y->next=x;
		x->prev->next=y;
		y->prev=x->prev;
		x->prev=y;
		number++;
	}
}

void supprimer(){
	
	if(!x){
		
		printf("Liste vide\n");
		
	} else if(x->prev==x){
		
		free(x);
		number--;
		
	} else {
		
		x->prev->next=x->next;
		x->next->prev=x->prev;
		suivant();
		number--;
		
	}
}

void afficher(){
	
	if(x){
		
		printf("%d\n",x->pid);
		
	} else {
		
		printf("Liste vide\n");
		
	}
}

void ajout(){
	
	int content;
	FILE* fichier=fopen("pid.dat","r");
	if(fichier!=NULL){
		
		fscanf(fichier, "%d", &content);
		fclose(fichier);
	}
	printf("%d\n",content);
	kill(content,SIGSTOP);
	ajouter(content);
}

void init(){
	
	FILE* fichier;
	fichier = fopen("ordo.dat", "w+");
	if (fichier != NULL){
		
		fprintf(fichier,"%d",getpid());
		fclose(fichier);
		
	}
}

void boucle(){
	
	while(1){
		
		if((number==0)||(number==1)){
			
			afficher();
			sleep(2);
			
		} else {
			
			afficher();
			kill(x->pid,SIGCONT);
			sleep(2);
			kill(x->pid,SIGSTOP);
			suivant();
			
		}
	}
}

int main(){
	
	init();
	signal(SIGUSR1,ajout);
	signal(SIGUSR2,supprimer);
	boucle();
	return 0;
}

