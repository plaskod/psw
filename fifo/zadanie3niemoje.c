#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
//serwer klient
#define MAX 512

int main(int argc, char *argv[]){
    int pdeskS, pdeskK, lbajt;
    char buf[MAX];
    if (fork()==0){//serwer
        mkfifo("fifoS", 0666);
        pdeskS = open("fifoS", O_RDONLY);
        if (pdeskS == -1){
            perror("Serwer: blad otwarcia kolejki");
            exit(1);
        }
        sleep(1);
        lbajt = read(pdeskS,buf, MAX);
        if(fork() == 0){
            close(1);
            pdeskK = open(buf, O_WRONLY);
            if(pdeskK == -1){
                perror("Serwer: blad otwarcia kolejki klienta");
                exit(1);
            }
            execlp("ls", "ls", NULL);
            close(pdeskK);
            perror("Blad ls");
            exit(1);
        }
        
    }else{
        if (fork()==0){//klient
            mkfifo("fifoK", 0666);
            pdeskS = open("fifoS", O_WRONLY);
            if(pdeskS == -1){
                perror("blad otwarcia kolejki Serwera");
                exit(1);
            }
            write(pdeskS, "fifoK", 6);
            close(pdeskS);
            pdeskK = open("fifoK", O_RDONLY);
            if(pdeskK == -1){
                perror("blad otwarcia kolejki Klienta");
                exit(1);
            }
            lbajt = read(pdeskK, buf, MAX);
            write(1, buf, lbajt);
            
        }else{
            wait(NULL);
        }
    }
}
