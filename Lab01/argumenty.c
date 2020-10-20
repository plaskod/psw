#include <stdio.h>

int main(int argc, char* argv[])
{
	for (int i=0; i< argc; i++)
	{
		printf("argument %d: %s\n",i,argv[i]);
	}
	printf("Koniec...\n");
	return 0;

};
