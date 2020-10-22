#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

#define MAX 1024

int main(int argc, char* argv[])
{
	int fd;
	fd=open(argv[1],O_RDWR);

	char buf[MAX];
	char x;
	int i=0,j;
	while(read(fd,&x,1)>0)
	{
		if(x!='\n')
		{
			buf[i]=x;
			i++;
		}
		else
		{
			lseek(fd,-(i+1),SEEK_CUR);
			for(j=i-1;j>=0;j--)
			{
				write(fd,&buf[j],1);
			}
			write(fd,"\n",1);
			i=0;
		}

	}
	return 0;
}
