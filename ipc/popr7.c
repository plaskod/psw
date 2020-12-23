#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#define MAX 512

void closing(int pdesk[5][2])
{
int i;
for(i = 0; i<5; i++)
{
	int j;
	for(j=0; j<2; j++)
	{
		close(pdesk[i][j]);
	}
} 
}

int main(int argc, char* argv[]) {
int x, pdesk[5][2], i;

for(i = 0; i<5; i++)
{
	pipe(pdesk[i]);
} 

switch(fork())
{
	case  -1:// blad w tworzeniu  procesu
		perror(" Tworzenie  procesu ");
		exit (1);
	case 0://  proces  potomny

		if(fork()==0)
		{	
		if(fork()==0)
		{
			if(fork()==0)
			{
				if(fork()==0)
				{
					dup2(pdesk[0][1], 1);
					closing(pdesk);
					execlp("ps", "ps","-ef", NULL);
				}
				dup2(pdesk[0][0], 0);
				dup2(pdesk[1][1], 1);
				closing(pdesk);
				execlp("tr", "tr", " ", ":", NULL);
			}
			dup2(pdesk[1][0], 0);
			dup2(pdesk[2][1], 1);
			closing(pdesk);
			execlp("cut", "cut", "-d:", "-f","1", NULL);
			
		}
		
		dup2(pdesk[2][0], 0);
		dup2(pdesk[3][1], 1);
		closing(pdesk);
		execlp("sort","sort", NULL);;
		}
		
		else{
		dup2(pdesk[3][0], 0);
		dup2(pdesk[4][1], 1);
		closing(pdesk);
		execlp("uniq","uniq","-c", NULL);
		exit (1);
		}
	default: 
	{//  proces  macierzysty


		dup2(pdesk[4][0], 0);
		closing(pdesk);
		execlp("sort","sort", "-n", NULL);
		perror("Urochomienie tr");
		exit(1);
		
	}
}
}
