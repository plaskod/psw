#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	printf("Poczatek\n");
	if(fork()==0){
		execlp("ls","ls", NULL);
		exit(1);
	}
	
	wait(NULL);
	printf("Koniec\n");
	
	
}
