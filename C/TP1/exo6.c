#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

pid_t pid;

void murder(int sig) {
	
	kill(pid, SIGTERM);
	run = 0;
}

int main(int argc, char * argv[]){
	
	if(argc != 3) {
		
		printf("Saisissez deux arguments.\n");
		return 1;
	}
	
	int time = atoi(argv[2]);
	pid = atoi(argv[1]);
	signal(SIGALRM, murder);  
	alarm((time<=0)?1:time);
	
	while(1) {
		
		sleep(1);
	}
	
	return 0;
} 