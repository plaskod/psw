#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>


int main(int argc, char* argv[]){
	int fd[2];
	pipe(fd);

	if(fork()){
		close(fd[1]);
		dup2(fd[0],0);
		execlp("tr","tr","a-z","A-Z",NULL);
		close(fd[0]);
	}
	else{

		close(fd[0]);
		dup2(fd[1],1);
		execlp("ls","ls","-l",NULL);
		close(fd[1]);
	}
}
