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
#include <dirent.h>
#include <time.h>

int main(void)
{
    int fd1[2]; // prima pipe
    int fd2[2]; // seconda pipe 
    pipe(fd1);
    pipe(fd2);

    char input[100]; // stringa input padre
    char c; // carattere input padre
    int numero_padre ; // il numero che aspetta il padre 

    char input_figlio[100] ; // stringa input del figlio 
    char c_figlio; // carattere del figlio 
    int conta_figlio = 0;

    // var per gestire le directory
    DIR *dir,*dir2;
    struct dirent * directory,*directory2;
    struct stat buff;

    pid_t f1 = fork(); // creazione figlio

    if(f1 > 0) // codice padre
    {
        close(fd1[0]); // chiusa prima pipe in lettura 
        close(fd2[1]); // chiusara seconda pipe in scrittura 

        printf("Inserisci la stringa in input : ");
        scanf("%s",input);
        printf("Inserisci il careattere : ");
        scanf(" %c", &c);
        
        write(fd1[1],input,sizeof(input));
        write(fd1[1],&c,sizeof(c));

        close(fd1[1]);
        
        read(fd2[0],&numero_padre,sizeof(numero_padre));
        close(fd2[0]);

        printf("Numero di volte : %d\n",numero_padre);

        return 0;

    }else if(f1 == 0) // codice figlio
    {
        close(fd1[1]); // chiusura prima pipe in scrittura 
        close(fd2[0]); // chiusura seconda pipe in lettura 

        read(fd1[0],input_figlio,sizeof(input_figlio));
        read(fd1[0],&c_figlio,sizeof(c_figlio));
        
        close(fd1[0]);
        // apertura della directory
        if((dir = opendir(".") )!= NULL )
        {
            // lettura delle directory entry
            while((directory = readdir(dir)) != NULL)
            {    
                // la entry coincide con il nome 
                if(strcmp(input_figlio,directory->d_name) == 0)
                {
                    // ci prendiamo le informazione della entry con la stat
                    if(lstat(directory->d_name,&buff) != -1)
                    {
                        // controllo se è una directory
                        if(S_ISDIR(buff.st_mode))
                        {
                            // entro nella directory per controllare le directory entry 
                            if((dir2 = opendir(directory->d_name)) != NULL)
                            {
                                while((directory2 = readdir(dir2)) != NULL)
                                {
                                    char *s = directory2->d_name;
                                    if(s[strlen(s)-1] == c_figlio) conta_figlio++;
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
        closedir(dir2);
        closedir(dir);
        write(fd2[1],&conta_figlio,sizeof(conta_figlio));
        close(fd2[1]);

        exit(0);

    }
}