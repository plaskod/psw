#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 1024

int main( int argc, char* argv[]){

	int fd;
	fd = open(argv[1], O_RDWR);

	bool tekst= true;
	char x;
	while(read(fd, &x, 1)>0){
		if (isascii(x)!=true){
			tekst=false;
			break;
		}
	}


	if(tekst){
		 char text[]= "Plik tekstowy \n"; 
		 write(2, text ,sizeof(text));
	}
	else{
		 char text[]="Plik nie tekstowy \n";
		 write(2, text, sizeof(text));
	}

	return 0;
}

