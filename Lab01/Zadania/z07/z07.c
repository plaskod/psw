#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#define MAX 1024

void terminate(char* msg);

int main(int argc, char* argv[]){
	
	if(argc <= 1) terminate("Za malo argumentow");		
	int fd;
	if((fd = open(argv[1], O_RDWR))<0) terminate("Blad przy otwarciu pliku");

	char x;
	while(read(fd, &x, 1)>0){
		if (isascii(x)!=1){
		  char text[]= "Plik nie jest tekstowy \n"; 
		  write(1, text, sizeof(text));
		  exit(0); 	
		}
	}
		  char text[]="Plik jest tekstowy \n";
		  write(1, text, sizeof(text));
	
	if(close(fd)<0) terminate("Blad przy zamknieciu pliku");
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
