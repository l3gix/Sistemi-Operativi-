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
    int ispal = 1;
    char input[100];
    char input_figlio[100];
    char testo[100];

    pipe(fd1);
    pipe(fd2);


    pid_t f1 = fork();
    if(f1 > 0)  // padre
    {
        close(fd1[0]);
        close(fd2[1]);

        printf("Inserisci la stringa : ");
        scanf("%s",input);

        write(fd1[1],input,sizeof(input));
        close(fd1[1]);

        read(fd2[0],testo,sizeof(testo));
        close(fd2[0]);
        //wait(NULL);

        printf("risulatato : %s\n",testo);

        exit(0);

    }else if(f1 == 0) // figlio
    {
        close(fd1[1]);
        close(fd2[0]);

        read(fd1[0],input_figlio,sizeof(input_figlio));
        close(fd1[0]);

        for(int i = 0; i < (strlen(input_figlio) / 2) ; i++)
        {
            if(input_figlio[i] != input_figlio[strlen(input_figlio) - i - 1]) ispal = 0; //sono divere;
        }

        if(ispal) write(fd2[1],"palindroma",sizeof("palindroma"));
        else write(fd2[1],"notpalindroma",sizeof("notpalindroma"));

        close(fd2[1]);
        exit(0);

    }
}