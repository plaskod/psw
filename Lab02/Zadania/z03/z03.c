#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>


#define MAX 1024


int main(int argc, char* argv[]){

	printf("Poczatek\n");
	execlp("ls", "-a", NULL);
	printf("Koniec\n");

}

