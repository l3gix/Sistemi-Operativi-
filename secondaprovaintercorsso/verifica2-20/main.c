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

int main(void)
{
    int fd1[2]; // padre -> figlio
    int fd2[2]; // figlio -> padre

    char nomefile[100];
    char stringa[100];
    char nomefile_figlio[100];
    char stringa_figlio[100];
    char input[100];

    int conta = 0;
    int conta_input;
    pipe(fd1);
    pipe(fd2);

    pid_t figlio = fork();

    if(figlio > 0 ) // padre
    {
        close(fd1[0]); // chiusura lettura da parte del padre

        close(fd2[1]);// chiusara in scrittura da parte del padre da usare successivamente 

        printf("Insersci nomefile : ");
        scanf("%s",nomefile);
        printf("Inserisci la stringa : ");
        scanf("%s",stringa);

        write(fd1[1],nomefile,sizeof(nomefile));
        write(fd1[1],stringa,sizeof(stringa));

        close(fd1[1]);

        read(fd2[0],&conta_input,sizeof(conta_input));

        close(fd2[0]);

        printf("conto : %d\n",conta_input);

        wait(NULL);
    }else if(figlio == 0) // figlio
    {
        close(fd1[1]); // chiusura scrittura da parte del figlio
        close(fd2[0]); // chiusura lettura da parte del figlio che usera succesivamente 

        read(fd1[0],nomefile_figlio,sizeof(nomefile_figlio));
        read(fd1[0],stringa_figlio,sizeof(stringa_figlio));

        close(fd1[0]);

        FILE *f = fopen(nomefile_figlio,"r");
        while(fscanf(f,"%s",input) > 0) // parto dal fatto che il file abbia per ogni riga una sola parola 
        {
            if(strncmp(input,stringa_figlio,strlen(stringa_figlio)) == 0)conta++;
        }

        fclose(f);


        write(fd2[1],&conta,sizeof(conta));
        close(fd2[1]);

        exit(0);

    }


    return 0;

}