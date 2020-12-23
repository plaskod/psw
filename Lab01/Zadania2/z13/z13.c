//Napisz program do znajdowania łańcucha znaków podanego jako pierwszy
//argument linii poleceń w plikach o nazwach podanych jako pozostałe argumenty
//linii poleceń. Program powinien informować o nazwie pliku i miejscu (numer
//linii, numer znaku w linii), w którym dany łańcuch został znaleziony. 

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX 1024
#define TXT 100

void terminate(const char msg[]);

int main(int argc, char* argv[]){
	if(argc==1){
		terminate("Nie podano lancucha znakow albo nazw plikow\n");	
	}
	else if(argc==2){
		terminate("Nie podano nazw plikow\n");
	}
	else{

		char ss[MAX];
		strcpy(ss,argv[1]);
		write(1,"Szukany lancuch to: ",sizeof("Szukany lancuch to: "));
		write(1,ss,strlen(ss));
		write(1,"\n",1);

		for(int i=2;i<argc;i++){
			char msg[TXT]="Blad przy otwarciu pliku: ";
			strcat(msg,argv[i]);
			int fd;
			if((fd=open(argv[i],O_RDONLY))<0) terminate(msg);
			char x;
			char buf[MAX]="";
			int iter=0;
			int line_num=1;
			while((read(fd,&x,1)>0)){
				buf[iter]=x;
				if(x=='\n'){
					char tmp[MAX]="";
					strncpy(tmp,buf,iter+1);
					char *zawiera;
					zawiera=strstr(tmp,ss);
					if(zawiera){
						char m1[TXT]="Lancuch znaleziono w pliku: ";
						strcat(m1,argv[i]);
						char m2[TXT]=" w linii nr.: ";
						strcat(m1,m2);
						char linia[sizeof(int)];
						sprintf(linia,"%d",line_num);
						strcat(m1,linia);
						char m3[TXT]=" oraz numerze znaku: ";
						strcat(m1,m3);
						int miejsce;
						miejsce= zawiera-tmp+1;
						char pozycja[sizeof(int)];
						sprintf(pozycja, "%d",miejsce);
						strcat(m1,pozycja);

						write(1,m1,strlen(m1));
						write(1,"\n",1);
						
					}

					memset(buf,'\0',MAX);
					iter=0;
					line_num++;
				}
				else{
					iter++;
				}
			}
			
			char msg2[TXT]="Blad przy zamknieciu pliku: ";
			strcat(msg2,argv[i]);
			if(close(fd)<0) terminate(msg2);
		}
	}
	return 0;
}

void terminate(const char msg[]){

	if(errno!=0){
		perror(msg);
	}
	else{
		write(1,"ERROR: ",strlen("ERROR: "));
		write(1,msg,strlen(msg));
	}
	exit(1);
}
