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
    int fd[2];//pipe
    pipe(fd);
    pid_t f1;
    int op1,op2;
    int sum,op1_figlio,op2_figlio;
    char op_figlio;
    char op;


    f1 = fork();

    if(f1 > 0) // padre
    {
        close(fd[0]);
        printf("Inserisci le operazioni : \n");
        scanf("%d %c %d",&op1,&op,&op2);
        
        write(fd[1],&op1,sizeof(op1));
        write(fd[1],&op,sizeof(op));
        write(fd[1],&op2,sizeof(op2));

        close(fd[1]);
        wait(NULL);
        exit(0);
    }else if(f1 == 0)//figlio
    {
        close(fd[1]);
        read(fd[0],&op1_figlio,sizeof(op1_figlio));
        read(fd[0],&op_figlio,sizeof(op_figlio));
        read(fd[0],&op2_figlio,sizeof(op2_figlio));
        switch (op_figlio)
        {
        case '+':
            sum = op1_figlio + op2_figlio;
            /* code */
            break;
        case '-':
            sum = op1_figlio - op2_figlio;
            /* code */
            break;
        case '*':
            sum = op1_figlio * op2_figlio;
            /* code */
            break;
        case '/':
            sum = op1_figlio / op2_figlio;
            /* code */
            break;
        }
        
        printf("Somma : %d\n",sum);

        close(fd[0]);
        exit(0);
    }
}