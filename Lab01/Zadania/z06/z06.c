#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#define MAX 1024		

void terminate(char* msg);

int main(int argc, char* argv[]){

	if(argc <= 1) terminate("Za malo argumentow");
	int fd,fd2;
	if((fd= open(argv[1], O_RDONLY))<0) terminate("Blad przy otwarciu pliku nr. 1");	
	if((fd2= open(argv[2], O_WRONLY))<0) terminate("Blad przy otwarciu pliku nr. 2");
	
	lseek(fd,-11,SEEK_END);
	char z;
	for(int i=0; i<10; i++){
		read(fd,&z,1);
		write(fd2,&z,1);
	}
	write(fd2,"\n",1);	
	write(fd2,"\n",1);

	char buf[MAX];
	int iter=0;	
	int num_of_words=0;
	int filesize;
	filesize=lseek(fd,0,SEEK_END);
	char x;	
	for(int i=filesize-1; i>=0; i--){
		lseek(fd,i,SEEK_SET);
		read(fd, &x,1);
		
		if(num_of_words == 10 && (x==' ' || x=='\n')){
			num_of_words++;
			break;
		}
		else if(x==' '){
			num_of_words++;
			buf[iter]=x;
			iter++;
		}
		else if(x=='\n'){
			num_of_words++;
			buf[iter]='\n';
			iter++;
		}
		else{
			buf[iter]=x;
			iter++;
		}
	}
	
	for(int j=iter-1; j>=0; j--){
			
		write(fd2,&buf[j],1);
	}	
	write(fd2,"\n",1);

	lseek(fd,0,SEEK_END);
	char line[MAX];
	char l;
	int num_of_lines=0;
	int it=0;
	for(int i=filesize-1; i>=0; i--){
		lseek(fd,i,SEEK_SET);
		read(fd, &l, 1);
		if(num_of_lines==10 && l=='\n'){
			num_of_lines++;
			line[it]='\n';
			it++;
			break;
		}
		else if(l=='\n'){
			num_of_lines++;
			line[it]='\n';
			it++;
		}
		else{
			line[it]=l;
			it++;
		}
	}	
	for(int k=it-1;k>=0;k--){
		write(fd2,&line[k],1);
	}



	if(close(fd)<0) terminate("Blad przy zamknieciu pliku nr 1");
	if(close(fd2)<0) terminate("Blad przy zamknieciu pliku nr 2");
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

