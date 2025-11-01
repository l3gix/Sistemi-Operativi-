#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    DIR *dir;
    struct dirent *directory;
    struct stat buff;
    int conta = 0;
  

    if(argc != 2 )
    {
        printf("ERRORE\n");
        exit(2);
    }

    if(lstat(argv[1],&buff) != -1)
    {
        if(S_ISDIR(buff.st_mode))
        {
            printf("Directory \n");
            if((dir = opendir(argv[1])) != NULL)
            {
                while((directory = readdir(dir)) != NULL) conta++;
            }

            printf("numero di file nella directory %d \n", conta);

        }else if(S_ISREG(buff.st_mode))
        {
            printf("Regular file\n");
        }

        printf("dimensione %ld\n",buff.st_size);
        printf("id del propietario %d\n",buff.st_uid);
        printf("Numero dei link %ld\n",buff.st_nlink);
    }

}