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
    char cwd[100],c;
    int fd,conta = 0;
    if(argc != 3)
    {
        fprintf(stderr,"Errore\n");
        exit(2);
    }

   

    getcwd(cwd,100);
    if((dir = opendir(cwd)) != NULL)
    {
        while((directory = readdir(dir)) != NULL)
        {
            if(strcmp(argv[1],directory->d_name) == 0) 
            {
                printf("Trovata cio che coincide\n");

                if((lstat(directory->d_name,&buff)) != -1)
                {
                    if(S_ISREG(buff.st_mode)) // controlliamo se è un regula file
                    {
                        printf("Regula file\n");
                        printf("permessi file %o\n" , buff.st_mode);
                        printf("Dimensione %ld \n", buff.st_size);
                        fd = open(directory->d_name,O_RDONLY);// apriamo un file in sola lettura 
                        while(read(fd,&c,1) > 0) // leggiamo un carattere alla volta 
                        {
                            if(c == *argv[2])conta++; // contiamo se troviamo il carattere 
                        }

                    }else if(S_ISDIR(buff.st_mode)) // controlliamo se una directory
                    {
                        printf("una dirctory");
                    }else 
                    {
                        printf("nessuna delle scelte chieste");
                    }
                }
            }
        } 
    }

    printf("Numero di %c contate = %d\n",*argv[2],conta);
    return 0;
}