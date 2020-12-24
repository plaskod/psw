#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAX 1024

int main(int argc, char *argv[]){
    int ps, pc;
    char buf[MAX];
    int bajty;
    if (fork()==0){//server
        mkfifo("fs", 0666);
        ps = open("fs", O_RDONLY);
        if (ps == -1){
            perror("Serwer: blad otwarcia kolejki");
            exit(1);
        }
        sleep(1);
        bajty = read(ps,buf, MAX);
        if(fork() == 0){
            close(1);
            pc = open(buf, O_WRONLY);
            if(pc == -1){
                perror("Serwer: blad otwarcia kolejki klienta");
                exit(1);
            }
            execlp("ls", "ls", NULL);
            close(pc);
            perror("Blad ls");
            exit(1);
        }
        
    }else{
        if (fork()==0){//klient
            mkfifo("fc", 0666);
            ps = open("fs", O_WRONLY);
            if(ps == -1){
                perror("blad otwarcia kolejki Serwera");
                exit(1);
            }
            write(ps, "fc", 6);
            close(ps);
            pc = open("fc", O_RDONLY);
            if(pc == -1){
                perror("blad otwarcia kolejki Klienta");
                exit(1);
            }
            bajty = read(pc, buf, MAX);
            write(1, buf, bajty);
            
        }else{
            wait(NULL);
        }
    }
}
