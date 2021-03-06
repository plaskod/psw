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
	if((fd= open(argv[1], O_RDWR))<0) terminate("Blad przy otwarciu pliku");
	char x;
	char buf[MAX];
	int iter=0;
	while((read(fd, &x, 1)>0)){
		int tmp=x;	
		if(tmp >= 65 && tmp <= 90){
			tmp+=32;
		}

		else if(tmp >= 97 && tmp <= 122){
			tmp-=32;
		}
		if(tmp == '\n'){
			buf[iter]='\n';
		}
		else{
			buf[iter]=tmp;
		}

		iter++;
	
	}
	lseek(fd, 0, SEEK_SET);
	write(fd,buf,iter);
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
