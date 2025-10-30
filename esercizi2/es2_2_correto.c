#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


int main()
{
    int fd1,fd2;
    int pos;
    char buff;
    fd1 = open("File1",O_RDONLY);
    fd2 = open("File2",O_RDWR | O_CREAT | O_TRUNC  ,0644);

    pos = lseek(fd1,-1,SEEK_END);

    while ( pos >= 0 )
    {
        read(fd1,&buff,1);
        write(fd2,&buff,1);
        pos = lseek(fd1,-2,SEEK_CUR);
    }
    
    return 0;

}