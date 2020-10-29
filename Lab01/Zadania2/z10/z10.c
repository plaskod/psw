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
		int word_cnt=0;
		int was_word=0;
		while((read(1,&x,1)>0)){
			int tmp=x;
			if(((tmp >=48 && tmp <=57)||(tmp >= 65 && tmp <= 90)||(tmp >= 97 && tmp <= 122)||(tmp == 95))&&(was_word==0)) {	
				word_cnt++;
				was_word=1;
			}
		
			else if(((tmp >=48 && tmp <=57)||(tmp >= 65 && tmp <= 90)||(tmp >= 97 && tmp <= 122)||(tmp == 95))) {	
				continue;
			}
			else{
				was_word=0;
			}

		}
		printf("\nIlosc podanych slow to: %d\n",word_cnt); 
	}
	else{
		int fd;
		if((fd=open(argv[1], O_RDONLY))<0) terminate("Blad w otwieraniu pliku");
		char x;
		int word_cnt=0;
		int was_word=0;
		while((read(fd,&x,1)>0)){
			int tmp=x;
			if(((tmp >=48 && tmp <=57)||(tmp >= 65 && tmp <= 90)||(tmp >= 97 && tmp <= 122)||(tmp == 95))&&(was_word==0)) {	
				word_cnt++;
				was_word=1;
			}
			else if(((tmp >=48 && tmp <=57)||(tmp >= 65 && tmp <= 90)||(tmp >= 97 && tmp <= 122)||(tmp == 95))) {	
				continue;
			}
			else{
				was_word=0;
			}

		}
		if(close(fd)<0) terminate("Blad przy zamykaniu pliku");
		printf("\nIlosc slow w pliku: %s wynosi: %d\n",argv[1],word_cnt);
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
