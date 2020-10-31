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
	char s[MAX]="";
	s[0]='b';
	s[1]='3';
	char t[MAX]="";
	strncpy(t,s,1);
	write(1,s,strlen(s));
	write(1,"\n",1);
	write(1,t,strlen(t));	
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
