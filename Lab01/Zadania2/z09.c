#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#define MAX 1024

void terminate(char *msg);



int main(int argc, char* argv[]){
	int dest,fd;
	if(argc==3){
		if((dest=open(argv[2],O_WRONLY))<0) terminate("Blad przy otwarciu pliku drugiego");
		if((fd=open(argv[1],O_RDONLY))<0) terminate("Blad przy otwarciu pliku do odczytu");
		char buf[MAX];
		int n;
		while((n=read(fd,buf,MAX))>0){
			write(dest,buf,n);
		}
		
	}
	else{
		if((dest=open(argv[argc-1], O_WRONLY))<0) terminate("Blad przy otwarciu pliku docelowego");

		for(int i=1; i<argc-1; i++){
			if((fd=open(argv[i],O_RDONLY))<0) terminate("Blad przy otwarciu pliku do odczytu)");
			char buf[MAX];
			int n;
			while((n=read(fd,buf,MAX))>0){
				write(dest,buf,n);
			}
			if(close(fd)<0) terminate("Blad przy zamknieciu pliku do odczytu");
		}
	}	
	if(close(dest)<0) terminate("Blad przy zamknieciu pliku do odczytu");
	



	return 0;
}

void terminate(char *msg){

	if(errno!=0){
		perror(msg);
	}

	else{
		fprintf(stderr, "ERROR: %s\n", msg);
	}
	exit(1);
}
