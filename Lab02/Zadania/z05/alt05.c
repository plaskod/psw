#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	printf("--------Poczatek listy----------\n");
	if(fork()==0){
		execlp("ps","ps", "--no-headers", NULL);
		exit(1);
	}
	
	wait(NULL);
	printf("---------Koniec listy-----------\n");
	
	
}
