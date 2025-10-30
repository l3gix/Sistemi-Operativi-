#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    struct dirent *directory; // per la directory
    struct stat buf; // per leggre la stat
    DIR *dir; // per leggere la direcory 
    int fd1;

    
    char c;
    char cwd[100]; // per prender la currente work directory


    getcwd(cwd,100);

    if((dir = opendir(cwd) )!= NULL)
    {   
        while((directory = readdir(dir) )!= NULL) // prendiamo le entry della direcory e di cui ci importa il nome
        {
           if(lstat(directory->d_name,&buf) >= 0) // prendiamo le informazioni dei file tramite la stat
           {
                if(S_ISLNK(buf.st_mode)) // controlliamo se e un link 
                {
                    fd1 = open(directory->d_name,O_RDONLY);
                    while(read(fd1,&c,1) > 0)
                    {
                        printf("%c",c);
                    }
                }
           }
        }
    }

}