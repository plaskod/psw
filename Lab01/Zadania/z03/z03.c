#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 1024

int main(int argc, char* argv[]){

	int len=0, max_len=0;
	int fd;
	fd = open(argv[1], O_RDONLY);
	char x;
	while(read(fd, &x, 1)>0){
		len++;
		if(x == 'n'){
			if(len > max_len){
				max_len = len -1;
			}
		}
	}
	printf("%d\n", max_len);


	return 0;
}
