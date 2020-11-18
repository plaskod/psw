#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

	printf("Poczatek\n");
	int child=fork();
	if(child){
		execlp( "ls","a", NULL);
		exit(0);
	}
	else{
		waitpid(child,NULL,0);
		printf("Koniec\n");
	}
	return 0;
}
