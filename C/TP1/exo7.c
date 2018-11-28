#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	
	if(argc!=3) {
		
		printf("Saisissez deux arguments.\n");
		return 1;
	}
	
	int pidx = atoi(argv[1]);
	int pidy = atoi(argv[2]);
	
	while(1){
		
		sleep(1);
		kill(pidx, SIGUSR1);
		
		sleep(1);
		kill(pidy, SIGUSR1);
	}
	
	return 0;
}