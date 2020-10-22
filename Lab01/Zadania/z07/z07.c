#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>

int main( int argc, char* argv[]){

	int fd;
	fd = open(argv[1], O_RDWR);

	bool tekst= true;
	char x;
	while(read(fd, &x, 1)>0){
		if (isascii(x)!=true){
			tekst=false;
		}
	}
	if(tekst) printf("Plik tekstowy \n");
	else printf("Plik nie tekstowy \n");


	return 0;
}

