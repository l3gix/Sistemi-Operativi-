#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX 50

int main(void)
{
    int fd1,fd2,n;
    char buff[MAX];
    char buff2;

    fd1 = open("FILE3",O_CREAT | O_TRUNC | O_RDWR , 0666) ;// apro un file in lettura e nel momento in cui non esite lo crea con i permessi 666
    fd2 = open("FILE4",O_CREAT | O_TRUNC | O_RDWR , 0666);

    n = read(0,&buff,MAX);

    buff[n] = '\0';

    write(fd1,&buff,n);

    while((n = read(fd1,&buff2,1) )> 0)
        buff[n] = buff2;
    
    for(int i = strlen(buff) - 1  ; i >= 0 ; i--)
    {
        if(buff[i] != '\n') write(fd2,&buff[i],1);// nel caso incontra lo spazio non lo inserisce 
    }

    //Da rifare 
    
    //printf("la stringa %s",buff);
}