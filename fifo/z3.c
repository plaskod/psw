#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>

#define MAX 1024

///int mkfifo(const char *path, mode_t mode)
//int open(const char *path, int oflag)- otwiera kolejke path w trybie oflag
//O_NONBLOCK lub O_NDELAY nie blokuje
//int unlink(const char *path) usuwa FIFO


int main(int argc, char* argv[]){
	int pserver, pclient;
	char buf[MAX];
	int bajty;
	
	switch(fork()){
		case -1:
			perror("Blad tworzenia procesu");
			exit(1);
		case 0:
			mkfifo("fifoserver",0666);
			pserver=open("fifoserver",O_RDONLY);
			if(pserver==-1){
				perror("Blad otwarcia kolejki fifo serwera");
				exit(1);
			}
			sleep(1);
			bajty=read(pserver,buf,MAX);
			if(fork()==0){
				close(1);
				pclient=open(buf,O_WRONLY);
				if(pclient == -1){
					perror("Blad przy otwarciu");
					exit(1);
				}
				execlp("ls","ls",NULL);
				close(pclient);
				perror("ls nie wykonany");
				exit(1);
			}

		default:{ //proces macierzysty
			
			if(fork()==0){//klient
			
				mkfifo("fifoclient", 0666);
				pserver=open("fifoserver", O_WRONLY);
				if(pserver==-1){
					perror("Blad przy otwarciu kolejki fifo serwera");
					exit(1);
				}
				write(pserver,"fifoclient",11);
				close(pserver);
				pclient=open("fifoclient",O_RDONLY);
				if(pclient==-1){
					perror("blad przy otwarciu kolejki fifo serwera");
					exit(1);
				}
				bajty=read(pclient,buf,MAX);
				write(1,buf,bajty);
			}
			else{
				wait(NULL);
				exit(1);
			}
	
		}	

	}	

}
