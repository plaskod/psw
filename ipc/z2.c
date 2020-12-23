#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
struct MsgText{
	long type;
	char text[256];

};

int main(int argc, char* argv[]){
	
	if(argc!=2){
		perror("Za malo argumentow");
		exit(1);
	}

	int x;
	x=atoi(argv[1]);

	int mid = msgget(0x123,0666 | IPC_CREAT);
	
	struct MsgText msg;

	msg.type=1;

	if(fork()==0){
		sleep(1);
		for(int i=1; i<10;i++){
			msg.type=i;
			sprintf(msg.text,"Wiadomosc o typie: %d",i);
			msgsnd(mid,&msg,256,0);
		}
		
		exit(1);

	}
	else{
		struct MsgText msgR;
		msgR.type=1;
		int mid=msgget(0x123,0666| IPC_CREAT);
		
		if(msgrcv(mid, &msgR,256,x,0)==-1){
			perror("MSGRCV nie zadzialal");
			exit(1);
		}
		printf("Odebrana wiadomosc: %s\n",msgR.text);
		
	}

}
