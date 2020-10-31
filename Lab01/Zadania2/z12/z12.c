// ---ZAD12--- Napisz program do filtrowania linii tekstu odczytywanego ze standardowego
//wejścia w taki sposób, że jeśli linia odczytanego tekstu zawiera łańcuch znaków 
//przekazanych jako argument linii poleceń, to jest ona zapisywana na
//standardowym wyjściu, w przeciwnym przypadku jest pomijana.


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX 1024

void terminate(const char msg[]);

int main(int argc, char* argv[]){
	
	if(argc==2){
		char ss[MAX];
		strcpy(ss,argv[1]);
		char ans[MAX]="";
		char buf[MAX]="";
		int num_chars=0;
		char y;
		while((read(1,&y,1)>0)){
			buf[num_chars]=y;	
			if(y=='\n'){
				char tmp[MAX]="";
				strncpy(tmp,buf,num_chars+1);
				char *zawiera;
				zawiera=strstr(tmp,ss);
				if(zawiera){
					strcat(ans,tmp);
				}
				
				memset(buf,'\n',MAX);	
				num_chars=0;
			}
			else{
				num_chars++;
			}
		}
		write(1,"\n",1);
		write(1,"---WYNIK---\n",sizeof("---WYNIK---\n"));
		write(1,ans,sizeof(ans));

	}
	else if(argc==1){
		terminate("Nie podano lancucha znakow\n");
	}
	else{
		terminate("Podano zbyt duzo argumentow\n");
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
