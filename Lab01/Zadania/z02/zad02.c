#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

#define MAX 1024

int main(int argc, char* argv[])
{
	int fd;
	fd=open(argv[1],O_RDWR);

	char buf[MAX];
	char line_buf[MAX];
	int line_len=0;
	while(read(fd,&buf, MAX)>0){
		line_len++;
		if(buf=="\n"){
			for(int i=line_len-1;i>0;i--){
				write(fd,&line_buf[i],1);
			}
			write(fd,"\n",1);
			line_len=0;
		}
		line_buf[line_len]=buf;
	}


	return 0;
}
