#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int fd2,fd1,fout;
    char buff;
    fd1 = open("FILE1",O_RDWR);
    fd2 = open("FILE2",O_TRUNC | O_CREAT | O_RDWR , 0666); 

    fout = dup(1);// prendo il riferimento lo fd  
    dup2(fd1,0); //assegna un altro fd
    dup2(fd2,1); //assegna un altro fd 

    while(read(0,&buff,1) > 0) 
    {
        write(1,&buff,1);
    }

    dup2(fout,1);

    printf("Ho finito\n");
}