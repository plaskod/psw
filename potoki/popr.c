#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>


int main(int argc, char* argv[]){
	int pdesk[2];
	int fd=0;
	pipe(pdesk);
	if(fork()==0){
		dup2(pdesk[1],1);
		close(pdesk[0]);
		execlp("ps","ps","-ef",NULL);
		exit(1);
	}
	else{
		wait(NULL);
		close(pdesk[1]);
		fd=pdesk[0];
		pipe(pdesk);
		if(fork()==0){
			dup2(fd,0);
			dup2(pdesk[1],1);
			close(pdesk[0]);
			execlp("tr","tr","-s","' '",":",NULL);
			exit(1);

		}
		else{
			wait(NULL);
			close(pdesk[1]);
			fd=pdesk[0];
			pipe(pdesk);
			
			if (fork()==0){
				dup2(fd,0);
				dup2(pdesk[1],1);
				close(pdesk[0]);
				execlp("cut","cut","-d:","-f1",NULL);
				exit(1);
			}
			else{
				wait(NULL);
				close(pdesk[1]);
				fd=pdesk[0];
				pipe(pdesk);

				if(fork()==0){

					dup2(fd,0);
					dup2(pdesk[1],1);
					close(pdesk[0]);
					execlp("sort", "sort",NULL);
					exit(1);
				}

				else{
					wait(NULL);
					close(pdesk[1]);
					fd=pdesk[0];
					pipe(pdesk);

					if(fork()==0){
						dup2(fd,0);
						close(pdesk[0]);
						execlp("uniq","uniq","-c",NULL);
						exit(1);
						
					}
					else{
						wait(NULL);
						close(pdesk[1]);
						fd=pdesk[0];
						pipe(pdesk);

						if(fork()==0){
							dup2(fd,0);
							close(pdesk[0]);
							execlp("sort", "sort" "n", NULL);
							exit(1);	
						}

						else{
							wait(NULL);
						}
					}

				}
			}
		}
	}


}	
