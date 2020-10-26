#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#define MAX 1024

void terminate(char *msg);

int main(int argc, char* argv[]){

	if(argc <= 1) terminate("Za malo argumentow");
	int fd;
	if((fd= open(argv[1], O_RDONLY))<0) terminate("Blad przy otwarciu pliku");







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
