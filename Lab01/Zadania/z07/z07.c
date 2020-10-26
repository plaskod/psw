#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 1024

int main( int argc, char* argv[]){

	int fd;
	fd = open(argv[1], O_RDWR);

	char x;
	while(read(fd, &x, 1)>0){
		if (isascii(x)!=1){
		  char text[]= "Plik nie jest tekstowy \n"; 
		  write(2, text, sizeof(text));
		  exit(0); 	
		}
	}
		 char text[]="Plik jest tekstowy \n";
		 write(2, text, sizeof(text));

	return 0;
}

