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

    // var del padre 
    char input[100] ; // input del padre 
    int is_dir_padre;
    int conto_padre;

    // var figlio 
    char input_figlio[100]; 
    int is_dir_figlio = 0; // varibile per capire se la directory contiene un entrty che è una dicectory e che ha lo stesso nome della stringa passata in input
    int conta_figlio = 0;
    
    // var per gestire le directory
    DIR *dir,*dir2;
    struct dirent * directory,*directory2;
    struct stat buff,buff2;

    pid_t f1 = fork(); // creazione figlio

    if(f1 > 0) // codice del padre 
    {
        close(fd1[0]); // chiusa prima pipe in lettura 
        close(fd2[1]); // chiusara seconda pipe in scrittura 
        printf("Input della stringa : ");
        scanf("%s",input);

        // scrivo la stringa da mandare al figlio 
        write(fd1[1],input,sizeof(input));
        close(fd1[1]);


        read(fd2[0],&is_dir_padre,sizeof(is_dir_padre));

        if(is_dir_padre)
        {
            printf("Esiste la directory\n");

            read(fd2[0],&conto_padre,sizeof(conto_padre));
            printf("Numero di file standard : %d\n",conto_padre);

        }else 
        {
            printf("La directory non esite ");
        }

        close(fd2[0]);

        return 0;


    }else if ( f1 == 0) // codice del figlio
    {
        close(fd1[1]); // chiusura prima pipe in scrittura 
        close(fd2[0]); // chiusura seconda pipe in lettura 

        // legge la stringa mandata dal padre 
        read(fd1[0],input_figlio,sizeof(input_figlio));
        close(fd1[0]); // chiude la prima pipe 

        // controllo se esiste una directory con il nome preso dalla pipe 
        if((dir = opendir(".")) != NULL)
        {
            while((directory = readdir(dir)) != NULL)
            {
                if(strcmp(input_figlio,directory->d_name) == 0)
                {
                    if(lstat(directory->d_name,&buff) != -1)
                    {
                        if(S_ISDIR(buff.st_mode))
                        {
                            is_dir_figlio = 1;
                            break;
                        }
                    }
                }
            }
        }

        closedir(dir);
        //scrivo al padre se ce una direcory con il nome da input 
        write(fd2[1],&is_dir_figlio,sizeof(is_dir_figlio));

        if(is_dir_figlio) //entriamo solo se esista la directory seno è inutile contare 
        {
            if((dir2 = opendir(input_figlio)) != NULL)
            {
                while((directory2 = readdir(dir2)) != NULL)
                {
                    //printf("%s\n",directory2->d_name);
                    
                    // serve per prendere bene le informazione prendendo la direcortyr
                    // quindi sara input_figlio/directory2->d_name pk serve il path
                    char path[100];
                    strcpy(path,input_figlio);
                    strcat(path,"/");
                    strcat(path,directory2->d_name);

                    if(lstat(path,&buff2) != -1)
                    {
                        if(S_ISREG(buff2.st_mode))
                        {
                            conta_figlio++;
                        }
                    }
                }
            }
        }
        closedir(dir2);
        //scrivo al padre il numero di reg file trovati
        write(fd2[1],&conta_figlio,sizeof(conta_figlio));
        close(fd2[1]);

        exit(0);

    }
}