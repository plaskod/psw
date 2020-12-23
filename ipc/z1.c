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
	int mid = msgget(0x123,0666 | IPC_CREAT);
	
	struct MsgText msg;

	msg.type=1;

	if(fork()==0){
		sleep(1);
		strcpy(msg.text, "Hello\n");
		msgsnd(mid, &msg, strlen(msg.text)+1,0);
		printf("\nProces wyslal wiadomosc\n");
		exit(1);

	}
	else{
		struct MsgText msgR;
		msgR.type=1;
		int mid=msgget(0x123,0666| IPC_CREAT);
		
		if(msgrcv(mid, &msgR,256,1,0)==-1){
			perror("MSGRCV nie zadzialal");
			exit(1);
		}
		printf("Odebrana wiadomosc: %s\n",msgR.text);
		
	}

}
