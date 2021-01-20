#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define KEY 12345

int main(int argc, char *argv[]){
	int liczba_pszczol;
	int liczba_misiow;
	if(argc<3){
		printf("Za malo argumentow\n");
		exit(1);
	}
	else{
		liczba_pszczol=atoi(argv[1]);
		liczba_misiow=atoi(argv[2]);
	}


	int shmid;
	int *buf;
	
	shmid=shmget(KEY,sizeof(int),IPC_CREAT|0600);
	if(shmid == -1){
		perror("Blad w shmget\n");
		exit(1);
	}

	buf = (int*)shmat(shmid,NULL,0);
	*buf=0;

	for (int i=0;i<liczba_pszczol;i++){
		if(!fork()){
			int miod_dodany=0;
			buf = (int*)shmat(shmid,NULL,0);
			while(1){
				sleep(1);
				miod_dodany+=10;
				*buf+=10;
				printf("Pszczola %d zanioslam do ula %d kg miodu, w ulu obecnie jest: %d kg miodu\n", i ,20 ,*buf);
			}
		}
		sleep(1);
	}

	for (int i=0;i<liczba_misiow;i++){
		if(!fork()){
			int miod_zjedzony=0;
			int tmp;
			buf = (int*)shmat(shmid,NULL,0);
			while(1){
				sleep(3);
				if(*buf < 20){
					tmp=*buf;
				}
				else{
					tmp=20;
				}
				miod_zjedzony+=tmp;
				*buf -= tmp;
				printf("Mis %d zjadl %d kg miodu, pozostalo: %d\n",i,tmp,*buf);
			}
		}
		sleep(2);

	}
	
	shmdt(buf);
	shmctl(shmid,IPC_RMID,NULL);
	wait(NULL);

}
