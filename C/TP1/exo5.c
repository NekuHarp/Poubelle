#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int compteur = 0;

void seconde(int sign) {

	printf("bonjour\n");
	compteur++;
	
	alarm(1);
	
	if(compteur>=5) {
		
		printf("au revoir\n");
		compteur = 0;
	}  
}

int main(){
	
	signal(SIGALRM, seconde);  
	alarm(1);
	
	while(1) {
		
		sleep(1);
	}
	
	return 0;
} 