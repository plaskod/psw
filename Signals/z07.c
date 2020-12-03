#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	if (fork()){
		while(1){
			if (!fork()){
				execlp("ls","ls",NULL);
			}
		}
	}
	else{
		while(1){
			if(!fork()){
				execlp("ps","ps",NULL);
			}
		}
	}
}
