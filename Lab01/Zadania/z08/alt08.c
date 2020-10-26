#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#define MAX 1024

void terminate(char *msg);

int main(int argc, char* argv[]){

	 if(argc==1){
		char x;
		char buf[MAX];
		int iter=0;
		while((read(1,&x,1)>0)){
			int tmp=x;
			if(tmp >= 65 && tmp <= 90){
				tmp+=32;
			}
			else if(tmp >= 97 && tmp <=122){
				tmp-=32;
			}
			if (tmp=='\n'){
				buf[iter]='\n';
			}
			else{
				buf[iter]=tmp;
			}
			iter++;

		}
		write(1,"\n",1);		
		write(1,buf,iter);		
	}
	else{
		int fd;
		if((fd= open(argv[1], O_RDWR))<0) terminate("Blad przy otwarciu pliku");
		char x;
		while((read(fd, &x, 1)>0)){
			int tmp=x;	
			if(tmp >= 65 && tmp <= 90){
				tmp+=32;
			}

			else if(tmp >= 97 && tmp <= 122){
				tmp-=32;
			}

			lseek(fd, -1, SEEK_CUR);
			if(tmp == '\n'){
				write(fd,"\n",1);
			}
			else{	
				char temp=tmp;
				write(fd,&temp,1);
			}
		}
		if(close(fd)<0) terminate("Blad przy zamknieciu pliku");
	}
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
