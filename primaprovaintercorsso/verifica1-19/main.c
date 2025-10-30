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
    char cwd[100],c;
    int fd,parola = 1,conta = 0,num_stringhe = 0;

    if(argc != 2)
    {
        printf("ERRORE\n");
        exit(2);
    }
    getcwd(cwd,100);

    if((dir = opendir(cwd)) != NULL )
    {
        while((directory = readdir(dir)) != NULL)
        {
            if(strncmp(directory->d_name,argv[1],strlen(argv[1])) == 0)
            {
                printf("contine la parola %s\n",argv[1]);
                parola = 1;
                conta = 0;
                num_stringhe = 0;

                if(lstat(directory->d_name,&buff) != -1)
                {
                    if(S_ISREG(buff.st_mode))
                    {
                       fd = open(directory->d_name,O_RDONLY);
                       while(read(fd,&c,1) > 0)
                       {    
                            if(c != ' ' )conta++;
                            if(c != ' ' && parola == 1)
                            {
                                if(c == 'a' || c == 'A')num_stringhe++;
                                parola = 0;
                            }else if(c == '\n' || c == ' ')
                            {
                                parola = 1;
                            }

                       }

                       printf("%s = numero della paroloe %d and stringhe che inziano per a/A %d\n",directory->d_name,conta,num_stringhe);

                    }else if(S_ISDIR(buff.st_mode))
                    {
                        printf("E una directory\n");
                    }
                }
            }
        }
    }
}