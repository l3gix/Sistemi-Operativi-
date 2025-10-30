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
    int fd,num_spazi = 0, num_par = 0;
    char c;

    if((dir = opendir(argv[1])) != NULL)
    {
        while((directory = readdir(dir)) != NULL)
        {
            if(directory->d_name[0] == 'a' || directory->d_name[0] == 'A')
            {
                printf("il file inzia con la lettera a/A \n");
                num_par = 0;
                num_spazi = 0;
                if(lstat(directory->d_name,&buff) != -1)
                {
                    if(S_ISREG(buff.st_mode)) 
                    {
                        printf("Regular file\n");
                        printf("I permessi %o\n",buff.st_mode);
                        fd = open(directory->d_name,O_RDONLY);
                        while(read(fd,&c,1) > 0)
                        {
                            if(c == ' ') num_spazi++;
                            else if(c == '\n') num_par++;
                        }
                    }else if(S_ISDIR(buff.st_mode))
                    {
                        printf("directory \n");
                    }
                    
                     printf(" %s = numero di spazi = %d and numero di paragrafi = %d\n",directory->d_name,num_spazi,num_par);

                }

            }
        }
    }

   
}