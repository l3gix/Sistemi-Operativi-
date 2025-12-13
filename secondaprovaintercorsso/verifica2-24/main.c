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
    
    int fd[2];//pipe
    pipe(fd);// creo la pipe
    char nomefile[100];
    char nomefileinput[100];
    pid_t f1;

    f1 = fork();

    if(f1 > 0) //padre
    {
        close(fd[0]);
        printf("Insersci il nome del file : ");

        scanf("%s",nomefile);
        
        write(fd[1],&nomefile,sizeof(nomefile)); // scrivo nell pipe

        close(fd[1]);

        wait(NULL);

    }else if(f1 == 0) // figlio 
    {
        close(fd[1]);

        read(fd[0],&nomefileinput,sizeof(nomefileinput));

        close(fd[0]);
        execl("./CONTA_SPAZI","CONTA_SPAZI",nomefileinput,NULL);
        exit(1);
    }
}