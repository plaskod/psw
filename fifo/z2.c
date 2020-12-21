#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>


///int mkfifo(const char *path, mode_t mode)
//int open(const char *path, int oflag)- otwiera kolejke path w trybie oflag
//O_NONBLOCK lub O_NDELAY nie blokuje
//int unlink(const char *path) usuwa FIFO


int main(int argc, char* argv[]){
	int pdesk;
	if(mkfifo("/tmp/fifo",0777)==-1){
		perror("Tworzenie kolejki FIFO");
		exit(1);
	}
	switch(fork()){

		case -1:
			perror("Tworzenie procesu");
			exit(1);
		case 0: //proces potomny
			close(1);
			pdesk=open("/tmp/fifo",O_WRONLY);
			if (pdesk==-1){
				perror("Otwarcie potoku do zapisu");
				exit(1);

			}
			execlp("ls","ls",NULL);
			perror("Uruchomienie ls");
			exit(1);

		default: //proces macierzysty
			close(0);
			pdesk=open("/tmp/fifo",O_RDONLY);
			if(pdesk == -1){
				perror("Otwarcie potoku do odczytu");
				exit(1);
			}
			else if(pdesk != 0){

				fprintf(stderr, "Zly deskryptor do odczytu\n");
				exit(1);
			}
			execlp("wc", "wc", NULL);
			perror("Problem przy uruchamianiu wc");
			exit(1);

	}


}
