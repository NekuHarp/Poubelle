#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void handler(int sign) {
	
	if(sign == SIGINT) {
		
		char buffer[40];
		char * password = "exit";
		printf("\nMot de passe ?\n");
		scanf("%s",buffer);
		
		while (strcmp(buffer,password) != 0) {
			
			printf("Mot de passe incorrect.\n");
			printf("Mot de passe ?\n");
			scanf("%s",buffer);
		}

		printf("Mot de passe correct.\n");
		
		exit(0);
	}
}

int main(void) {
	
	if (signal(SIGINT, handler) == SIG_ERR) {
		
		printf("Erreur.\n");
	}

	printf("Ctrl + C ?\n");

	while(1) {
		
		sleep(1);
	}

	return 0;
}