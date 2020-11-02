//Napisz program do porównywania plików o nazwach przekazanych jako 
//argumenty. Wynikiem działania programu ma być komunikat że pliki są
//identyczne, pliki różnią się od znaku nr<nr znaku> w linii<nr znaku linii> lub –
//gdy gdy jeden z plików zawiera treść drugiego uzupełnioną o jakieś dodatkowe
//znaki – plik <nazwa> zawiera<liczba>znaków więcej niż zawartość pliku
//<nazwa>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX 1024
#define TXT 100

void terminate(const char msg[]);
void zczytaj_plik(int file, char arr[]);

int main(int argc, char* argv[]){
	if(argc<2){
		terminate("Nie podano wystarczajacej ilosci  nazw plikow\n");
	}
	else{	
		int odwiedzone[argc][argc];
		for(int p=0;p<argc;p++){
			for(int p2=0; p2<argc;p2++){
				odwiedzone[p][p2]=0;
			}
		}
		for(int i=1;i<argc;i++){
			for(int j=1;j<argc;j++){
				if(i==j){
					continue;
				}
				else if(!odwiedzone[i-1][j-1]){


					char msg1[TXT]="Blad przy otwarciu pliku: ";
					strcat(msg1,argv[i]);
					int fd,fd2;
					if((fd=open(argv[i],O_RDONLY))<0) terminate(msg1);
					
					char msg2[TXT]="Blad przy otwarciu pliku: ";
					strcat(msg2,argv[j]);
					if((fd2=open(argv[j],O_RDONLY))<0) terminate(msg2);
					
					odwiedzone[i-1][j-1]=1;
					odwiedzone[j-1][i-1]=1;

					char buf[MAX]="";				
					char buf2[MAX]="";
					zczytaj_plik(fd,buf);
					zczytaj_plik(fd2,buf2);
					
					char *zawiera=strstr(buf,buf2);
					char *zawiera2=strstr(buf2,buf);
					if(zawiera && strlen(buf)==strlen(buf2)){
						char m[TXT]="Pliki: ";
						strcat(m,argv[i]);
						char m1[]=" i ";
						strcat(m1,argv[j]);
						strcat(m,m1);
						char m2[]=" sa identyczne.\n";
						strcat(m,m2);

						write(1,m,strlen(m));
					}
					else if((zawiera||zawiera2) && strlen(buf)!=strlen(buf2)){
						int a=strlen(buf);
						int b=strlen(buf2);
						if(a>b){
							int dlg=a-b;
							char dlugosc[sizeof(int)];
							sprintf(dlugosc,"%d",dlg);
							char m[TXT]="Plik: ";
							strcat(m,argv[i]);
							char m1[]=" zawiera: ";
							strcat(m1,dlugosc);
							char m2[]=" znakow wiecej niz zawartosc pliku: ";
							strcat(m1,m2);
							strcat(m1,argv[j]);
							strcat(m,m1);							
							write(1,m,strlen(m));
							write(1,"\n",1);	
						}
						else{
							int dlg=b-a;
							char dlugosc[sizeof(int)];
							sprintf(dlugosc,"%d",dlg);
							char m[TXT]="Plik: ";
							strcat(m,argv[j]);
							char m1[TXT]=" zawiera: ";
							strcat(m1,dlugosc);
							char m2[TXT]=" znakow wiecej niz zawartosc pliku: ";
							strcat(m1,m2);
							strcat(m1,argv[i]);
							strcat(m,m1);							
							write(1,m,strlen(m));	
							write(1,"\n",1);	
						}
					}
					else{
						int linia=1;
						int pozycja_znaku=1;
						for(int k=0;k<=strlen(buf);k++){
							if(buf[k]=='\n'){
								linia++;
								pozycja_znaku=0;
							}
							if(buf[k]!=buf2[k]){
								char m[TXT]="Pliki: ";
								strcat(m,argv[i]);
								char space[]=" ";
								strcat(m,space);
								strcat(m,argv[j]);
								char mn[]=" roznia sie od znaku nr.: ";
								strcat(m,mn);
								char pos[sizeof(int)];
								sprintf(pos,"%d",pozycja_znaku);
								strcat(m,pos);
								char m2[TXT]=" w linii: ";
								char lin[sizeof(int)];
								sprintf(lin,"%d",linia);
								strcat(m2,lin);
								strcat(m,m2);
								write(1,m,strlen(m));	
								write(1,"\n",1);	
								break;
							}
							pozycja_znaku++;
						}	
					}


					char msg1a[TXT]="Blad przy zamknieciu pliku: ";
					strcat(msg1a,argv[i]);
					if(close(fd)<0) terminate(msg1a);
	
					char msg2a[TXT]="Blad przy zamknieciu pliku: ";
					strcat(msg2a,argv[j]);
					if(close(fd2)<0) terminate(msg2a);

				}
			}
		}
	}
	return 0;
}

void terminate(const char msg[]){

	if(errno!=0){
		perror(msg);
	}
	else{
		write(1,"ERROR: ",strlen("ERROR: "));
		write(1,msg,strlen(msg));
	}
	exit(1);
}

void zczytaj_plik(int file, char buf[]){
	while((read(file,buf,MAX))>0){
		continue;
	}
}	
