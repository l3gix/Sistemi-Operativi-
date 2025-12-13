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


int main(int argc,char *argv[])
{
    char c;
    int conta = 0;

    if(argc != 2)
    {
        printf("Errore");
        exit(2);
    }

    int fd = open(argv[1],O_RDONLY);
    
    while(read(fd,&c,sizeof(c)) > 0)
    {
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
            || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'
        ) conta++;
    }


    printf("Numero di vocali %d\n", conta);

    exit(0);
}