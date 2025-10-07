#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd,i;
    fd = open("FILE1",O_TRUNC | O_CREAT | O_RDWR | O_EXCL, 0666); // Creazione di un file con permessi di scrittura lettura e esecuzione
    write(fd,"aaaa",4); // Scrivo nel file 
    i = lseek(fd,20,SEEK_CUR); // Mi sposto 
    write(fd,"bbbbb",4); // Riscrivo sul file 
}