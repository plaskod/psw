#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	int x;
	x=atoi(argv[1]);
	for(int i=0; i<x; i++){
		sleep(rand()%9+1);

		if (fork()){
			sleep(rand()%4+1);
			printf("Proces skonczony %d\n", i);
			kill(0, SIGTERM);
		}
	}
}
