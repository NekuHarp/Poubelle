#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	
	if(argc<=1) {
		
		printf("Saisissez au moins un argument.\n");
		return 1;
	}
	
	int i = 1;
	int result = 0;
	
	while(i != argc) {
		
		result+= atoi(argv[i]);
		i++;
	}
	printf("%d\n",result); 
	
	return 0;
}