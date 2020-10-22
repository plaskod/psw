#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	int x;
	if(argc >= 1){
		int file1;
		file1=open(argv[1], O_RDWR);

		while(read(file1, &x, 1)>0){
			if((x>=65) && (x<=90))
			{
				x+=32;
				write(file1, &x, 1);
			}

			else if((x>=97 && x<=122))
			{
				x-=32;
				write(file1, &x, 1);
			}
		}

	}
	return 0;
}
