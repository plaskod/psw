#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define MAX 520

int main(int argc, char* argv[]){

	int fr,fw;
	fr=open(argv[1],O_RDONLY);
	fw=open(argv[2],O_WRONLY);

	char buf[MAX];
	int n;
	while((n=read(fr,buf,MAX))>0)
	{
		write(fw,buf,n);
	}
	return 0;
}
