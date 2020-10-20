#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int suma=0;
	for(int i=1; i<argc; i++)
	{
		suma+=atoi(argv[i]);
	}
	printf("Suma argumentow to: %d\n",suma);
	return 0;
}
