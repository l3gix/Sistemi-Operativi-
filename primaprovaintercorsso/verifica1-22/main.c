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
    struct dirent * directory;
    struct stat buff;
    int fd,inizio = 1,conta_vocali = 0;
    char c;

    if(argc != 3 )
    {
        printf("ERRORE \n");
        exit(2);
    }

    if((dir = opendir(argv[1])) != NULL)
    {
        while((directory = readdir(dir)) != NULL)
        {
            if(strcmp(directory->d_name,argv[2]) == 0)
            {
                printf("File trovato\n");
                if(lstat(directory->d_name,&buff) != -1)
                {
                    if(S_ISREG(buff.st_mode))
                    {
                        printf("dimensione file %ld\n",buff.st_size);
                        fd = open(directory->d_name,O_RDONLY);
                        while(read(fd,&c,1) > 0)
                        {
                            if(c == ' ' || c == '\n') inizio = 1;
                            if(inizio == 1 && (c != ' ' && c != '\n'))
                            {
                                if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
                                    || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') 
                                {
                                    
                                    conta_vocali++;
                                   
                                }
                                
                                 inizio = 0;
                            }

                            
                        }

                    }else if(S_ISLNK(buff.st_mode))
                    {
                        printf("E un link \n");
                    }
                }
            }
        }
    }

    printf("numero delle vocali per il file %s = %d\n" , argv[2] , conta_vocali);
    return 0;
}