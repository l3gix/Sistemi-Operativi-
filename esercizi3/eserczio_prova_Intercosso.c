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
    struct dirent *directory;
    struct stat buf;
    struct stat buff_link;
    DIR *dir;
    char c,buffer[100];
    char cwd[100];

    if(argc != 3) printf("Errore \n");

    getcwd(cwd,sizeof(cwd));

    if(dir = opendir(cwd) != NULL)
    {
        while ((directory = readdir(dir) )!= NULL)
        {
            if(!strncmp(directory->d_name,argv[2],size(argv[2])))
            {
                    printf("Il nome e un prefisso %s\n", directory->d_name);
            }

            if(lstat(directory->d_name,&buf) != -1 )
            {
                if( S_ISREG(buf.st_mode)) printf("Regular file\n");
                else if(buf.st_mode == S_ISLINK())
                {
                    printf("Link file\n");
                    printf("Dimensione del file %d",buf.st_size);
                    
                    readlink(directory->d_name,buffer,size(buffer));
                    if(lstat(buffer,&buff_link) != -1)
                    {
                        if(S_ISREG(buff_link.st_mode )) printf("Regular file\n");
                        else if(S_ISDIR(buff_link.st_mode)) printf("Directory file\n");
                        else if(S_ISCHR(buff_link.st_mode)) printf("Charcher special file\n");
                        else if(S_ISBLK(buff_link.st_mode)) printf("Block special file\n");
                        else if(S_ISFIFO(buff_link.st_mode)) printf("Pipe file\n");
                        else if(S_ISLNK(buff_link.st_mode)) printf("Symbolic file\n");
                        else printf("Socket file\n");
                    }
                   
                }
            }
        }
        
    }
    

    return 0;
}