#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define KEY 11111

int main(int argc, char *argv[]){
	time_t t;
	srand((unsigned) time(&t));
	int liczba_pszczol;
	int liczba_misiow;
	if(argc<3){
		printf("Za malo argumentow\n Najpierw nalezy podac liczbe pszczol, potem misiow\n");
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
			buf = (int*)shmat(shmid,NULL,0);
			while(1){
				sleep(1);
				int r=10+rand()%40;
				*buf+=r;
				printf("Pszczola %d zanioslam do ula %d kg miodu, w ulu obecnie jest: %d kg miodu\n", i ,r ,*buf);
			}
		}
		sleep(1);
	}

	for (int i=0;i<liczba_misiow;i++){
		if(!fork()){
			int tmp;
			buf = (int*)shmat(shmid,NULL,0);
			while(1){
				sleep(3);
				if(*buf < 20){
					tmp=*buf;
				}
				else{
					tmp=20+rand()%50;
				}
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
