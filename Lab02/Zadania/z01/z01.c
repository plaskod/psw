#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>


#define MAX 1024


int main(int argc, char* argv[]){


	if(fork()==0){
		printf("PID=%d, PPID=%d\n", getpid(), getppid());
		if(fork()==0){
			printf("PID=%d, PPID=%d\n", getpid(), getppid());
		}
	}
	else if(fork()==0){

		printf("PID=%d, PPID=%d\n", getpid(), getppid());
		if(fork()==0){
			printf("PID=%d, PPID=%d\n", getpid(), getppid());
		}
	}


	return 0;
}

