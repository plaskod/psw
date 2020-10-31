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
		char ans[MAX];
		char buf[MAX];
		int iter=0;
		char x;
		while((read(1,&x,1)>0)){
		
			buf[iter]=x;	
			if(x=='\n'){

				char tmp[MAX];
				//strncpy(tmp,buf,iter)
				write(1,buf,iter+1);
				strncpy(tmp,buf,iter+1);
				write(1,tmp,strlen(tmp));		
				char *zawiera;
				zawiera=strstr(tmp,ss);
				if(zawiera){
					//strcpy(tmp,buf);
					strcat(ans,tmp);
				}

				iter=-1;
			}
			iter++;
		}
		write(1,"\n",1);
		write(1,ans,strlen(ans));

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
