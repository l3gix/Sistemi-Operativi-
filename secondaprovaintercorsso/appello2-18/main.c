#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <time.h>

int main(void)
{
    int fd1[2];//padre -> figlio
    int fd2[2];//figlio -> padre
    char nomefile[100];
    char c;
    char nomefilefiglio[100];
    char c_figlio;
    int conto_padre = 0;


     char car;
        int start = 1;
        int conto = 0;
    pipe(fd1); // creazione pipe
    pipe(fd2); // creazione pipe

    pid_t f1 = fork();

    if(f1 > 0) // padre
    {   
        close(fd1[0]);
        close(fd2[1]);
        printf("nome file : ");
        scanf("%s",nomefile);
        printf("Inserisci il carattere da cercare : \n");
        scanf(" %c",&c);
        
        write(fd1[1],nomefile,sizeof(nomefile));// scrittura pipe
        write(fd1[1],&c,1); // scrittura pipe 
        close(fd1[1]);

        read(fd2[0],&conto_padre,sizeof(conto_padre));
        close(fd2[0]);

        printf("numero di occorenze %d\n",conto_padre);

    }else if(f1 ==  0) // figlio;
    {
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0],nomefilefiglio,sizeof(nomefilefiglio));
        read(fd1[0],&c_figlio,1);

        close(fd1[0]);
       
        int fd = open(nomefilefiglio,O_RDONLY);
        while(read(fd,&car,1) > 0)
        {
            if(start == 1 )
            {
                if(car == c_figlio) conto++; // controllo prima stringa 
                start = 0;
            }else if(car == ' ' || car == '\n')start = 1;//inzio nuova stringa 
        }

        write(fd2[1],&conto,sizeof(conto));

        close(fd2[1]);



    }

}