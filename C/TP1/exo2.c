#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	if(argc!=3) {
		
		printf("Saisissez deux arguments.\n");
		return 1;
	}
	
	int result;
	
	result = atoi(argv[1])+atoi(argv[2]);	
	printf("%d\n",result); 
	
	return 0;
}